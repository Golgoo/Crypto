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
    virtual int decode_length() const = 0 ;
  };

  class Encoder{
  public:
    Encoder();
    virtual ~Encoder() = 0 ;
    virtual void encode(std::vector<uchar> &block) = 0 ;
    virtual int encode_length() const = 0 ;
  };

  class Coder{
  public:
    Coder(Encoder* encoder, Decoder* decoder);
    inline void encode(std::vector<uchar> &block) { _encoder->encode(block); };
    inline void decode(std::vector<uchar> &block) { _decoder->decode(block); };
    inline int encode_length() const {return _encoder->encode_length(); } ;
    inline int decode_length() const {return _decoder->decode_length(); } ;
  private:
    Encoder *_encoder;
    Decoder *_decoder;
  };
};
