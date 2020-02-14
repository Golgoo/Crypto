#include "OperatingModel/cfb_model.hpp"
#include "Bourrage/stub_jam.hpp"

Cfb_Model::Cfb_Model(const std::string src_path, crypter::Coder coder, Jammer *jammer): OperatingModel(src_path, coder, jammer)
{

}

Cfb_Model::~Cfb_Model()
{

}

#include <iostream>
void Cfb_Model::encode_file(const std::string dst_path)
{
  load_stream(dst_path);
  std::vector<uchar> buffer ;
  write(_init_vector);

  std::vector<uchar> state = _init_vector ;

  read(buffer, 16);
  while(buffer.size() == 16){
    _coder.encode(state);
    operation::XOR(state, buffer);
    write(state);
    read(buffer, 16);
  }
  _jammer->jam(buffer, 16);
  _coder.encode(state);
  operation::XOR(state, buffer);
  write(state);
}

#include <iostream>
void Cfb_Model::decode_file(const std::string dst_path)
{
  load_stream(dst_path);
  std::vector<uchar> buffer;
  std::vector<uchar> state ;

  read(state, 16);
  read(buffer, 16);
  while(buffer.size() > 0){
    _coder.encode(state);
    operation::XOR(state, buffer);
    if(lastBlockReached()){
      _jammer->unjam(state);
    }
    write(state);
    state = buffer ;
    read(buffer, 16);
  }
}
