// -*- coding: utf-8 -*-

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LG_FLUX
#define LG_FLUX 10
#endif
// Ce programme ne produira par défaut que les 10 premiers octets de la clef longue.

typedef unsigned char uchar; // Les octets sont non-signés.

//uchar clef[]={0x01, 0x02, 0x03, 0x04, 0x05};
uchar clef[] = {'K', 'Y', 'O', 'T', 'O'};

uchar state[256];
int i, j;
void initialisation(void);
uchar production(void);

int main(void)
{
  initialisation();      // Phase d'initialisation de l'état du système RC4
  FILE *input = fopen("butokuden.jpg","r");
  FILE *output = fopen("confidential.jpg", "w");
  if(!input || !output){
    printf("Impossible d'ouvrir / usage\n");
    exit(1);
  }
  printf("Premiers octets de la clef longue : ");
  int readed_int ;
  while((readed_int = fgetc(input)) != EOF){
    uchar product = production();
    printf("0x%02X ", product);  // Affichage d'un octet produit en hexadécimal
    uchar c = readed_int;
    printf("0x%02X ", c);
    fputc(c^product, output);
    printf("\n");
  }

  printf("\n");
  exit(EXIT_SUCCESS);
}


void echange (uchar *state, int i, int j)
{
  uchar temp = state[i];
  state[i] = state[j];
  state[j] = temp;
}

void initialisation(void)
{
  int lg = sizeof(clef);
  printf("Clef courte utilisée : ");
  for (int k = 0; k < lg ; k++ ) printf ("0x%02X ", clef[k]);
  printf("\nLongueur de la clef courte : %d\n",lg);
  for (i=0; i < 256; i++) state[i] = i;

  j = 0;
  for (i=0; i < 256; i++) {
    j = (j + state[i] + clef[i % lg]) % 256;
    echange(state,i,j);           // Echange des octets en i et j
  }
  i=0;
  j=0;
}

uchar production(void)
{
  i = (i + 1) % 256;            // Incrémentation de i modulo 256
  j = (j + state[i]) % 256;     // Déplacement de j
  echange(state,i,j);           // Echange des octets en i et j
  return state[(state[i] + state[j]) % 256];
}


/* 1er test avec la clef 12345
  $ make
  gcc -o mon_RC4 -I/usr/local/include -I/usr/include mon_RC4.c -L/usr/local/lib
  -L/usr/lib -lm -lssl -lcrypto -g -Wall
  $ ./mon_RC4
  Clef courte utilisée : 0x01 0x02 0x03 0x04 0x05
  Longueur de la clef courte : 5
  Premiers octets de la clef longue : 0xB2 0x39 0x63 0x05 0xF0 0x3D 0xC0 0x27 0xCC 0xC3
*/

/* 2nd test avec la clef "KYOTO"
  $ make
  gcc -o mon_RC4 -I/usr/local/include -I/usr/include mon_RC4.c -L/usr/local/lib
  -L/usr/lib -lm -lssl -lcrypto -g -Wall
  $ ./mon_RC4
  Clef courte utilisée : 0x4B 0x59 0x4F 0x54 0x4F
  Longueur de la clef courte : 5
  Premiers octets de la clef longue : 0x8C 0xE5 0x01 0xB4 0xD3 0xDF 0x6B 0xA7 0x41 0x0D
*/
