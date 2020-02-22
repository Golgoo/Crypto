#pragma once

#include "operating_model.hpp"

#include "Padder/stub_jam.hpp"

class Ofb_Model: public OperatingModel
{
public:
  Ofb_Model(crypter::Coder coder, Jammer* jammer =  new StubJammer());
  ~Ofb_Model();

public:
  void encode_file() override;
  void decode_file() override;
};
