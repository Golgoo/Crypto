#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif
#include <openssl/md5.h>

#include <HMAC.hpp>
#include <MiniMimeMailer.hpp>

#include <string>

int main(int argc, char* argv[])
{
  if(argc < 2){
    printf("Usage..");
    exit(EXIT_FAILURE);
  }
  string x_auth_field_name = "X-AUTH";
  string email_path = string(argv[1]);

  string secret = "Alain Turin";


  Mailer mailer(email_path);
  string found_auth = mailer.getHeaderValue(x_auth_field_name) ;


  HMAC hmac (mailer.readCorpse());
  string computed_auth = hmac.get_RFC_2104_hash(secret);

  if(computed_auth == found_auth){
    std::cout << "Valid auth" << std::endl;
  }else{
    std::cout << computed_auth << std::endl;
    std::cout << found_auth << std::endl;
  }

  exit(EXIT_SUCCESS);
}
