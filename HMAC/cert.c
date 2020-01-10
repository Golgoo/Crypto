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

  char * auth = mail_hash_func_RFC_2104(fichier);

  fprintf(stdout, "\n\n*************************\n");
  fprintf(stdout, "X-AUTH : %s", auth);
  fprintf(stdout, "\n*************************\n");
  write_x_auth(file_path, auth);

  fclose (fichier);
  exit(EXIT_SUCCESS);
}
