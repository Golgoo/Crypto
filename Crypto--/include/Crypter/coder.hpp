#pragma once

#include <vector>
typedef unsigned char uchar;

namespace crypter
{
  class Decoder{
  public:
    Decoder();
    virtual ~Decoder() = 0 ;
    virtual void decode(std::vector<uchar> &block) = 0 ;
  };

  class Encoder{
  public:
    Encoder();
    virtual ~Encoder() = 0 ;
    virtual void encode(std::vector<uchar> &block) = 0 ;
  };
};
