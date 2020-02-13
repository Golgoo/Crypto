#pragma once

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Bourrage/PKCS_1.hpp"

typedef unsigned char uchar ;

class PKCS_1_Test : public CppUnit::TestCase
{
  public:
    CPPUNIT_TEST_SUITE( PKCS_1_Test );
      CPPUNIT_TEST( emptyVectorTest );
      CPPUNIT_TEST( fullVectorTest );
      CPPUNIT_TEST( normalVectorTest );
      CPPUNIT_TEST( toBigVectorTest );
      CPPUNIT_TEST( unjamEmpty );
      CPPUNIT_TEST( unjamFull );
      CPPUNIT_TEST( unjamNormal );
    CPPUNIT_TEST_SUITE_END();

  private:
    PKCS_1 pkcs_1_jam;

  public :
    void emptyVectorTest();
    void fullVectorTest();
    void normalVectorTest();
    void toBigVectorTest();

    void unjamEmpty();
    void unjamFull();
    void unjamNormal();
};
