#include <iostream>
#include "Crypter/RSA/rsa.hpp"
#include "Crypter/AES/aes.hpp"
#include "OperatingModel/ecb_model.hpp"
#include "Crypter/coder.hpp"
#include "Bourrage/Jammer.hpp"
#include "Bourrage/PKCS_5.hpp"

int main(void)
{
  std::cout << "Programme 1" << std::endl;
  {
    crypter::Encoder *rsa_encoder = new rsa::RSA();
    Ecb_Model op_m ("in.txt");
    op_m.encode_file("out.txt", *rsa_encoder);
    delete rsa_encoder ;
  }

  Jammer * jam = new PKCS_5();

  std::cout << "Programme 2" << std::endl;
  {
    crypter::Decoder *rsa_decoder = new rsa::RSA();
    Ecb_Model op_m_d("out.txt");
    op_m_d.decode_file("decrypt.txt", *rsa_decoder);
    delete rsa_decoder;
  }

  return EXIT_SUCCESS;
}
