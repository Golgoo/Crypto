#include "Cipher/ecb_model.hpp"

#include "Padder/stub_jam.hpp"

#include "Util/util.hpp"


Ecb_Model::Ecb_Model(crypter::Coder coder, Jammer *jammer): OperatingModel(coder, jammer)
{

}

Ecb_Model::~Ecb_Model()
{

}

void Ecb_Model::encode_file()
{
  std::vector<uchar> buffer ;
  read(buffer, _coder.encode_length());
  while(buffer.size() == 16){
    _coder.encode(buffer);
    write(buffer);
    read(buffer, _coder.encode_length());
  }
  _jammer->jam(buffer, _coder.encode_length());
  _coder.encode(buffer);
  write(buffer);
}

void Ecb_Model::decode_file()
{
  std::vector<uchar> buffer;
  read(buffer, _coder.decode_length());
  while(buffer.size() > 0){
    _coder.decode(buffer);
    if(lastBlockReached()){
      _jammer->unjam(buffer);
    }
    write(buffer);
    read(buffer, _coder.decode_length());
  }
}
