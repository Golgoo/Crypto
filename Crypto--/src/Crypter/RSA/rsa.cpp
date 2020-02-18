#include "Crypter/RSA/rsa.hpp"

using namespace rsa;

RSA::RSA(RSA_Key key):_key(key), crypter::Encoder(), crypter::Decoder()
{
  mpz_init(_mpz_block);
}

RSA::~RSA()
{
  mpz_clear(_mpz_block);
}

#include <Util/util.hpp>
#include <iostream>
#include <iomanip>

void RSA::convert_vector_into_mpz(mpz_t& mpz_dst, std::vector<uchar>& src_vector)
{
  std::stringstream ss;
  for(uchar bite : src_vector){
    ss << std::setfill('0') << std::setw(2)
              << std::uppercase << std::hex
              << (int)bite ;
  }
  mpz_set_str(mpz_dst, ss.str().c_str(), 16);
}

void RSA::convert_mpz_into_vector(std::vector<uchar>& dst_vector, mpz_t& mpz_src)
{
  dst_vector.clear();
  int mpz_size =  mpz_sizeinbase(mpz_src, 16);
  char *str = (char*)malloc(sizeof(char) * mpz_size);
  mpz_get_str(str, 16, mpz_src);
  if(mpz_size % 2 == 1){
    uchar c = convert::CharToHex(str[0]);
    dst_vector.push_back(c);
  }
  for(int i = (mpz_size%2) ; i < mpz_size ; i += 2){
    uchar c = convert::CharToHex(str[i]);
    c = c * 16 ;
    c += convert::CharToHex(str[i+1]);
    dst_vector.push_back(c);
  }
  free(str);
}

//#define NDEBUG
#include <cassert>

void RSA::encode(std::vector<uchar> &block)
{
  std::cout << "Start of Encoding -------------------------"<<std::endl;
  std::cout << "Input block : " << std::endl;
  out::display_block(block);
  convert_vector_into_mpz(_mpz_block, block);
  std::cout << "Input converted into Mpz : " << std::endl;
  gmp_printf("%ZX\n",_mpz_block);

  mpz_powm(_mpz_block, _mpz_block, _key.e, _key.n);
  std::cout << "Size of encoder : " << mpz_sizeinbase(_mpz_block, 16) << std::endl;
  std::cout << "Mpz_Encoded : " << std::endl;
  gmp_printf("%ZX\n",_mpz_block);

  convert_mpz_into_vector(block, _mpz_block);
  std::cout << "Block_encoded" << block.size() << std::endl;
  out::display_block(block);

  std::cout << "End of Encoding -------------------------"<<std::endl;
}

void RSA::decode(std::vector<uchar> &block)
{

  convert_vector_into_mpz(_mpz_block, block);

  mpz_powm(_mpz_block, _mpz_block, _key.d, _key.n);

  convert_mpz_into_vector(block, _mpz_block);
  //out::display_block(block);
}
