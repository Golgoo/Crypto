#include "Crypter/AES/aes.hpp"

using namespace aes;

//#define NDEBUG
#include <cassert>
#include "Util/util.hpp"

AES::AES(std::vector<uchar> key):_CBlock(4, 4, constantes::CBox), _SBlock(16, 16, constantes::SBox),
                                 _InvCBlock(4, 4, constantes::InvCBox), _InvSBlock(16, 16, constantes::InvSBox)
{
  _key_extender = new KeyExtender(key);
}

AES::~AES()
{
  if(_key_extender != nullptr)
  delete _key_extender;
}

void AES::encode(std::vector<uchar>& block)
{
  assert(block.size() == 16);
  Block current_state(4, 4, block);

  int nbRound = _key_extender->getNbRounds();
  int currentIndex = 0 ;
  std::vector<uchar> currentRound = _key_extender->getRound(0);
  Block roundBlock(4, 4, currentRound);

  current_state.XOR(roundBlock);

  for( currentIndex = 1 ; currentIndex < nbRound - 1 ; currentIndex ++)
  {
    current_state.SubBlock(_SBlock);

    for(int i = 0 ; i < 4 ; i ++){
      current_state.rotate(i, i);
    }
    for(int c = 0 ; c < 4 ; c ++){
      current_state.MulCol(c, _CBlock);
    }
    currentRound = _key_extender->getRound(currentIndex);
    roundBlock.setContent(currentRound);

    current_state.XOR(roundBlock);

  }
  current_state.SubBlock(_SBlock);

  for(int i = 0 ; i < 4 ; i ++){
    current_state.rotate(i, i);
  }

  currentRound = _key_extender->getRound(currentIndex);
  roundBlock.setContent(currentRound);

  current_state.XOR(roundBlock);

  current_state.write_into_vector(block);
}

void AES::decode(std::vector<uchar>& block)
{
  assert(block.size() == 16);

}
