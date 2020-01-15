#ifndef __MINI_MIME_MAILER_H__
#define __MINI_MIME_MAILER_H__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstddef>

using namespace std ;

/*!
 * \file MiniMimeMailer.hpp
 * \brief Gestion de mail très simplifié
 * \author Gautier Maurice
 * \version 0.1
 */

 /*!
  * \class Mailer
  * \brief Classe permettant de gérer un email
  *
  * La classe permet de récupérer le corp d'un email, d'y ajouter un header et de récupérer la valeur d'un header
  */
class Mailer
{
  public :
  /*!
   *  \brief Constructeur
   *
   *  Constructeur de la classe Mailer
   *
   *  \param email_path : chemin vers l'email à traiter
   */
    Mailer(string email_path);
    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Mailer
     */
    ~Mailer();
  private :
    ifstream fxx ; /*< flux vers l'email*/
    string email_path ; /*< chemin vers l'email*/
  public :
  /*!
   *  \brief Lit le corp de l'email
   *
   *  Lit le corp de l'email passé au constructeur
   *
   *  \return le corp de l'email dans une string
   */
    std::string readCorpse();

    /*!
     *  \brief Ajoute un header à l'email
     *  \param name : nom du header
     *  \param value : valeur du header
     *
     *  Rajoute le champs à la fin des headers déjà présent.
     *  Cette fonction ne vérifie pas si le champs et déjà présent ou non.
     *  Le comportement sera toujours le même
     */
    void addHeader(string name, string value);
    /*!
     *  \brief Récupère la valeur d'un header d'un email
     *  \param field_name : nom du header
     *
     *
     *  \return une chaine correspondante ou une chaine non initialisée si le champ n'existe pas
     */
    string getHeaderValue(string field_name);
};


#endif
