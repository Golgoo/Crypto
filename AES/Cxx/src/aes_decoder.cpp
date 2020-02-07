#include "aes.hpp"
#include "util.hpp"
#include "diversification.hpp"
#include <cstring>

using namespace AES ;

Decoder::Decoder(uchar * key, size_t key_len) : AES(key, key_len)
{}
Decoder::Decoder(char * key):AES(key)
{}

void Decoder::decode(Block& current_state)
{
  uchar * currentRound ;
  int nbRound = keyExtender->getNbRound();
  int currentIndex = nbRound - 1 ;

  currentRound = keyExtender->getExtendedKey() + currentIndex * 16;
  Block roundBlock(4, 4, currentRound);

  //crypt_util::XOR(current_state, currentRound, 16);
  current_state.XOR(roundBlock);

  for(int i = 3 ; i >= 0 ; i --){
    current_state.rotate(i, 4-i);
  }

  //crypt_util::inv_SubWord(current_state, 16);
  current_state.SubBlock(_InvSBlock);

  for( currentIndex = keyExtender->getNbRound() - 2 ; currentIndex > 0 ; currentIndex --)
  {
    currentRound -= 16;
    roundBlock.setContent(currentRound);

    current_state.XOR(roundBlock);
//    crypt_util::XOR(current_state, currentRound, 16);


    //crypt_util::inv_MixColumn(current_state);
    for(int i = 0 ; i < 4 ; i ++)
    {
      current_state.MulCol(i, _InvCBlock);
    }

    for(int i = 0 ; i < 4 ; i ++){
      current_state.rotate(i, 4-i);
    }
    current_state.SubBlock(_InvSBlock);
  }

  currentRound = keyExtender->getExtendedKey();
  roundBlock.setContent(currentRound);
  current_state.XOR(roundBlock);
}
