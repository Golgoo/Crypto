#pragma once

#include "Padder/Padder.hpp"

class CipherPadder: public Padder
{
public:
  CipherPadder();
  virtual ~CipherPadder();
};
