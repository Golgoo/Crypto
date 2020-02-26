#ifndef __ECB_MODEL_HPP__
#define __ECB_MODEL_HPP__


#include "operating_model.hpp"

#include "Padder/stub_jam.hpp"

class Ecb_Model: public OperatingModel
{
public:
  Ecb_Model(crypter::Coder coder, Padder* jammer =  new StubJammer());
  ~Ecb_Model();

public:
  void encode_file() override;
  void decode_file() override;
};

#endif
