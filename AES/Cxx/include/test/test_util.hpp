#ifndef __TEST_UTIL_HPP__
#define __TEST_UTIL_HPP__


#include "util.hpp"

#include <cstdlib>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>


typedef unsigned char uchar ;

class testCryptUtil : public CppUnit::TestCase
{
  /** Implémentation auto de la fonction CppUnit::TestSuite* suite(); */
  // <=> Créer la liste de test
  public:
    CPPUNIT_TEST_SUITE( testCryptUtil );
      CPPUNIT_TEST( correctXORTest );
      CPPUNIT_TEST( incorrectXORTest );
      CPPUNIT_TEST( RotWordTest );
      CPPUNIT_TEST( SubWordTest );
      CPPUNIT_TEST( SubByteTest );
      CPPUNIT_TEST( ShiftRowsTest );
      CPPUNIT_TEST( ShiftRowsTest2 );
      CPPUNIT_TEST( ShiftRowsTestTP );
      CPPUNIT_TEST( MixColumnsTest );
      CPPUNIT_TEST( ReverseTest );
      CPPUNIT_TEST( ReverseTest2 );
    CPPUNIT_TEST_SUITE_END();

  public :
  /*** Implémentation des tests **/
    void correctXORTest(){
      uchar a [] = {0x2A, 0x09, 0xFF};
      uchar b [] = {0x1B, 0xC0, 0x0D};
      crypt_util::XOR(a, b, 3);
      CPPUNIT_ASSERT_EQUAL((int)a[0], 0x31);
      CPPUNIT_ASSERT_EQUAL((int)a[1], 0xC9);
      CPPUNIT_ASSERT_EQUAL((int)a[2], 0xF2);
    }
    void incorrectXORTest(){
      uchar a [] = {0x2B, 0x09, 0xFF};
      uchar b [] = {0x1B, 0xC0, 0x0D};
      crypt_util::XOR(a, b, 3);
      CPPUNIT_ASSERT((int)a[0] != 0x31);
    }
    void RotWordTest(){
      uchar a [] = {0x00, 0x01, 0x02, 0x03};
      crypt_util::RotWord(a, 4);
      CPPUNIT_ASSERT_EQUAL((int)a[0], 0x01);
      CPPUNIT_ASSERT_EQUAL((int)a[1], 0x02);
      CPPUNIT_ASSERT_EQUAL((int)a[2], 0x03);
      CPPUNIT_ASSERT_EQUAL((int)a[3], 0x00);
    }
    void SubWordTest(){
      uchar a [] = {0x00, 0x12, 0x2A, 0x10};
      crypt_util::SubWord(a, 4);
      CPPUNIT_ASSERT_EQUAL((int)a[0], 0x63);
      CPPUNIT_ASSERT_EQUAL((int)a[1], 0xC9);
      CPPUNIT_ASSERT_EQUAL((int)a[2], 0xE5);
      CPPUNIT_ASSERT_EQUAL((int)a[3], 0xCA);
    }
    void SubByteTest(){
      uchar a [] = {0x00, 0x12, 0x2A, 0x10,
                    0x00, 0x12, 0x2A, 0x10,
                    0x00, 0x12, 0x2A, 0x10,
                    0x00, 0x12, 0x2A, 0x10};
      crypt_util::SubWord(a, 16);
      CPPUNIT_ASSERT_EQUAL((int)a[0], 0x63);
      CPPUNIT_ASSERT_EQUAL((int)a[1], 0xC9);
      CPPUNIT_ASSERT_EQUAL((int)a[2], 0xE5);
      CPPUNIT_ASSERT_EQUAL((int)a[3], 0xCA);
      CPPUNIT_ASSERT_EQUAL((int)a[8], 0x63);
      CPPUNIT_ASSERT_EQUAL((int)a[5], 0xC9);
      CPPUNIT_ASSERT_EQUAL((int)a[14], 0xE5);
      CPPUNIT_ASSERT_EQUAL((int)a[7], 0xCA);
    }
    void SubByteTPTest(){
      uchar a [] = {0x00, 0x00, 0x00, 0x00,
                    0x01, 0x01, 0x01, 0x01,
                    0x02, 0x02, 0x02, 0x02,
                    0x03, 0x03, 0x03, 0x03};
      crypt_util::SubWord(a, 16);
      CPPUNIT_ASSERT_EQUAL((int)a[0], 0x63);
      CPPUNIT_ASSERT_EQUAL((int)a[4], 0x7C);
      CPPUNIT_ASSERT_EQUAL((int)a[8], 0x77);
      CPPUNIT_ASSERT_EQUAL((int)a[12], 0x7B);
    }
    void ShiftRowsTest(){
      uchar a [] = {0x00, 0x00,
                    0x01, 0x01};
      crypt_util::RotWord(a + 1, 3, 2);
      CPPUNIT_ASSERT_EQUAL((int)a[1], 0x01);
      CPPUNIT_ASSERT_EQUAL((int)a[2], 0x00);
      CPPUNIT_ASSERT_EQUAL((int)a[3], 0x01);
    }
    void ShiftRowsTest2(){
      uchar a [] = {0x00, 0x00,
                    0x01, 0x01};
      crypt_util::RotWord(a + 0, 4, 3);
      CPPUNIT_ASSERT_EQUAL((int)a[0], 0x01);
      CPPUNIT_ASSERT_EQUAL((int)a[1], 0x00);
      CPPUNIT_ASSERT_EQUAL((int)a[2], 0x00);
      CPPUNIT_ASSERT_EQUAL((int)a[3], 0x01);
    }
    void ShiftRowsTestTP(){
      uchar a [] = {0xA0, 0xA1, 0xA2, 0xA3,
                    0xB0, 0xB1, 0xB2, 0xB3,
                    0xC0, 0xC1, 0xC2, 0xC3,
                    0xD0, 0xD1, 0xD2, 0xD3};
      crypt_util::RotWord(a + 0, 4, 0);
      crypt_util::RotWord(a + 4, 4, 1);
      crypt_util::RotWord(a + 8, 4, 2);
      crypt_util::RotWord(a + 12, 4, 3);
      uchar expected[] = {0xA0, 0xA1, 0xA2, 0xA3,
                            0xB1, 0xB2, 0xB3, 0xB0,
                            0xC2, 0xC3, 0xC0, 0xC1,
                            0xD3, 0xD0, 0xD1, 0xD2};
      char message [] = "Indice 00\0";
      for(int i = 0 ; i < 16 ; i ++){
        sprintf(message, "Indice %d", i);
        CPPUNIT_ASSERT_EQUAL_MESSAGE(message, (int)expected[i], (int)a[i]);
      }
    }
    void MixColumnsTest(){
      uchar a[] = {
        0x0E, 0x0B, 0x0D, 0x09,
        0x09, 0x0E, 0x0B, 0x0D,
        0x0D, 0x09, 0x0E, 0x0B,
        0x0B, 0x0D, 0x09, 0x0E
      };
      uchar expected[] = {
        0x01, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x01
      };
      crypt_util::MixColumns(a);
      char message [] = "Indice 00\0";
      for(int i = 0 ; i < 16 ; i ++){
        sprintf(message, "Indice %d", i);
        CPPUNIT_ASSERT_EQUAL_MESSAGE(message, (int)expected[i], (int)a[i]);
      }
    }
    void ReverseTest(){
      uchar a[] = {
        0x62, 0x63, 0x63, 0x63,
        0x62, 0x63, 0x63, 0x63,
        0x62, 0x63, 0x63, 0x63,
        0x62, 0x63, 0x63, 0x63
      };
      uchar expected[] = {
        0x62, 0x62, 0x62, 0x62,
        0x63, 0x63, 0x63, 0x63,
        0x63, 0x63, 0x63, 0x63,
        0x63, 0x63, 0x63, 0x63
      };
      crypt_util::reverse(a, 4, 4);
      char message[] = "Indice 00\0";
      for(int i = 0 ; i < 16 ; i ++){
        sprintf(message, "Indice %d", i);
        CPPUNIT_ASSERT_EQUAL_MESSAGE(message, (int)expected[i], (int)a[i]);
      }
    }
    void ReverseTest2(){
      uchar a[] = {
        0x62, 0x63, 0x63,
        0x62, 0x63, 0x63,
        0x62, 0x63, 0x63,
        0x62, 0x63, 0x63
      };
      uchar expected[] = {
        0x62, 0x62, 0x62, 0x62,
        0x63, 0x63, 0x63, 0x63,
        0x63, 0x63, 0x63, 0x63
      };
      crypt_util::reverse(a, 4, 3);
      char message[] = "Indice 00\0";
      for(int i = 0 ; i < 12 ; i ++){
        sprintf(message, "Indice %d", i);
        CPPUNIT_ASSERT_EQUAL_MESSAGE(message, (int)expected[i], (int)a[i]);
      }
    }

};

#endif
