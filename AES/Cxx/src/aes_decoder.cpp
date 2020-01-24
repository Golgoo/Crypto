#include "aes.hpp"
#include "util.hpp"
#include "diversification.hpp"
#include <cstring>
using namespace AES ;


/** TODO :: tester les fonciton utilitaire d'inversement */
Decoder::Decoder()
{}

/*TODO Abstraction pour construction/initialisation + vérifier les longeurs des clefs*/
uchar * Decoder::decode(uchar * content, char * key)
{
  this->current_state = content ;
  this->keyExtender = new KeyExtender(key, strlen(key) >> 1);

  decode_algo();
  return this->current_state ;
}

uchar * Decoder::decode(uchar * content, uchar * key, size_t len)
{
  this->current_state = content ;
  this->keyExtender = new KeyExtender(key, len);

  decode_algo();
  return this->current_state;
}

void Decoder::decode_algo()
{
  //This bloc for the future abstract initialisation ; use class field plz.
  int nbRound = this->keyExtender->getNbRound();
  int currentIndex = this->keyExtender->getNbRound() - 1 ;
  uchar * currentRound ;

  currentRound = this->keyExtender->getExtendedKey() + currentIndex * 16;
  crypt_util::reverse(currentRound, 4, 4);
  crypt_util::XOR(this->current_state, currentRound, 16);
  for(int i = 0 ; i < 4 ; i ++){
    crypt_util::RotWord(this->current_state + i*4, 4, 4-i);
  }
  crypt_util::inv_SubWord(this->current_state, 16);

  for( currentIndex = this->keyExtender->getNbRound() - 2 ; currentIndex > 0 ; currentIndex --)
  {
    currentRound = this->keyExtender->getExtendedKey() + currentIndex * 16;
    crypt_util::reverse(currentRound, 4, 4);

    crypt_util::XOR(this->current_state, currentRound, 16);

    crypt_util::inv_MixColumn(this->current_state);
    for(int i = 0 ; i < 4 ; i ++){
      crypt_util::RotWord(this->current_state + i*4, 4, 4-i);
    }
    crypt_util::inv_SubWord(this->current_state, 16);
  }

  currentRound = this->keyExtender->getExtendedKey();
  crypt_util::reverse(currentRound, 4, 4);
  crypt_util::XOR(this->current_state, currentRound, 16);
}

Decoder::~Decoder(){
  delete keyExtender ;
}
