#include "OperatingModel/ofb_model.hpp"


Ofb_Model::Ofb_Model(const std::string src_path, crypter::Coder coder, Jammer *jammer): OperatingModel(src_path, coder, jammer)
{

}

Ofb_Model::~Ofb_Model()
{

}

#include <iostream>
void Ofb_Model::encode_file(const std::string dst_path)
{
  load_stream(dst_path);
  std::vector<uchar> buffer ;
  write(_init_vector);

  std::vector<uchar> state = _init_vector ;
  read(buffer, 16);
  while(buffer.size() == 16){
    _coder.encode(state);
    operation::XOR(buffer, state);
    write(buffer);
    read(buffer, 16);
  }
  _jammer->jam(buffer, 16);
  _coder.encode(state);
  operation::XOR(buffer, state);
  write(buffer);
}

#include <iostream>
void Ofb_Model::decode_file(const std::string dst_path)
{
  load_stream(dst_path) ;
  std::vector<uchar> buffer ;
  std::vector<uchar> state ;

  read(state, 16);
  read(buffer, 16);
  while(buffer.size() > 0){
    _coder.encode(state);
    operation::XOR(buffer, state);
    if(lastBlockReached()){
      _jammer->unjam(buffer);
    }
    write(buffer);
    read(buffer, 16);
  }
}
