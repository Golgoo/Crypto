#include <iostream>
#include "Crypter/RSA/rsa.hpp"
#include "Crypter/AES/aes.hpp"
#include "Cipher/ecb_model.hpp"
#include "Crypter/coder.hpp"
#include "Padder/Jammer.hpp"
#include "Padder/PKCS_5.hpp"
#include "Cipher/cbc_model.hpp"
#include "Cipher/cfb_model.hpp"
#include "Cipher/ofb_model.hpp"
#include "Cipher/ecb_model.hpp"
#include "Crypter/dummy_coder.hpp"
#include "Crypter/coder.hpp"
#include <fstream>

int main(int argc, char*argv[])
{
  rsa::Key_Factory key_factory ;
  int precision = rsa::Key_Factory::createDefaultPrecision();
  rsa::RSA_Key _key = key_factory.createRandomKey(precision);
  std::cout << "RSA key : " << std::endl;
  rsa::display_key(_key);


  std::vector<uchar> init_v(16);
  std::fill(init_v.begin(), init_v.end(), 0x01);

  crypter::Encoder *rsa_encoder = new rsa::RSA(_key);
  crypter::Decoder *rsa_decoder = new rsa::RSA(_key);

  crypter::Coder coder(rsa_encoder, rsa_decoder);
  std::cout << "Programme 1" << std::endl;
  {
    if(argc < 2) return EXIT_FAILURE;
    Ofb_Model op_m (coder);
    op_m.set_init_vector(init_v);
    std::ifstream in_s(argv[1]);
    std::ofstream out_s("tmp.txt");
    op_m.set_stream(&in_s, &out_s);
    op_m.encode_file();
  }

  std::cout << "Programme 2" << std::endl;
  {
    if(argc < 3 ) return EXIT_FAILURE;
    std::ifstream in_s("tmp.txt");
    std::ofstream out_s(argv[2]);
    Ofb_Model op_m_d(coder);
    op_m_d.set_stream(&in_s, &out_s);
    op_m_d.decode_file();
  }

  delete rsa_encoder;
  delete rsa_decoder;

  return EXIT_SUCCESS;
}
