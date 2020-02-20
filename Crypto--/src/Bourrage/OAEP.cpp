#include "Bourrage/OAEP.hpp"

OAEP::OAEP()
{

}

OAEP::~OAEP()
{

}


std::vector<uchar> lHash =
{
  0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55, 0xbf, 0xef, 0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09
};


#include "Util/util.hpp"
#include <cassert>
#include <iostream>
std::vector<uchar> OAEP::MGF(std::vector<uchar>& seed, size_t final_length)
{
  assert(final_length < 0xFF);
  std::vector<uchar> v(0), tmp;
  std::vector<uchar> concat(seed);
  concat.resize(concat.size() + 4);

  int index = 0 ;
  while(v.size() < final_length){
    concat[23] = index;
    tmp = hash::_SHA1(concat);
    v.insert(v.end(), tmp.begin(), tmp.end());
    std::cout << "Vector size : " << v.size() << std::endl;
    index ++ ;
  }
  v.resize(final_length);
  return v;
}

void OAEP::jam(std::vector<uchar> &vector, size_t block_size)
{

  assert(block_size == 128 && vector.size() <= 86);
  vector.insert(vector.begin(), 0x01);
  int ps_length = 128 - ( vector.size() + 1 + 20);
  std::vector<uchar> ps(ps_length) ;
  vector.insert(vector.begin(), ps.begin(), ps.end());
  vector.insert(vector.begin(), lHash.begin(), lHash.end());
  vector.insert(vector.begin(), 0x00);
  std::vector<uchar> seed(20);
  std::vector<uchar> transformed = MGF(seed, 107);
  operation::XOR(vector, transformed);
  transformed = MGF(vector, 20);
  operation::XOR(seed, transformed);
  vector.insert(vector.begin(), seed.begin(), seed.end());
  vector.insert(vector.begin(), 0x00);
}

void OAEP::unjam(std::vector<uchar> &vector)
{
  assert(vector.size() == 128 && vector.at(0) == 0x00);

  vector.erase(vector.begin());
}
