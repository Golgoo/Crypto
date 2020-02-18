#include <iostream>
#include "Crypter/RSA/rsa.hpp"
#include "Crypter/AES/aes.hpp"
#include "OperatingModel/ecb_model.hpp"
#include "Crypter/coder.hpp"
#include "Bourrage/Jammer.hpp"
#include "Bourrage/PKCS_5.hpp"

int main(int argc, char*argv[])
{
  rsa::RSA_Key _key ;
  crypter::Encoder *rsa_encoder = new rsa::RSA(_key);
  crypter::Decoder *rsa_decoder = new rsa::RSA(_key);
  crypter::Coder coder(rsa_encoder, rsa_decoder);

  std::cout << "Programme 1" << std::endl;
  {
    Ecb_Model op_m (argv[1], coder);
    op_m.encode_file("tmp.txt");
    delete rsa_encoder ;
  }


  //std::cout << "Programme 2" << std::endl;
  {
    Ecb_Model op_m_d("tmp.txt", coder);
    op_m_d.decode_file(argv[2]);
    delete rsa_decoder;
  }

  return EXIT_SUCCESS;
}
