#pragma once

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Bourrage/PKCS_5.hpp"

typedef unsigned char uchar ;

class PKCS_5_Test : public CppUnit::TestCase
{
  public:
    CPPUNIT_TEST_SUITE( PKCS_5_Test );
      CPPUNIT_TEST( emptyVectorTest );
      CPPUNIT_TEST( fullVectorTest );
      CPPUNIT_TEST( normalVectorTest1 );
      CPPUNIT_TEST( normalVectorTest2 );
      CPPUNIT_TEST( toBigVectorTest );
      CPPUNIT_TEST( unjamEmpty );
      CPPUNIT_TEST( unjamFull );
      CPPUNIT_TEST( unjamNormal );
    CPPUNIT_TEST_SUITE_END();

  private:
    PKCS_5 pkcs_5_jam;

  public :
    void emptyVectorTest();
    void fullVectorTest();
    void normalVectorTest1();
    void normalVectorTest2();
    void toBigVectorTest();

    void unjamEmpty();
    void unjamFull();
    void unjamNormal();
};
