// -*- coding: utf-8 -*-

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;

uchar SBox[256] = {
  0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
  0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
  0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
  0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
  0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
  0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
  0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
  0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
  0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
  0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
  0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
  0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
  0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
  0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
  0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
  0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};
// Table de substitution

uchar Rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 } ;
// Constantes de ronde

uchar K[32] = {                          // Une clef courte a une longueur maximale de 32 octets
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } ;

uchar W[240];                  // La longueur maximale de W est (14+1)*16=240 octets

int longueur_de_la_clef, longueur_de_la_clef_etendue, Nk, Nr;

void affiche_la_clef(uchar *clef, int longueur)
{
  for (int i=0; i<longueur; i++) { printf ("%02X ", clef[i]); }
  printf("\n");
}

//https://stackoverflow.com/questions/33982870/how-to-convert-char-array-to-hexadecimal
uchar CharToHex( char c )
{
    switch( c ) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': case 'A': return 10;
        case 'b': case 'B': return 11;
        case 'c': case 'C': return 12;
        case 'd': case 'D': return 13;
        case 'e': case 'E': return 14;
        case 'f': case 'F': return 15;
    }
    return 16;
}

void calcule_la_clef_courte(char * clef_en_hexa){ // À modifier !
  int length = strlen(clef_en_hexa);
  uchar a, b ;
  for(int i = 0, j = 0 ; i < length ; i += 2, j++ ){
    a = CharToHex(clef_en_hexa[i]);
    b = CharToHex(clef_en_hexa[i + 1]);
    if(a > 15 || b > 15){
      fprintf(stderr,"La clée doit être saisie en hexédécimale :\n");
      if(a > 15){
        fprintf(stderr, "%c", clef_en_hexa[i]);
      }
      if(b > 15){
        fprintf(stderr, "%c", clef_en_hexa[i+1]);
      }
      fprintf(stderr, " n'est pas en hexadécimale\n");
      exit(EXIT_FAILURE);
    }
    K[j] = a << 4 ;
    K[j] += b ;
  }
}

void RotWord(uchar *tab);
void SubWord(uchar *tab);
void XorRCon(uchar *tab, int index);
void XorW(uchar *target, int index);

void calcule_la_clef_etendue() { // À modifier !
  if (longueur_de_la_clef == 16){
    Nr = 10; Nk = 4;
  } else if (longueur_de_la_clef == 24){
    Nr = 12; Nk = 6;
  } else {
    Nr = 14; Nk = 8;
  }
  longueur_de_la_clef_etendue = 4*(4*(Nr+1));
  uchar tmp[4] = {0x00, 0x00 ,0x00 ,0x00};
  for(int i = 0 ; i < longueur_de_la_clef ; i ++){
    W[i] = K[i];
  }
  affiche_la_clef(W , 16);
  for(int i = longueur_de_la_clef ; i < longueur_de_la_clef_etendue * 4 ; i+= 4)
  {
    printf("\n------------\n");
    int index = i / 4 ;
    printf("index : %d - i : %d\n", index, i);
    for(int j = 0 ; j < 4 ; j ++){
      tmp[j] = W[(i-4) + j];
    }
    printf("Clée tmp init : ");
    affiche_la_clef(tmp , 4);
    if( (index)%Nk == 0 ) {
      printf("\nCase i % Nk == 0\n");
      RotWord(tmp);
      printf("After RotWord : ");
      affiche_la_clef(tmp , 4);
      SubWord(tmp);
      printf("After SubWord : ");
      affiche_la_clef(tmp , 4);
      XorRCon(tmp, (index)/Nk - 1);
      printf("After XorRCon : ");
      affiche_la_clef(tmp, 4);
    }else if(Nk > 6 && (index)%Nk == 4){
      SubWord(tmp);
    }

    XorW(tmp, (index - Nk) * 4);
    printf("After XorW : ");
    affiche_la_clef(tmp , 4);
    for(int j = 0 ; j < 4 ; j ++){
      W[i + j] = tmp[j];
    }
  }
}

void RotWord(uchar *tab)
{
  uchar tmp ;
  tmp = tab[0];
  for(int i = 0 ; i < 3 ; i ++){
    tab[i] = tab[i+1];
  }
  tab[3] = tmp ;
}

void SubWord(uchar *tab)
{
  for(int i = 0 ; i < 4 ; i ++){
    tab[i] = SBox[tab[i]];
  }
}

void XorRCon(uchar *tab, int index){
  tab[0] ^= Rcon[index];
}

void XorW(uchar *tab, int index){
  printf("Index for XorW : %d\n", index);
  for(int i = 0 ; i < 4 ; i ++){
    tab[i] ^= W[index + i];
  }
}

int main(int argc, char* argv[])
{
  if(argc !=2){
    printf("Usage: %s <clef en hexadécimal>", argv[0]);
    exit(EXIT_FAILURE);
  }
  longueur_de_la_clef = strlen(argv[1]) >> 1; // Il faut 2 caractères hexadécimaux pour un octet
  if((longueur_de_la_clef != 16) && (longueur_de_la_clef != 24) && (longueur_de_la_clef != 32)){
    printf("Usage: %s clef en hexadécimal (formée de 128, 192 ou 256 bits)\n", argv[0]);
    printf("\t Une clef AES est formée de 32, 48, ou 64 caractères hexadécimaux,\n");
    printf("\t c'est-à-dire 128, 192, ou 256 bits.\n");
    exit(EXIT_FAILURE);
  }

  calcule_la_clef_courte(argv[1]);            // Fonction à écrire pour récupérer la clef courte
  calcule_la_clef_etendue();                    // Fonction à écrire pour compléter le programme

  affiche_la_clef(W, longueur_de_la_clef_etendue);
  exit(EXIT_SUCCESS);
}

/* 2nd test à effectuer
   $ make
   gcc diversification.c -o diversification
   $ ./diversification 2b7e151628aed2a6abf7158809cf4f3c
   La clef est : 2B 7E 15 16 28 AE D2 A6 AB F7 15 88 09 CF 4F 3C
   Les clefs de rondes sont :
   RoundKeys[00] =  2B  7E  15  16  28  AE  D2  A6  AB  F7  15  88  09  CF  4F  3C
   RoundKeys[01] =  A0  FA  FE  17  88  54  2C  B1  23  A3  39  39  2A  6C  76  05
   RoundKeys[02] =  F2  C2  95  F2  7A  96  B9  43  59  35  80  7A  73  59  F6  7F
   RoundKeys[03] =  3D  80  47  7D  47  16  FE  3E  1E  23  7E  44  6D  7A  88  3B
   RoundKeys[04] =  EF  44  A5  41  A8  52  5B  7F  B6  71  25  3B  DB  0B  AD  00
   RoundKeys[05] =  D4  D1  C6  F8  7C  83  9D  87  CA  F2  B8  BC  11  F9  15  BC
   RoundKeys[06] =  6D  88  A3  7A  11  0B  3E  FD  DB  F9  86  41  CA  00  93  FD
   RoundKeys[07] =  4E  54  F7  0E  5F  5F  C9  F3  84  A6  4F  B2  4E  A6  DC  4F
   RoundKeys[08] =  EA  D2  73  21  B5  8D  BA  D2  31  2B  F5  60  7F  8D  29  2F
   RoundKeys[09] =  AC  77  66  F3  19  FA  DC  21  28  D1  29  41  57  5C  00  6E
   RoundKeys[10] =  D0  14  F9  A8  C9  EE  25  89  E1  3F  0C  C8  B6  63  0C  A6
*/
