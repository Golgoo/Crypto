#include "Crypter/dummy_coder.hpp"


DummyCoder::DummyCoder(): crypter::Encoder(), crypter::Decoder()
{

}

DummyCoder::~DummyCoder()
{

}

void DummyCoder::encode(std::vector<uchar> &block)
{
  
}

void DummyCoder::decode(std::vector<uchar> &block)
{

}
