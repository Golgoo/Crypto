#include <HMAC.hpp>

#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif
#include <stdlib.h>

#include <string.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


HMAC::HMAC(std::string str)
{
  this->content = str;
}


std::string HMAC::hash_string(std::string str)
{
  MD5_CTX ctx; MD5_Init (&ctx);
  MD5_Update(&ctx, str.c_str(), str.size());
  unsigned char md5_ [MD5_DIGEST_LENGTH];
  MD5_Final (md5_, &ctx);

  string hashed;
  char * tmp = (char*)malloc(sizeof(char)*3);

  for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
    sprintf(tmp, "%02x", md5_[i]);
    tmp[2]='\0';
    hashed += tmp ;
    //std::cout << hashed << endl;
  }
  free(tmp);
  
  return hashed ;
}

void HMAC::hash_secret(std::string secret)
{
  this->hashed_secret = hash_string(secret);
}

void HMAC::init_MD5()
{
  MD5_Init(&this->md5_ctx);
}

void HMAC::append(string str)
{
  this->final_bytes += str;
}

string HMAC::get_soft_hash(std::string secret)
{
  hash_secret(secret);
  init_MD5();
  append(this->content);
  append(this->hashed_secret);
  string res = hash_string(this->final_bytes);
  return res ;
}

#include <sstream>
unsigned int hex2int(const char hex)
{
  unsigned int val;
  std::stringstream ss;
  ss << hex;
  ss >> std::hex >> val;
  return val ;
}

string XOR(string a, string b)
{
  string str;
  if(a.size() == 65 && b.size() == 65)
    for(int i = 0 ; i < 64 ; i++){
      std::stringstream stream ;
      stream << std::hex << (hex2int(a.at(i)) ^ hex2int(b.at(i)));
      //std::string result( stream.str() );
      str.append(stream.str());
    }
  return str;
}

void HMAC::fill(std::string *str, size_t size, string motif)
{
  int motif_size = motif.size();
  for(int i = str->size() ; i < size ; i += motif_size){
    str->append(motif);
  }
  str->push_back('\0');
}

std::string ipad_motif = "36";
std::string opad_motif = "5c";
std::string empty_motif = "0";

string HMAC::get_RFC_2104_hash(std::string secret)
{
  hash_secret(secret);
  init_MD5();

  fill(& this->hashed_secret, 64, empty_motif);
  string ipad ;
  fill(&ipad, 64, ipad_motif);
  string opad ;
  fill(&opad, 64, opad_motif);

  std::cout << "S    : " ;
  std::cout << this->hashed_secret  << endl;
  std::cout << "opad : " ;
  std::cout << opad << endl;

  string s_xor_opad = XOR(this->hashed_secret, opad);

  std::cout << "xor  : " ;
  std::cout << s_xor_opad << endl << endl ;

  std::cout << "S    : " ;
  std::cout << this->hashed_secret  << endl;
  std::cout << "ipad : " ;
  std::cout << ipad  << endl;

  string s_xor_ipad = XOR(this->hashed_secret, ipad);

  std::cout << "xor  : " ;
  cout << s_xor_ipad << endl ;

  append(s_xor_ipad);
  append(this->content);
  string res1 = hash_string(this->final_bytes);
  this->final_bytes.clear();

  std::cout << "f((S xor IPAD).c) => res1"<< endl ;
  std::cout << res1 << endl ;

  append(s_xor_opad);
  append(res1);
  string res = hash_string(this->final_bytes);

  std::cout << "f((S xor OPAD).res1)"<< endl ;
  std::cout << res << std::endl ;

  return res;
}
