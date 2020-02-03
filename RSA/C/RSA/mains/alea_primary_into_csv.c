
#include "util.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
  int log_4_precision = m_log("1000000000000000", 10, "4");
  clock_t t1 ;
  gmp_randstate_t alea;
  gmp_randinit_default(alea);
  gmp_randseed_ui(alea, time(NULL));
  mpz_t x;
  mpz_init(x);
  FILE *csv_f = fopen("csv_alea_gen.csv","w");
  if(csv_f){
    fprintf(csv_f,";ExecTime(ms);NbTentatives;valeur\n");
  }
  char res [1024];
  int moy_tentative = 0;
  float moy_temps = 0 ;

  int nb_tentative ;
  float temps ;
  int nombre_d_essai = 10;
  for(int i = 0 ; i < nombre_d_essai ; i ++){
    t1 = clock();
    nb_tentative = trouve_nombre_premier(alea, &x, 512, log_4_precision);
    temps = (float)(clock() - t1)/(CLOCKS_PER_SEC / 1000 );
    if(csv_f){
      gmp_sprintf(res,"%Zd", x);
      fprintf(csv_f,"essaie%d;%f;%d;%s\n", i, temps, nb_tentative, res);
    }
    moy_tentative += nb_tentative ;
    moy_temps += temps ;
  }
  if(csv_f){
    fprintf(csv_f, "moy;%f;%d;\n", moy_temps/(float)nombre_d_essai, moy_tentative/nombre_d_essai );
    fclose(csv_f);
  }

  mpz_clear(x);
}
