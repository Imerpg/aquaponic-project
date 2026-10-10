#ifndef RECUPMODULE_H
#define RECUPMODULE_H

#include <iostream>

class recupModule
{
private:
    // Info imporatante
    char const * ip; // L'IP
    int port; // Le PORT

    // Info BDD
    const char * serveur = "127.0.0.1"; // L'url du serveur mariadb (phpmyadmin)
    const char * user;  // Login de connexion
    const char * password;   // Mot de passe de connexion
    const char * database;    // La Data Base (l'endroit ou sont stokées les tables)

    // Result 
    std::string result[7]; // Réponse en tableau

public:
    recupModule(char * IP, int PORT, const char * s, const char * u, const char * pwd, const char * db); // Lancement de la classe

    // Demmare la recuperation de données
    int startModule(); // Recupere les information
    void putInDB(); // Met le resultat dans la BDD

    ~recupModule();
};

#endif // RECUPMODULE_H