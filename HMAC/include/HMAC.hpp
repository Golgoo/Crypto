#ifndef __HMAC_H__
#define __HMAC_H__

#include <stdio.h>
#include <cstddef>
#include <vector>
#include <string>
#include <openssl/md5.h>

using namespace std;


/*!
 * \file HMAC.hpp
 * \brief Générateur de HMAC basique
 * \author Gautier Maurice
 * \version 0.1
 */

 /*!
  * \class HMAC
  * \brief Classe permettant de générer des HMAC de différentes façons
  *
  * La classe permet de générer des HMAC en suivant la méthode présentée en TP ( MD5_sum(<secret>.<corp>) ),
  * ou bien en suivant la norme RFC_2104
  */
class HMAC{
  public :
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe HMAC
     *
     *  \param content : contenue à hacher
     */
    HMAC(std::string content);
  private :
    string content ; /*!< contenu à hacher */
    string hashed_secret ; /*! < secret pour le hachage */

    MD5_CTX md5_ctx; /*!< contexte MD5 */
    std::string final_bytes /*!< hachage final*/;

  private:
    /*!
     *  \brief hache une string
     *
     *  Methode qui permet de hacher une string via la fonction MD5_Sum
     *
     *  \param str : la chaîne à hacher
     *  \return le hache correspondant à cette chaîne
     */
    string hash_string(std::string str);
    /*!
     *  \brief hache le secret
     *
     *  \param secret : le secret à hasher
     *  Appelle la fonction hash_string et stocke le résultat dans le champ privé 'hashed_secret'
     */
    void hash_secret(std::string secret);
    /*!
     *  \brief Initialise le contexte MD5
     *
     *  initialise le contexte MD5 suivant la bibilothèque dans <openssl/md5.h>
     */
    void init_MD5();
    /*!
     *  \brief Concatène une chaine à la fin du contenu final
     *  \param str : chaîne à concaténer
     *  Concatène à la chaîne privée final_bytes la chaine str.
     */
    void append(string str);

    /*!
     *  \brief Rempli une chaîne en suivant un motif précis
     *  \param str : adresse vers la chaîne à remplir
     *  \param size : taille que doit atteindre la chaine à la fin de la fonction
     *  \param motif : chaîne utilisée pour remplir str.
     *
     *  Suposons n <=> taille de str et s taille du motif
     *  pour i : n -> size ; i+= s
     *  --- concaténer motif à str.
     */
    void fill(string* str, size_t size, string motif);
  public :

    /*!
     *  \brief retourne un hachage simplifié
     *  \param secret : secret utilisé pour le hachage
     *
     *  s <=> secret ; c <=> content
     *  h(s,c) = MD5(c.MD5(s));
     *
     *  \return le hachage correspondant
     */
    string get_soft_hash(std::string secret);
    /*!
     *  \brief retourne un hachage respectant la norme RFC_2104
     *  \param secret : secret utilisé pour le hachage
     *
     *  s <=> secret ; c <=> content
     *  X <=> Xor
     *  opad <=> 0x5c 0x5c .... 0x5c (64 octets)
     *  ipad <=> 0x36 0x36 .... 0x36 (64 octets)
     *  h(s,c) = MD5( (MD5(s)Xopad). MD5( (MD5(s)Xipad).c ) );
     *
     *  \return le hachage correspondant
     */
    string get_RFC_2104_hash(std::string secret);
};

#endif
