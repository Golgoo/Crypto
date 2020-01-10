#include "HMAC.h"
#define _GNU_SOURCE
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>

void copy_header(FILE* src, FILE* dst)
{
  char *buffer = (char*)malloc(sizeof(char)*1024);
  size_t size  ;
  int returned ;
  do{
    returned = getline(&buffer, &size, src);
    fprintf(dst,"%s", buffer);
  }while(returned!=EOF && strchr(buffer, ':')!=NULL);
  free(buffer);
}

void copy_rest(FILE*src, FILE*dst)
{
  char c ;
  while((c = fgetc(src)) != EOF){
    fprintf(dst,"%c", c);
  }
}

void write_x_auth(char* filename, char* value)
{
  FILE *file = fopen(filename,"r+");
  char * existing_xauth = load_header_value(file, "X-AUTH");
  if(existing_xauth != NULL){
    fprintf(stderr, "An X-Auth is already present for this mail : %s\n", existing_xauth);
    fprintf(stderr, "Delete it if you want to change it \n");
  }else{
    FILE * tmp = fopen("tmp.tmp.tmp","w");
    rewind(file);
    copy_header(file, tmp);
    fseek(tmp, -1, SEEK_CUR);
    fprintf(tmp, "X-AUTH: %s\n", value);
    fprintf(tmp,"\n");
    copy_rest(file, tmp);
    fclose(tmp);
    tmp = fopen("tmp.tmp.tmp", "r");
    fseek(file, 0, SEEK_SET);
    copy_rest(tmp, file);
    fclose(tmp);
  }
  fclose(file);
}

char * load_header_value(FILE* fichier, char * field_name)
{
  char *buffer = (char*)malloc(sizeof(char)*1024);
  size_t size  ;
  int returned ;
  const char delim[2] = ": ";
  char *tmp_field_name;
  do{
    returned = getline(&buffer, &size, fichier);
    tmp_field_name = strtok(buffer, delim);
    if(strcmp(field_name, tmp_field_name) == 0){
      tmp_field_name = strtok(NULL, delim);
      tmp_field_name[32] = '\0';
      return tmp_field_name;
    }

  }while(returned!=EOF);

  free(buffer);

  return NULL ;
}

void seek_f_to_corpse(FILE * fichier)
{
  char *buffer = (char*)malloc(sizeof(char)*1024);
  size_t size  ;
  int returned ;
  do{
    returned = getline(&buffer, &size, fichier);
  }while(returned!=EOF && strchr(buffer, ':')!=NULL);
  free(buffer);
}

unsigned char * md5_string(char * string)
{
  MD5_CTX ctx;
  MD5_Init (&ctx);
  MD5_Update(&ctx, string, strlen(string));

  unsigned char * md5_ = (unsigned char*) malloc(sizeof(unsigned char) * MD5_DIGEST_LENGTH);
  MD5_Final (md5_, &ctx);
  return md5_ ;
}

char * convert_md5_to_string(unsigned char * str)
{
  char * chaine = (char*)malloc(sizeof(char)* MD5_DIGEST_LENGTH*2);
  char * tmp = (char*)malloc(sizeof(char)*2);
  for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
    sprintf(tmp, "%02x", str[i]);
    chaine [i*2] = tmp[0];
    chaine [i*2 + 1] = tmp[1];
  }
  free(tmp);
  chaine[MD5_DIGEST_LENGTH*2 ] = '\0';
  return chaine;
}

char * generate_secret()
{
  return "Alain Turin";
}

