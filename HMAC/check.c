#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include "HMAC.h"

int main(int argc, char* argv[])
{
  if(argc < 2){
    printf("Usage..");
    exit(EXIT_FAILURE);
  }
  char * file_path = argv[1];

  FILE * fichier = fopen(file_path, "r");
  if(!fichier){
    exit(EXIT_FAILURE);
  }

  char * received_auth = load_header_value(fichier, "X-AUTH");
  if(received_auth == NULL) {
    printf("X-AUTH field not detected in mail's headers\n");
    exit(3);
  }

  char * computed_c_auth = mail_hash_func_RFC_2104(fichier);
  fclose(fichier);

  fprintf(stdout, "Computed X-AUTH : ");
  fprintf(stdout, "%s", computed_c_auth);

  fprintf(stdout, "\n*************************\n");

  fprintf(stdout, "\n\n*************************\n");

  fprintf(stdout, "Found X-AUTH : ");
  fprintf(stdout, "%s", received_auth);

  fprintf(stdout, "\n*************************\n");

  if(strcmp(received_auth, computed_c_auth) == 0 ){
    printf("Authenticity is valid !");
  }else{
    printf("Authenticity is not valid");
  }

  free(computed_c_auth);

  exit(EXIT_SUCCESS);
}
