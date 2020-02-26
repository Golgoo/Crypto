#pragma once

#include "Padder/CipherPadder.hpp"

typedef unsigned char uchar ;

class StubJammer : public CipherPadder
{
public:
  StubJammer();
  ~StubJammer();
  void jam(std::vector<uchar> &vector, size_t block_size) override;
  void unjam(std::vector<uchar> &vector) override;
};
