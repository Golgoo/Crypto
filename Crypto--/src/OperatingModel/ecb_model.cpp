#include "OperatingModel/ecb_model.hpp"

#include "Bourrage/stub_jam.hpp"


Ecb_Model::Ecb_Model(const std::string src_path, crypter::Coder coder, Jammer *jammer): OperatingModel(src_path, coder, jammer)
{

}

Ecb_Model::~Ecb_Model()
{

}

#include <iostream>
void Ecb_Model::encode_file(const std::string dst_path)
{
  load_stream(dst_path);
  std::vector<uchar> buffer ;
  read(buffer, 16);
  while(buffer.size() == 16){
    _coder.encode(buffer);
    write(buffer);
    read(buffer, 16);
  }
  _jammer->jam(buffer, 16);
  _coder.encode(buffer);
  write(buffer);
}

#include <iostream>
void Ecb_Model::decode_file(const std::string dst_path)
{
  load_stream(dst_path);
  std::vector<uchar> buffer;
  read(buffer, 16);
  while(buffer.size() > 0){
    if(lastBlockReached()){
      _jammer->unjam(buffer);
    }
    _coder.decode(buffer);
    write(buffer);
    read(buffer, 16);
  }
}
