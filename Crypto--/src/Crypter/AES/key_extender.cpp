#include "Crypter/AES/aes.hpp"

using namespace aes;

#include <cassert>
#include <algorithm>

#include "Util/util.hpp"

KeyExtender::KeyExtender(std::vector<uchar> key)
{
  _key_len = key.size();
  assert(_key_len == 16 ||_key_len == 24 ||_key_len == 32);

  _rounds.push_back(key);
  init_Ns();
  computeExtendedKey();
}

void KeyExtender::init_Ns()
{
  if (_key_len == 16){
    _Nr = 10; _Nk = 4;
  } else if (_key_len == 24){
    _Nr = 12; _Nk = 6;
  } else {
    _Nr = 14; _Nk = 8;
  }
}




void KeyExtender::computeExtendedKey()
{
  std::vector<uchar> tmp(4);
  int modulo ;
  std::vector<uchar> current_round;
  std::vector<uchar> last_col(_Nk);

  for(int round_index = 0 ; round_index < 4 * (_Nr+1) ; round_index++){

    std::vector<uchar> tmp_col(_Nk);
    int modulo = round_index % _Nk ;

    if(modulo == 0){
      std::copy(_rounds.back().end() - 4 , _rounds.back().end(), tmp_col.begin());
    }else{
      std::copy(current_round.end() - 4 , current_round.end(), tmp_col.begin());
    }

    if(modulo == 0){
      operation::RotWord(tmp_col, 1);
      operation::SubWord(tmp_col);
      operation::RCon(tmp_col, (round_index / _Nk));
    }else if(_Nk > 6 && modulo == 4){
      operation::SubWord(tmp_col);
    }

    operation::XOR(tmp_col, _rounds.back(), modulo*4);

    current_round.resize(current_round.size()+4);
    std::copy(tmp_col.begin(), tmp_col.end(), current_round.begin() + modulo * 4);
    if(current_round.size() == 4 * _Nk){
      _rounds.push_back(current_round);
      current_round.clear();
    }
  }
}

KeyExtender::~KeyExtender()
{

}

std::vector<uchar> KeyExtender::getRound(int roundIndex) const
{
  return _rounds[roundIndex];
}
std::vector<std::vector<uchar>> KeyExtender::getRounds() const
{
  return _rounds;
}
int KeyExtender::getNbRounds() const
{
  return _Nr + 1;
}
