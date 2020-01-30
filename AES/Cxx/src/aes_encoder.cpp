#include "aes.hpp"
#include "diversification.hpp"
#include "util.hpp"

#include <cstring>
#include <iostream>

using namespace AES ;

Encoder::Encoder(uchar * key, size_t key_len):AES(key, key_len)
{}
Encoder::Encoder(char * key):AES(key)
{}

void Encoder::encode(uchar *current_state)
{
  int nbRound = keyExtender->getNbRound();
  int currentIndex = 0 ;
  uchar * currentRound = keyExtender->getExtendedKey();

  crypt_util::XOR(current_state, currentRound, 16);

  for( currentIndex = 1 ; currentIndex < nbRound - 1 ; currentIndex ++)
  {
    crypt_util::SubWord(current_state, 16);

    for(int i = 0 ; i < 4 ; i ++){
      crypt_util::RotWord(current_state + i*4, 4, i);
    }
    crypt_util::MixColumns(current_state);
    currentRound += 16;

    crypt_util::XOR(current_state, currentRound, 16);
  }
  crypt_util::SubWord(current_state, 16);

  for(int i = 0 ; i < 4 ; i ++){
    crypt_util::RotWord(current_state + i*4, 4, i);
  }
  currentRound = currentRound += 16;

  crypt_util::XOR(current_state, currentRound, 16);
}

void Encoder::encode_file(char * src_filename, char * dst_filename)
{
  FILE *f_src = fopen(src_filename, "r");
  FILE *f_dst = fopen(dst_filename, "w");

  if(f_src && f_dst) {
    uchar * content = (uchar*)malloc(sizeof(uchar) * 16);
    uchar buffer[16];
    for(int i = 0 ; i < 16 ; i ++) content [i] = 0x00 ;

    int nb_octets_lus = fread (buffer, 1, sizeof(buffer), f_src);
    while (nb_octets_lus == 16) {
      crypt_util::XOR(content, buffer, 16);
      this->encode(content);

      for(int i = 0 ; i < 16 ; i ++)
        fputc(content[i], f_dst);
      nb_octets_lus = fread (buffer, 1, sizeof(buffer), f_src);
    }

    std::cout << "Left length : " << 16 - nb_octets_lus << std::endl ;
    if(nb_octets_lus == 0){
      crypt_util::fill(buffer, 16, 0x16);
    }else{
      crypt_util::fill(buffer + nb_octets_lus, 16 - nb_octets_lus, 16 - nb_octets_lus);
    }

    crypt_util::XOR(content, buffer, 16);
    this->encode(content);
    for(int i = 0 ; i < 16 ; i ++)
      fputc(content[i], f_dst);

    free(content);
  }
  if(f_src)
    fclose(f_src);
  if(f_dst)
    fclose(f_dst);
}
