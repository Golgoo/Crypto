
#include "Cipher/operating_model.hpp"

#include <iostream>

OperatingModel::OperatingModel(crypter::Coder coder, Padder *jammer) :_jammer(jammer), _init_vector(16), _coder(coder)
{
  _input_stream = &std::cin;
  _output_stream = &std::cout;
}

OperatingModel::~OperatingModel()
{

}

void OperatingModel::set_stream(std::istream* input_stream, std::ostream* output_stream)
{
  _input_stream = input_stream;
  _output_stream = output_stream;
}

void OperatingModel::set_input_stream(std::istream *input_stream)
{
  _input_stream = input_stream;
}

void OperatingModel::set_output_stream(std::ostream *output_stream)
{
  _output_stream = output_stream;
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