char * mail_hash_func(FILE *fichier)
{
  seek_f_to_corpse(fichier);
  MD5_CTX contexte;
  MD5_Init (&contexte);

  unsigned char buffer[1024];
  int nb_octets_lus = fread (buffer, 1, sizeof(buffer), fichier); // Lecture du premier morceau
  while (nb_octets_lus != 0) {
    MD5_Update (&contexte, buffer, nb_octets_lus);                // Digestion du morceau
    nb_octets_lus = fread (buffer, 1, sizeof(buffer), fichier);   // Lecture du morceau suivant
  }

  unsigned char *md5_secret = md5_string("Alain Turin");

  char * tmp_not_hex_str = (char*)malloc(sizeof(2));

  for(int i = 0 ; i < MD5_DIGEST_LENGTH ; i++){
    sprintf(tmp_not_hex_str, "%02x", md5_secret[i]);
    MD5_Update(&contexte, tmp_not_hex_str, 2);
  }

  free(tmp_not_hex_str);

  unsigned char resume_md5[MD5_DIGEST_LENGTH];
  MD5_Final (resume_md5, &contexte);

  char * computed_c_auth = convert_md5_to_string(resume_md5);

  return computed_c_auth;
}

void init_with(char * tab, size_t len, char c)
{
  for(ssize_t i = 0 ; i < len ; i ++){
    tab[i] = c;
  }
}

#define STR_LEN 64

char * XOR(char * a, char * b)
{
  char * chaine = (char*)malloc(sizeof(char)*(STR_LEN + 1)) ;
  for(ssize_t i = 0 ; i < STR_LEN ; i ++){
    chaine[i] = a[i]^b[i];
  }
  chaine[STR_LEN] = '\0';
  return chaine;
}

char * mail_hash_func_RFC_2104(FILE *fichier)
{
  char * secret_txt = generate_secret();
  char * secret_md5 = convert_md5_to_string(md5_string(secret_txt));

  char * oppad = (char*)malloc(sizeof(char)*(STR_LEN + 1));
  init_with(oppad, (STR_LEN + 1), 0x5c);
  char * ippad = (char*)malloc(sizeof(char)*(STR_LEN + 1));
  init_with(ippad, (STR_LEN + 1), 0x36);

  char * appendice = (char*)malloc(sizeof(char) * (STR_LEN + 1));
  appendice[0] = '\0';
  strcat(appendice, XOR(secret_md5,oppad));
  printf("Appendice : %s\n", appendice);
  char * arg2 = XOR(secret_md5, ippad);
  printf("Arg2 : %s\n", arg2);
  MD5_CTX contexte;
  MD5_Init (&contexte);

  MD5_Update (&contexte, arg2, STR_LEN);

  seek_f_to_corpse(fichier);
  unsigned char buffer[1024];
  int nb_octets_lus = fread (buffer, 1, sizeof(buffer), fichier); // Lecture du premier morceau
  while (nb_octets_lus != 0) {
    printf("Readed : %s\n", buffer);
    MD5_Update (&contexte, buffer, nb_octets_lus);                // Digestion du morceau
    nb_octets_lus = fread (buffer, 1, sizeof(buffer), fichier);   // Lecture du morceau suivant
  }

  printf("---------\n");
  unsigned char resume_md5[MD5_DIGEST_LENGTH];
  MD5_Final (resume_md5, &contexte);

  char * no_name_idea = (char*)malloc(sizeof(char)*MD5_DIGEST_LENGTH*2);
  char * tmp = (char*)malloc(sizeof(char)*2);
  for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
    sprintf(tmp, "%02x", resume_md5[i]);
    printf("%02x",resume_md5[i]);
    no_name_idea [i*2] = tmp[0];
    no_name_idea [i*2 + 1] = tmp[1];
  }
  free(tmp);
  no_name_idea[MD5_DIGEST_LENGTH*2 ] = '\0';
  printf("\n%s\n",no_name_idea);
  MD5_CTX ctx;
  MD5_Init (&ctx);
  MD5_Update (&ctx, appendice, STR_LEN);
  MD5_Update(&ctx, no_name_idea, STR_LEN);

  MD5_Final(resume_md5, &ctx);

  free(arg2);
  free(ippad);
  free(oppad);
  return convert_md5_to_string(resume_md5) ;
}
