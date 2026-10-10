#ifndef BDDSERVEUR_H
#define BDDSERVEUR_H

#include <iostream>
#include <mysql/mysql.h>

class bddServeur
{
private:
    // Initialisation de la varable permetant de stoker la conexion a la BDD
    MYSQL *con = mysql_init(NULL);

    // Variable de connection a la BDD
    char const *serveur;
    char const *user;
    char const *password;
    char const *dataBase;

public:

    bddServeur(char const * s, char const *u, char const *pwd, char const *db);

    // Se connecte a la BDD
    void connectBDD();

    // Déconnecter de la BDD
    void stopBDD();

    // Get con
    MYSQL *getConnexion();

    ~bddServeur();

};
#endif // BDDSERVEUR_H