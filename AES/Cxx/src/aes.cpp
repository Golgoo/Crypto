#include "aes.hpp"
#include "diversification.hpp"
#include "util.hpp"

using namespace AES ;

#include <cstring>
#include <array>

Encoder::Encoder()
{}

Encoder::~Encoder()
{
  //delete this->keyExtender;
}

uchar * Encoder::encode(uchar *content, char *key)
{
  std::cout << "Here" << std::endl ;
  this->current_state = content ;
  std::cout << key << std::endl ;
  std::cout << (strlen(key) >> 1) << std::endl ;

  //segfault ... //this->keyExtender = new KeyExtender(key, strlen(key) >> 1);
  //keyExtender->printRounds();
  //encode_algo();
  return this->current_state;
}

uchar * Encoder::encode(uchar * content, uchar * key, size_t len)
{
  this->current_state = content ;
  this->keyExtender = new KeyExtender(key, len);
  keyExtender->printRounds();
  encode_algo();
  return this->current_state;
}

void Encoder::encode_algo()
{
  int nbRound = this->keyExtender->getNbRound();
  int currentIndex = 0 ;
  int roundIndex = 0 ;

  crypt_util::XOR(this->current_state, this->keyExtender->getExtendedKey(), 16);

  for( currentIndex = 1 ; currentIndex < this->keyExtender->getNbRound() - 1 ; currentIndex ++)
  {
    crypt_util::SubWord(this->current_state, 16);
    for(int i = 0 ; i < 4 ; i ++){
      crypt_util::RotWord(this->current_state + i*4, 4, i);
    }
    crypt_util::MixColumns(this->current_state);
    crypt_util::XOR(this->current_state, this->keyExtender->getExtendedKey() + currentIndex * 16, 16);
  }
  crypt_util::SubWord(this->current_state, 16);
  for(int i = 0 ; i < 4 ; i ++){
    crypt_util::RotWord(this->current_state + i*4, 4, i);
  }
  crypt_util::XOR(this->current_state, this->keyExtender->getExtendedKey() + this->keyExtender->getNbRound() * 16, 16);
}
