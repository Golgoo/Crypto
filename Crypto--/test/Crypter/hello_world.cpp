#include <iostream>
#include "Crypter/RSA/rsa.hpp"
#include "Crypter/AES/aes.hpp"
#include "OperatingModel/ecb_model.hpp"
#include "Crypter/coder.hpp"
#include "Bourrage/Jammer.hpp"
#include "Bourrage/PKCS_5.hpp"

int main(int argc, char*argv[])
{

  std::cout << "Programme 1" << std::endl;
  {
    crypter::Encoder *rsa_encoder = new rsa::RSA();
    Ecb_Model op_m (argv[1]);
    op_m.encode_file("tmp.txt", *rsa_encoder);
    delete rsa_encoder ;
  }


  std::cout << "Programme 2" << std::endl;
  {
    crypter::Decoder *rsa_decoder = new rsa::RSA();
    Ecb_Model op_m_d("tmp.txt");
    op_m_d.decode_file(argv[2], *rsa_decoder);
    delete rsa_decoder;
  }

  return EXIT_SUCCESS;
}