#ifndef __AES_HPP__
#define __AES_HPP__

#include <vector>
#include "Crypter/coder.hpp"

namespace aes{

  typedef unsigned char uchar ;

  class KeyExtender{
  public:
    KeyExtender(std::vector<uchar> key);
    ~KeyExtender();

  public:
    std::vector<uchar> getRound(int roundIndex) const;
    std::vector<std::vector<uchar>> getRounds() const;
    int getNbRounds() const;
  private:
    std::vector<std::vector<uchar>> _rounds;
    int _key_len;
    int _Nk, _Nr ;
  private:
    void init_Ns();
    void computeExtendedKey();
  };

  class Block{
  private:
    int _lines, _columns ;
    std::vector<std::vector<uchar>*>* _matrix;
  public:
    Block(int l, int c, uchar *tab);
    Block(int lines, int cols);
    Block(int l, int c, std::vector<uchar> tab);
    ~Block();
    void rotate(int line, int shift);
    void set(int l, int c, uchar v);
    uchar get(int l, int c) const;
    uchar getAt(int index) const;
    void XOR(const Block& other);
    void MulCol(int c, const Block& other);
    void SubBlock(const Block& other);
    void setContent(uchar *tab);
    void setContent(std::vector<uchar> tab);
    void printBlock();
    void write_into_vector(std::vector<uchar> &vector);
    inline int getLine() const { return _lines; } ;
    inline int getCols() const { return _columns; } ;
  };

  class AES : public crypter::Encoder, public crypter::Decoder
  {
  public:
    AES(std::vector<uchar> key);
    ~AES();

  private:
    KeyExtender * _key_extender = nullptr;
    Block _SBlock;
    Block _CBlock;
    Block _InvCBlock;
    Block _InvSBlock;
  public:
    void encode(std::vector<uchar>& block) override ;
    void decode(std::vector<uchar>& block) override ;
  };

};


#endif
