#include "OperatingModel/cbc_model.hpp"


Cbc_Model::Cbc_Model(const std::string src_path, Jammer *jammer): OperatingModel(src_path, jammer)
{

}

Cbc_Model::~Cbc_Model()
{

}

#include <iostream>
void Cbc_Model::encode_file(const std::string dst_path, crypter::Encoder &encoder)
{
  load_stream(dst_path);
  std::vector<uchar> buffer ;
  std::vector<uchar> state = _init_vector;
  read(buffer, 16);
  /*while(buffer.size() == 16){
    //XOR (state, buffer)
    encoder.encode(state);
    write(state);
    read(buffer, 16);
  }
  _jammer->jam(buffer, 16);
  //XOR(state, buffer)
  encoder.encode(state);*/
  //write(state);
  //TODO Package Utility => XOR vector
}

#include <iostream>
void Cbc_Model::decode_file(const std::string dst_path, crypter::Decoder &decoder)
{
  load_stream(dst_path);
  std::vector<uchar> buffer;
  read(buffer, 16);
  /*while(buffer.size() > 0){
    if(lastBlockReached()){
      _jammer->unjam(buffer);
    }
    decoder.decode(buffer);
    write(buffer);
    read(buffer, 16);
  }*/
}
