#pragma once

#include "Bourrage/Jammer.hpp"

typedef unsigned char uchar ;

class StubJammer : public Jammer
{
public:
  StubJammer();
  ~StubJammer();
  void jam(std::vector<uchar> &vector, size_t block_size) override;
  void unjam(std::vector<uchar> &vector) override;
};
