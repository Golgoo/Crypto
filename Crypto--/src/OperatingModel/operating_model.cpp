
#include "OperatingModel/operating_model.hpp"


OperatingModel::OperatingModel(const std::string src_path, Jammer *jammer) :_jammer(jammer), _init_vector(16)
{
  _input_stream = new std::ifstream(src_path.c_str());
}

OperatingModel::~OperatingModel()
{
  if(_input_stream) {
    _input_stream->close();
    delete _input_stream;
  }
  if(_output_stream){
    _output_stream->close();
    delete _output_stream;
  }
}

void OperatingModel::load_stream(const std::string dst_path)
{
  if(_output_stream != nullptr){
    _output_stream->close();
    delete _output_stream;
  }
  _output_stream = new std::ofstream(dst_path.c_str(), std::ios::out | std::ios::binary);
}

void OperatingModel::read(std::vector<uchar> &buffer, int octets)
{
  buffer.resize(octets);
  _input_stream->read((char*)(&buffer[0]), octets);
  buffer.resize(_input_stream->gcount());
}

void OperatingModel::set_init_vector(std::vector<uchar> vector)
{
  _init_vector = vector ;
}

bool OperatingModel::lastBlockReached()
{
  return (_input_stream->peek()<0);
}

void OperatingModel::write(std::vector<uchar> &buffer)
{
  _output_stream->write((const char*)&buffer[0], buffer.size());
}
