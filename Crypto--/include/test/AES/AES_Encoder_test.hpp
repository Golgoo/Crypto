#pragma once

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Crypter/AES/aes.hpp"

typedef unsigned char uchar ;

class AES_Encoder_Test : public CppUnit::TestCase
{
  public:
    CPPUNIT_TEST_SUITE( AES_Encoder_Test );
      CPPUNIT_TEST( TP_Test );
      CPPUNIT_TEST( Butokuden );
    CPPUNIT_TEST_SUITE_END();

  public :
    void TP_Test();
    void Butokuden();
};
