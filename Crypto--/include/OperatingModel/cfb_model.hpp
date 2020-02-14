#pragma once

#include "operating_model.hpp"

#include "Bourrage/stub_jam.hpp"

class Cfb_Model: public OperatingModel
{
public:
  Cfb_Model(const std::string src_path, crypter::Coder coder, Jammer* jammer = new StubJammer());
  ~Cfb_Model();

public:
  void encode_file(const std::string dst_path) override;
  void decode_file(const std::string dst_path) override;
};
