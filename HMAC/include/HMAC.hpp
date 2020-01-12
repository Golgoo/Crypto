#ifndef __HMAC_H__
#define __HMAC_H__

#include <stdio.h>
#include <cstddef>
#include <vector>
#include <string>
#include <openssl/md5.h>

using namespace std;

class HMAC{
  public :
    HMAC(vector<std::byte> bytes);
    HMAC(std::string str);
  private :
    string content ;
    string hashed_secret ;

    MD5_CTX md5_ctx;
    std::string final_bytes ;

  private:
    string hash_string(std::string str);
    vector<byte> hash_bytes(std::vector<byte> bytes);
    void hash_secret(std::string secret);
    void init_MD5();
    void append(string str);

    void fill(string* str, size_t size, string motif);
  public :
    string get_soft_hash(std::string secret);
    string get_RFC_2104_hash(std::string secret);
};

std::vector<byte> transform_into_bytes(std::string str);

void seek_f_to_corpse(FILE * fichier);

unsigned char * md5_string(char * string);

char * mail_hash_func(FILE *fichier);

char * mail_hash_func_RFC_2104(FILE *fichier);

char * generate_secret();

char * load_header_value(FILE* fichie, char * field_value);

void write_x_auth(char* filename, char* value);

char * convert_md5_to_string(unsigned char * str);

#endif
