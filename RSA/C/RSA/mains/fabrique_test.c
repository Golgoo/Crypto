#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(void)
{
  mpz_t code, code_chiffre, code_dechiffre ;
  mpz_inits(code, code_chiffre, code_dechiffre, (void*)NULL);
  mpz_set_str(code, "4b594f544f", 16);

  /* Affichage du code clair à l'aide de la fonction gmp_printf() */
  gmp_printf("Code clair        : %Zd\n", code);

  int log_4_precision = m_log("1000000000000000", 10, "4");
  rsa_key_s rsa_key = fabrique_RFC_4871(log_4_precision);

  /* Affichage des clefs utilisées à l'aide de la fonction gmp_printf() */
  gmp_printf("Clef publique (n) : %Zd\n", rsa_key.n);
  gmp_printf("Clef publique (e) : %Zd\n", rsa_key.e);
  gmp_printf("Clef privée (d)   : %Zd\n", rsa_key.d);

  /* On effectue d'abord le chiffrement RSA du code clair avec la clef publique */
  mpz_powm(code_chiffre, code, rsa_key.e, rsa_key.n);                    // Calcul du code chiffré
  gmp_printf("Code chiffré      : %Zd\n", code_chiffre);

  /* On déchiffre ensuite avec la clef privée */
  mpz_powm(code_dechiffre, code_chiffre, rsa_key.d, rsa_key.n);        // Calcul du code déchiffré
  gmp_printf("Code déchiffré    : %Zd\n", code_dechiffre);
  mpz_clears(code, code_chiffre, code_dechiffre);

}
