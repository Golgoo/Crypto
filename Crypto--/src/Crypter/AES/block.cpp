#include "Crypter/AES/aes.hpp"

#include <algorithm>
#include "Util/util.hpp"

using namespace aes;

Block::Block(int lines, int cols, uchar *tab):_lines(lines), _columns(cols)
{
  _matrix = new std::vector<std::vector<uchar>*>(lines);
  for(int l = 0 ;  l < lines ; l ++){
    (*_matrix)[l] = new std::vector<uchar>(cols);
    for(int c = 0 ; c < cols ; c ++){
      (*(*_matrix)[l])[c] = tab[l + c*cols];
    }
  }
}

Block::Block(int lines, int cols):_lines(lines), _columns(cols)
{
  _matrix = new std::vector<std::vector<uchar>*>(lines);
  for(int l = 0 ;  l < lines ; l ++){
    (*_matrix)[l] = new std::vector<uchar>(4);
    for(int c = 0 ; c < cols ; c ++){
      (*(*_matrix)[l])[c] = 0x00;
    }
  }
}

Block::Block(int lines, int cols, std::vector<uchar> tab):_lines(lines), _columns(cols)
{
  _matrix = new std::vector<std::vector<uchar>*>(lines);
  for(int l = 0 ;  l < lines ; l ++){
    (*_matrix)[l] = new std::vector<uchar>(cols);
    for(int c = 0 ; c < cols ; c ++){
      (*(*_matrix)[l])[c] = tab[l + c*cols];
    }
  }
}

Block::~Block()
{
  for (auto line : *_matrix){
      delete line;
  }
  delete _matrix;
}

void Block::rotate(int line, int shift)
{
  std::rotate((*_matrix)[line]->begin(), (*_matrix)[line]->begin() + shift, (*_matrix)[line]->end());
}

void Block::set(int l, int c, uchar v)
{
  (*(*_matrix)[l])[c] = v;
}
uchar Block::get(int l, int c) const
{
  return (*(*_matrix)[l])[c];
}

uchar Block::getAt(int index) const
{
  return (*(*_matrix)[index%_columns])[index/_lines];
}

void Block::XOR(const Block& other)
{
  for(int l = 0 ; l < _lines ; l ++){
    for(int c = 0 ; c < _columns ; c ++){
      (*(*_matrix)[l])[c] ^= other.get(l, c);
    }
  }
}

void Block::MulCol(int c, const Block& other)
{
  std::vector<uchar> tmp(_lines);
  for(int l = 0 ; l < _lines ; l ++){
    for(int tc = 0 ; tc < _columns ; tc++){
      tmp[l] ^= operation::gmul((*(*_matrix)[tc])[c], other.get(l, tc));
    }
  }
  for(int l = 0 ; l < _lines ; l++){
    (*(*_matrix)[l])[c] = tmp[l];
  }
}


void Block::SubBlock(const Block& other)
{
  for(int l = 0 ; l < _lines ; l ++){
    for(int c = 0 ; c < _columns ; c++){
      (*(*_matrix)[l])[c] = other.getAt((*(*_matrix)[l])[c]);
    }
  }
}

void Block::setContent(uchar *tab)
{
  for (auto line : *_matrix){
      delete line;
  }
  for(int l = 0 ;  l < _lines ; l ++){
    (*_matrix)[l] = new std::vector<uchar>(_columns);
    for(int c = 0 ; c < _columns ; c ++){
      (*(*_matrix)[l])[c] = tab[l + c*_columns];
    }
  }
}

void Block::setContent(std::vector<uchar> tab)
{
  for (auto line : *_matrix){
      delete line;
  }
  for(int l = 0 ;  l < _lines ; l ++){
    (*_matrix)[l] = new std::vector<uchar>(_columns);
    for(int c = 0 ; c < _columns ; c ++){
      (*(*_matrix)[l])[c] = tab[l + c*_columns];
    }
  }
}

void Block::write_into_vector(std::vector<uchar> &vector)
{
  vector.resize(_lines * _columns);
  for(int l = 0 ; l < _lines ; l ++){
    for(int c = 0 ; c < _columns ; c ++){
      vector[l + c*_columns] = (*(*_matrix)[l])[c];
    }
  }
}

#include <iostream>
#include <iomanip>
void Block::printBlock()
{
  std::cout << std::uppercase << std::hex ;
  for(int i = 0 ; i < _lines ; i ++){
    for(int j = 0 ; j < _columns ; j ++){
      std::cout << std::setfill('0') << std::setw(2)<< (int)get(i, j) << ' ';
    }
    std::cout << std::endl ;
  }
}
