#pragma once

#include "operating_model.hpp"

#include "Bourrage/stub_jam.hpp"

class Ofb_Model: public OperatingModel
{
public:
  Ofb_Model(const std::string src_path, crypter::Coder coder, Jammer* jammer =  new StubJammer());
  ~Ofb_Model();

public:
  void encode_file(const std::string dst_path) override;
  void decode_file(const std::string dst_path) override;
};
