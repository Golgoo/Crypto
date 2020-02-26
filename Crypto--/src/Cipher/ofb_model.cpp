#include "Cipher/ofb_model.hpp"

#include "Util/util.hpp"

Ofb_Model::Ofb_Model(crypter::Coder coder, CipherPadder *jammer): OperatingModel(coder, jammer)
{

}

Ofb_Model::~Ofb_Model()
{

}

#include <cassert>
void Ofb_Model::encode_file()
{
  std::vector<uchar> buffer ;
  write(_init_vector);

  std::vector<uchar> state = _init_vector ;
  assert(state.size() == _coder.encode_length());
  read(buffer, _coder.encode_length());
  while(buffer.size() == _coder.encode_length()){
    _coder.encode(state);

    operation::XOR(buffer, state);

    write(buffer);
    read(buffer, _coder.encode_length());
  }
  _jammer->jam(buffer, _coder.encode_length());
  _coder.encode(state);
  operation::XOR(buffer, state);
  write(buffer);
}

void Ofb_Model::decode_file()
{
  std::vector<uchar> buffer ;
  std::vector<uchar> state ;

  read(state, _coder.encode_length());
  read(buffer, _coder.encode_length());
  while(buffer.size() > 0){
    _coder.encode(state);
    operation::XOR(buffer, state);
    if(lastBlockReached()){
      _jammer->unjam(buffer);
    }
    write(buffer);
    read(buffer, _coder.encode_length());
  }
}
