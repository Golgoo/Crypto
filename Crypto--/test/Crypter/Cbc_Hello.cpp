#include <iostream>
#include "Crypter/RSA/rsa.hpp"
#include "Crypter/AES/aes.hpp"
#include "OperatingModel/ecb_model.hpp"
#include "Crypter/coder.hpp"
#include "Bourrage/Jammer.hpp"
#include "Bourrage/PKCS_5.hpp"
#include "OperatingModel/cbc_model.hpp"

int main(int argc, char*argv[])
{

  std::cout << "Programme 1" << std::endl;
  {
    if(argc < 1) return EXIT_FAILURE;
    crypter::Encoder *rsa_encoder = new rsa::RSA();
    Cbc_Model op_m (argv[1]);
    std::vector<uchar> init_r(16);
    std::fill(init_r.begin(), init_r.end(), 0xDD);
    op_m.set_init_vector(init_r);
    op_m.encode_file("tmp.txt", *rsa_encoder);
    delete rsa_encoder ;
  }

/*
  std::cout << "Programme 2" << std::endl;
  {
    crypter::Decoder *rsa_decoder = new rsa::RSA();
    Ecb_Model op_m_d("tmp.txt");
    op_m_d.decode_file(argv[2], *rsa_decoder);
    delete rsa_decoder;
  }
*/
  return EXIT_SUCCESS;
}
