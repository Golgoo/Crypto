#ifndef __OPERATING_MODEL_HPP__
#define __OPERATING_MODEL_HPP__

#include <vector>
#include <string>

#include <fstream>
#include <memory>

typedef unsigned char uchar;

#include "Crypter/coder.hpp"
#include "Bourrage/Jammer.hpp"

#include <memory>

class OperatingModel{
public:
  OperatingModel(const std::string src_path, Jammer* jammer);
  virtual ~OperatingModel() = 0;
public:
  virtual void encode_file(const std::string dst_file, crypter::Encoder& encoder) = 0 ;
  virtual void decode_file(const std::string dst_file, crypter::Decoder& decoder) = 0 ;
  void set_init_vector(std::vector<uchar> vector);
private:
  std::ofstream *_output_stream = nullptr;
  std::ifstream *_input_stream = nullptr;
protected:
  std::vector<uchar> _init_vector;
  Jammer *_jammer = nullptr;
  void load_stream(const std::string);
  void read(std::vector<uchar> &buffer, int octets);
  void write(std::vector<uchar> &buffer);
  bool lastBlockReached();
};

#endif
