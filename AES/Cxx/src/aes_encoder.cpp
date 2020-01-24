#include "aes.hpp"
#include "diversification.hpp"
#include "util.hpp"

#include <cstring>

using namespace AES ;

Encoder::Encoder()
{}

Encoder::~Encoder()
{
  delete keyExtender ;
}

uchar * Encoder::encode(uchar *content, char *key)
{
  this->current_state = content ;
  this->keyExtender = new KeyExtender(key, strlen(key) >> 1);

  encode_algo();
  return this->current_state;
}

uchar * Encoder::encode(uchar * content, uchar * key, size_t len)
{
  this->current_state = content ;
  this->keyExtender = new KeyExtender(key, len);

  encode_algo();
  return this->current_state;
}

void Encoder::encode_algo()
{
  int nbRound = this->keyExtender->getNbRound();
  int currentIndex = 0 ;
  uchar * currentRound = this->keyExtender->getExtendedKey();
  crypt_util::reverse(currentRound, 4, 4);
  //crypt_util::print_key(currentRound, 16);
  crypt_util::XOR(this->current_state, currentRound, 16);

  for( currentIndex = 1 ; currentIndex < this->keyExtender->getNbRound() - 1 ; currentIndex ++)
  {
    crypt_util::SubWord(this->current_state, 16);
    //ShiftRows
    for(int i = 0 ; i < 4 ; i ++){
      crypt_util::RotWord(this->current_state + i*4, 4, i);
    }
    crypt_util::MixColumns(this->current_state);
    currentRound = this->keyExtender->getExtendedKey() + currentIndex * 16;
    crypt_util::reverse(currentRound, 4, 4);
    //crypt_util::print_key(currentRound, 16);
    crypt_util::XOR(this->current_state, currentRound, 16);
  }
  crypt_util::SubWord(this->current_state, 16);
  //ShiftRows
  for(int i = 0 ; i < 4 ; i ++){
    crypt_util::RotWord(this->current_state + i*4, 4, i);
  }
  currentRound = this->keyExtender->getExtendedKey() + currentIndex * 16;
  crypt_util::reverse(currentRound, 4, 4);
  //crypt_util::print_key(currentRound, 16);
  crypt_util::XOR(this->current_state, currentRound, 16);
}
