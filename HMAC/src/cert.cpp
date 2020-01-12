#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>

#include <HMAC.hpp>
#include <MiniMimeMailer.hpp>

#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
  if(argc < 2){
    printf("Usage..");
    exit(EXIT_FAILURE);
  }

  std::string x_auth_field_name="X-AUTH";

  std::string email_path = argv[1] ;
  std::string secret = "Alain Turin";


  Mailer mailer (email_path);
  std::string corpse = mailer.readCorpse();

  HMAC hmac(corpse);
  std::string hash = hmac.get_RFC_2104_hash(secret);
  std::cout << hash << std::endl;

  mailer.addHeader(x_auth_field_name, hash);

  exit(EXIT_SUCCESS);
}
