#ifndef __OPERATING_MODEL_HPP__
#define __OPERATING_MODEL_HPP__

#include <vector>
#include <string>

#include <fstream>
#include <memory>

typedef unsigned char uchar;

#include "Crypter/coder.hpp"

class OperatingModel{
public:
  OperatingModel(const std::string src_path);
  virtual ~OperatingModel() = 0;
public:
  virtual void encode_file(const std::string dst_file, crypter::Encoder& encoder) = 0 ;
  virtual void decode_file(const std::string dst_file, crypter::Decoder& decoder) = 0 ;
private:
  std::ofstream *_output_stream = nullptr;
  std::ifstream *_input_stream = nullptr;
protected:
  void load_stream(const std::string);
  void read(std::vector<uchar> &buffer, int octets);
  void write(std::vector<uchar> &buffer);
};

#endif
