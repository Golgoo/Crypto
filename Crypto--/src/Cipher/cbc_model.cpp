#include "Cipher/cbc_model.hpp"

#include "Util/util.hpp"

Cbc_Model::Cbc_Model(crypter::Coder coder, CipherPadder *jammer): OperatingModel(coder, jammer)
{

}

Cbc_Model::~Cbc_Model()
{

}

#include <cassert>
void Cbc_Model::encode_file()
{
  std::vector<uchar> buffer ;
  std::vector<uchar> state = _init_vector;
  assert(state.size() == _coder.encode_length());
  write(_init_vector);
  read(buffer, _coder.encode_length());
  while(buffer.size() == _coder.encode_length()){
    operation::XOR(state, buffer);

    _coder.encode(state);
    write(state);

    read(buffer, _coder.encode_length());
    state.resize(_coder.encode_length());
  }
  _jammer->jam(buffer, _coder.encode_length());
  operation::XOR(state, buffer);
  _coder.encode(state);
  write(state);
}

void Cbc_Model::decode_file()
{
  std::vector<uchar> state;
  read(state, _coder.encode_length());

  std::vector<uchar> buffer;
  std::vector<uchar> tmp ;
  read(buffer, _coder.decode_length());
  while(buffer.size() > 0){
    tmp = buffer ;

    _coder.decode(buffer);
    operation::XOR(state, buffer);

    if(lastBlockReached()){
      _jammer->unjam(state);
    }
    write(state);

    read(buffer, _coder.decode_length());
    state = tmp ;
    state.resize(_coder.encode_length());
  }
}
