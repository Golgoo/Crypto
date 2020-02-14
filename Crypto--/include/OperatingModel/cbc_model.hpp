#pragma once


#include "operating_model.hpp"

#include "Bourrage/stub_jam.hpp"

class Cbc_Model: public OperatingModel
{
public:
  Cbc_Model(const std::string src_path, Jammer* jammer =  new StubJammer());
  ~Cbc_Model();

public:
  void encode_file(const std::string dst_path, crypter::Encoder &encoder) override;
  void decode_file(const std::string dst_path, crypter::Decoder &decoder) override;
};
