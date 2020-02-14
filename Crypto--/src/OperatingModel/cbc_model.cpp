#include "OperatingModel/cbc_model.hpp"


Cbc_Model::Cbc_Model(const std::string src_path, crypter::Coder coder, Jammer *jammer): OperatingModel(src_path, coder, jammer)
{

}

Cbc_Model::~Cbc_Model()
{

}

#include <iostream>
#include "Util/operation.hpp"
void Cbc_Model::encode_file(const std::string dst_path)
{
  load_stream(dst_path);
  std::vector<uchar> buffer ;
  std::vector<uchar> state = _init_vector;
  write(_init_vector);
  read(buffer, 16);
  while(buffer.size() == 16){
    operation::XOR(state, buffer);
    _coder.encode(state);
    write(state);
    read(buffer, 16);
  }
  _jammer->jam(buffer, 16);
  operation::XOR(state, buffer);
  _coder.encode(state);
  write(state);
}

#include <iostream>
void Cbc_Model::decode_file(const std::string dst_path)
{
  load_stream(dst_path);

  std::vector<uchar> state;
  read(state, 16);

  std::vector<uchar> buffer;
  std::vector<uchar> tmp ;
  read(buffer, 16);
  while(buffer.size() > 0){
    tmp = buffer ;

    _coder.decode(buffer);
    operation::XOR(state, buffer);

    if(lastBlockReached()){
      _jammer->unjam(state);
    }

    write(state);
    state = tmp ;

    read(buffer, 16);
  }
}
