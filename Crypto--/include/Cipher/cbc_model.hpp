#pragma once


#include "operating_model.hpp"

#include "Padder/stub_jam.hpp"

class Cbc_Model: public OperatingModel
{
public:
  Cbc_Model(crypter::Coder coder, CipherPadder* jammer =  new StubJammer());
  ~Cbc_Model();

public:
  void encode_file() override;
  void decode_file() override;
};
