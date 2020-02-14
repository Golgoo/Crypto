#ifndef __ECB_MODEL_HPP__
#define __ECB_MODEL_HPP__


#include "operating_model.hpp"

#include "Bourrage/stub_jam.hpp"

class Ecb_Model: public OperatingModel
{
public:
  Ecb_Model(const std::string src_path, Jammer* jammer =  new StubJammer());
  ~Ecb_Model();

public:
  void encode_file(const std::string dst_path, crypter::Encoder &encoder) override;
  void decode_file(const std::string dst_path, crypter::Decoder &decoder) override;
};

#endif
