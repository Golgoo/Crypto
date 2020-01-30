#include "aes.hpp"
#include "util.hpp"
#include "diversification.hpp"
#include <cstring>

using namespace AES ;

Decoder::Decoder(uchar * key, size_t key_len) : AES(key, key_len)
{}
Decoder::Decoder(char * key):AES(key)
{}

void Decoder::decode(uchar * current_state)
{
  uchar * currentRound ;
  int nbRound = keyExtender->getNbRound();
  int currentIndex = nbRound - 1 ;

  currentRound = keyExtender->getExtendedKey() + currentIndex * 16;
  crypt_util::XOR(current_state, currentRound, 16);

  for(int i = 0 ; i < 4 ; i ++){
    crypt_util::RotWord(current_state + i*4, 4, 4-i);
  }
  crypt_util::inv_SubWord(current_state, 16);

  for( currentIndex = keyExtender->getNbRound() - 2 ; currentIndex > 0 ; currentIndex --)
  {
    currentRound = keyExtender->getExtendedKey() + currentIndex * 16;

    crypt_util::XOR(current_state, currentRound, 16);

    crypt_util::inv_MixColumn(current_state);
    for(int i = 0 ; i < 4 ; i ++){
      crypt_util::RotWord(current_state + i*4, 4, 4-i);
    }
    crypt_util::inv_SubWord(current_state, 16);
  }

  currentRound = keyExtender->getExtendedKey();

  crypt_util::XOR(current_state, currentRound, 16);
}
