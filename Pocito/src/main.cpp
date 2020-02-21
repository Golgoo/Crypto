#include <iostream>
#include <vector>

/** Lib **/
#include <cryptom>
/********/



typedef unsigned char uchar;
int main(int argc, char *argv[])
{
  //argv[1] -encode / -decode
  //TODO :: URGENT :: ENCODER => Supprimer src_path from constructor
                    // => ne pas travailler avec des string <=> path_src mais des streams E/S ( par défaut std::cout & std::cin)

  //AES_Key <- rand_vec( size = 16 )

  //RSA_Key <- Select RSA_Key from where it should be
  //Coder <- RSA(RSA_Key);
  //Jammer <- PKCS_1();
  //Jammer.jam(AES_Key.copy)
  //Coder.encode(AES_Key.copy)
  //out:stream << AES_Key.copy

  //Coder <- AES(AES_Key);
  //Jammer <- PKCS_5();
  //cbc_model block_cipher(Coder, Jammer);
  //Init-V <- rand_vec(size = 16)
  //out:stream << Init-V
  //block_cipher.encode_file(argv[2]:stream, out:stream);


  return EXIT_SUCCESS;
}
