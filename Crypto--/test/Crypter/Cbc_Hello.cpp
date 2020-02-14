#include <iostream>
#include "Crypter/RSA/rsa.hpp"
#include "Crypter/AES/aes.hpp"
#include "OperatingModel/ecb_model.hpp"
#include "Crypter/coder.hpp"
#include "Bourrage/Jammer.hpp"
#include "Bourrage/PKCS_5.hpp"
#include "OperatingModel/cbc_model.hpp"
#include "OperatingModel/cfb_model.hpp"

int main(int argc, char*argv[])
{
  crypter::Encoder *rsa_encoder = new rsa::RSA();
  crypter::Decoder *rsa_decoder = new rsa::RSA();

  crypter::Coder coder(rsa_encoder, rsa_decoder);
  std::cout << "Programme 1" << std::endl;
  {
    if(argc < 2) return EXIT_FAILURE;
    Cfb_Model op_m (argv[1], coder);
    std::vector<uchar> init_r(16);
    std::fill(init_r.begin(), init_r.end(), 0x00);
    op_m.set_init_vector(init_r);
    op_m.encode_file("tmp.txt");
  }

  std::cout << "Programme 2" << std::endl;
  {
    if(argc < 3 ) return EXIT_FAILURE;
    Cfb_Model op_m_d("tmp.txt", coder);
    op_m_d.decode_file(argv[2]);
  }

  delete rsa_encoder;
  delete rsa_decoder;

  return EXIT_SUCCESS;
}
