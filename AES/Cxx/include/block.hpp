#ifndef __BLOCK_H__
#define __BLOCK_H__

typedef unsigned char uchar ;

#include <vector>

using namespace std;

class Block{
private:
  int _lines, _columns ;
  vector<vector<uchar>*>* _matrix;


public:
  Block(int l, int c, uchar *tab);
  Block(int lines, int cols);
  ~Block();
  void rotate(int line, int shift);
  void set(int l, int c, uchar v);
  uchar get(int l, int c) const;
  uchar getAt(int index) const;
  void XOR(const Block& other);
  void MulCol(int c, const Block& other);
  void SubBlock(const Block& other);
  void setContent(uchar *tab);
  void printBlock();
  inline int getLine() const { return _lines; } ;
  inline int getCols() const { return _columns; } ;
};

#endif
