#include <iostream>
#include "bddServeur.h"
#include "sockClient.h"

using namespace std;

//Paramétrage de la BDD
bddServeur::bddServeur(char const * s, char const *u, char const *pwd, char const *db) 
: serveur(s), user(u), password(pwd), dataBase(db)
{
    cout << "BDDServeur 1.0" << endl;
}

// Connection a la base de données 
void bddServeur::connectBDD()
{
    // Verifie qu'il arrive bien a se connecter 
    if(!mysql_real_connect(con, serveur, user, password, dataBase, 0, NULL, 0))
    {
        cout << "ERROR : Echec de la connection " << mysql_errno(con) << " ..." << endl;
    } else {
        cout << "Connexion etablie avec " << serveur << " ..." << endl;
    }
}

// Get connexion
MYSQL* bddServeur::getConnexion()
{
    return con; //Retourne la connexion (mysql_real_connect)
}

// Se deconnecte de la BDD
void bddServeur::stopBDD()
{
    mysql_close(con);
}

bddServeur::~bddServeur()
{
    
}