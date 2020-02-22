#include "Cipher/cfb_model.hpp"
#include "Padder/stub_jam.hpp"
#include "Util/util.hpp"

Cfb_Model::Cfb_Model(crypter::Coder coder, Jammer *jammer): OperatingModel(coder, jammer)
{

}

Cfb_Model::~Cfb_Model()
{

}

#include <cassert>
void Cfb_Model::encode_file()
{
  std::vector<uchar> buffer ;
  write(_init_vector);

  std::vector<uchar> state = _init_vector ;
  assert(state.size() == _coder.encode_length());
  read(buffer, _coder.encode_length());
  while(buffer.size() == _coder.encode_length()){
    _coder.encode(state);
    state.resize(_coder.encode_length());
    operation::XOR(state, buffer);
    write(state);
    read(buffer, _coder.encode_length());
  }
  _jammer->jam(buffer, _coder.encode_length());
  _coder.encode(state);
  state.resize(_coder.encode_length());
  operation::XOR(state, buffer);
  write(state);
}

void Cfb_Model::decode_file()
{
  std::vector<uchar> buffer;
  std::vector<uchar> state ;

  read(state, _coder.encode_length());
  read(buffer, _coder.encode_length());
  while(buffer.size() > 0){
    _coder.encode(state);
    state.resize(_coder.encode_length());
    operation::XOR(state, buffer);
    if(lastBlockReached()){
      _jammer->unjam(state);
    }
    write(state);
    state = buffer ;
    read(buffer, _coder.encode_length());
  }
}
