#include "aes.hpp"
#include "diversification.hpp"
#include "util.hpp"


#include <cstring>
#include <iostream>

using namespace AES ;

Encoder::Encoder(uchar * key, size_t key_len):AES(key, key_len)
{}
Encoder::Encoder(char * key):AES(key)
{}

void Encoder::encode(Block& current_state)
{
  int nbRound = keyExtender->getNbRound();
  int currentIndex = 0 ;
  uchar * currentRound = keyExtender->getExtendedKey();
  Block roundBlock(4, 4, currentRound);
//  Block subBlock(16, 16, crypt_util::SBox);
//  Block cBlock(4, 4, crypt_util::CBox);
  //crypt_util::XOR(current_state, currentRound, 16);
  current_state.XOR(roundBlock);

  for( currentIndex = 1 ; currentIndex < nbRound - 1 ; currentIndex ++)
  {
    //crypt_util::SubWord(current_state, 16);
    current_state.SubBlock(_SBlock);

    for(int i = 0 ; i < 4 ; i ++){
      current_state.rotate(i, i);
      //crypt_util::RotWord(current_state + i*4, 4, i);
    }
    //crypt_util::MixColumns(current_state);
    for(int c = 0 ; c < 4 ; c ++){
      current_state.MulCol(c, _CBlock);
    }
    currentRound += 16;
    roundBlock.setContent(currentRound);

    //    crypt_util::XOR(current_state, currentRound, 16);
    current_state.XOR(roundBlock);

  }
  //crypt_util::SubWord(current_state, 16);
  current_state.SubBlock(_SBlock);

  for(int i = 0 ; i < 4 ; i ++){
    //crypt_util::RotWord(current_state + i*4, 4, i);
    current_state.rotate(i, i);
  }

  currentRound += 16;
  roundBlock.setContent(currentRound);

//  crypt_util::XOR(current_state, currentRound, 16);
  current_state.XOR(roundBlock);
}

void write_bloc_into(Block& b, FILE *f)
{
  for(int c = 0 ; c < b.getCols() ; c++){
    for(int l = 0 ; l < b.getLine() ; l++){
      fputc(b.get(l, c), f);
    }
  }
}

void Encoder::encode_file(char * src_filename, char * dst_filename, Block &contentBlock2, bool concat_init_vector)
{
  FILE *f_src = fopen(src_filename, "r");
  FILE *f_dst = fopen(dst_filename, "w");



  if(f_src && f_dst) {

    /*if(concat_init_vector){
      write_bloc_into(contentBlock, f_dst);
    }*/

    uchar * content = (uchar*)malloc(sizeof(uchar) * 16);
    uchar buffer[16];
    for(int i = 0 ; i < 16 ; i ++) content [i] = 0x00 ;

    Block contentBlock(4,4, content);

    int nb_octets_lus = fread (buffer, 1, sizeof(buffer), f_src);
    while (nb_octets_lus == 16) {
      Block bufferBlock(4, 4, buffer);
      contentBlock.XOR(bufferBlock);
      //crypt_util::XOR(content, buffer, 16);
      //std::cout << "Contenu brut : " << std::endl;
      //contentBlock.printBlock();
      //crypt_util::print_key(content, 16);
      this->encode(contentBlock);
      //std::cout << "Contenu Chiffré : " << std::endl;
      //contentBlock.printBlock();
      //crypt_util::print_key(content, 16);
      //crypt_util::reverse(content, 4, 4);
      write_bloc_into(contentBlock, f_dst);
//      crypt_util::reverse(content, 4, 4);
      nb_octets_lus = fread (buffer, 1, sizeof(buffer), f_src);
    }

    //std::cout << "Left length : " << 16 - nb_octets_lus << std::endl ;
    /*if(nb_octets_lus == 0){
      crypt_util::fill(buffer, 16, 0xA0);
    }else{*/
      crypt_util::fill(buffer + nb_octets_lus, 16 - nb_octets_lus, 16 - nb_octets_lus);
    //}
    std::cout << "Bourrage :" << std::endl ;
    crypt_util::print_key(buffer, 16);

    Block lastBlock(4, 4, buffer);
    contentBlock.XOR(lastBlock);
//    crypt_util::XOR(content, buffer, 16);
  //  this->encode(content);
  //  crypt_util::reverse(content, 4, 4);
    //contentBlock.printBlock();
    write_bloc_into(contentBlock, f_dst);

    free(content);
  }
  if(f_src)
    fclose(f_src);
  if(f_dst)
    fclose(f_dst);
}
