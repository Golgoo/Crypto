#include "OperatingModel/ecb_model.hpp"



Ecb_Model::Ecb_Model(const std::string src_path): OperatingModel(src_path)
{

}

Ecb_Model::~Ecb_Model()
{

}


void Ecb_Model::encode_file(const std::string dst_path, crypter::Encoder &encoder)
{
  load_stream(dst_path);
  std::vector<uchar> buffer ;
  read(buffer, 16);
  while(buffer.size() > 0){
    encoder.encode(buffer);
    write(buffer);
    read(buffer, 16);
  }
}

void Ecb_Model::decode_file(const std::string dst_path, crypter::Decoder &decoder)
{
  load_stream(dst_path);
  std::vector<uchar> buffer;
  read(buffer, 16);
  while(buffer.size() > 0){
    decoder.decode(buffer);
    write(buffer);
    read(buffer, 16);
  }
}
