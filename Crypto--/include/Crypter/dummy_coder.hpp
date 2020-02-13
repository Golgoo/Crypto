#pragma once

#include <vector>

#include "Crypter/coder.hpp"

typedef unsigned char uchar;


class DummyCoder: public crypter::Encoder, public crypter::Decoder
{
public:
  DummyCoder();
  ~DummyCoder();
public:
  void encode(std::vector<uchar> &block) override ;
  void decode(std::vector<uchar> &block) override ;
};
