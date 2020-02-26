#pragma once

#include "Padder/Padder.hpp"

typedef unsigned char uchar ;

class StubJammer : public Padder
{
public:
  StubJammer();
  ~StubJammer();
  void jam(std::vector<uchar> &vector, size_t block_size) override;
  void unjam(std::vector<uchar> &vector) override;
};
