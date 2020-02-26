#ifndef __OPERATING_MODEL_HPP__
#define __OPERATING_MODEL_HPP__

#include <vector>
#include <string>


typedef unsigned char uchar;

#include "Crypter/coder.hpp"
#include "Padder/CipherPadder.hpp"

#include <istream>
#include <ostream>

class OperatingModel{
public:
  OperatingModel(crypter::Coder coder, CipherPadder* jammer);
  virtual ~OperatingModel() = 0;
public:
  virtual void encode_file() = 0 ;
  virtual void decode_file() = 0 ;

  void set_init_vector(std::vector<uchar> vector);
  void set_stream(std::istream* input_stream, std::ostream* output_stream);
  void set_input_stream(std::istream *input_stream);
  void set_output_stream(std::ostream *output_stream);

private:
  std::ostream* _output_stream ;
  std::istream* _input_stream ;
protected:
  std::vector<uchar> _init_vector;
  CipherPadder *_jammer = nullptr;
  crypter::Coder _coder;

  void read(std::vector<uchar> &buffer, int octets);
  void write(std::vector<uchar> &buffer);
  bool lastBlockReached();
};

#endif
