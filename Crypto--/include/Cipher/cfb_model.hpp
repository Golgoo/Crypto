#pragma once

#include "operating_model.hpp"

#include "Padder/stub_jam.hpp"

class Cfb_Model: public OperatingModel
{
public:
  Cfb_Model(crypter::Coder coder, Jammer* jammer = new StubJammer());
  ~Cfb_Model();

public:
  void encode_file() override;
  void decode_file() override;
};
