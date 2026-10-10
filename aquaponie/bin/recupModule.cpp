#include <iostream>
#include <string>
#include "sockClient.h"
#include "bddServeur.h"
#include "recupModule.h"

using namespace std;

recupModule::recupModule(char * IP, int PORT, const char * s, const char * u, const char * pwd, const char * db)
: ip(IP), port(PORT), serveur(s), user(u), password(pwd), database(db) {
        // Met les parametre en place
}

int recupModule::startModule()
{
    // Lance le socket
    sockClient sock;

    // Configure le socket
    sock.setIP(ip);
    sock.setPort(port);

    // Demare le socket
    int res = sock.createSock(0);

    // Si le sock a bien demmarer
    if (res == 1)
    {
        // Envoie le signal
        sock.sendTo("OK");

        // Recois la trame (nom_module, table_1, valeur_1, actif, table_2, valeur_2, actif, ' ')
        sock.recvTo();

        // Ecrit la trame (dev)
        // cout <<sock.getServeur_reply() << endl;

        // Met la fonction dans une variable
        string rep = sock.getServeur_reply();

        // La taille de la variable
        int rep_size = sock.getnbOctetsS();

        // Ecrit la taille de la variable (dev)
        //cout << "NB d'octet : " << rep_size << endl; 

        // Declare un char array
        char char_array[rep_size + 1];

        // Passe la variable qui recupere la valeur
        strcpy(char_array, sock.getServeur_reply().c_str());
        // La définitions de séparateurs connus.
        const char * separators = " ";

        // On cherche à récupérer, un à un, tous les mots (token) de la phrase
        // et on commence par le premier.
        int i = 0;
        char * strToken = strtok ( char_array, separators );
        for(int i = 0; i < 7; i++ ) {
            // On le stocke dans le tableau result
            result[i] = strToken;
            // On demande le token suivant.
            strToken = strtok ( NULL, separators );
        }
        // Fermeture du socket
        sock.deleteSock();
        // Lance la suite du programme
        putInDB();
        return 0;
    }
    // ERREUR
    return 11;
}

void recupModule::putInDB()
{
    // Appel de la classe
    bddServeur bdd(serveur, user, password, database);

    // Connecte
    bdd.connectBDD();
    
    // Recupere la connection a la bdd
    MYSQL * con = bdd.getConnexion();

    // Met en place le res et les rows
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Sert a stoker le valeur des deux capteurs
    char req[1000];
    string v1, v2;
    string m1, m2;
    string id1, id2;

    // Definie les variable selon les capteurs
    if(result[1] == "TEMPERATURE" && result[4] == "OXYGENE") {
        m1 = "temperature";
        id1 = "ID_TEMP";
        m2 = "oxygene";
        id2 = "ID_OXY";
    } else {
        m2 = "condutivite";
        id2 = "ID_COND";
        m1 = "ph";
        id1 = "ID_PH";
    }

    sprintf(req, "INSERT INTO %s (%s, ACTIF) VALUES (%s, %s)", m1.c_str(), result[1].c_str(), result[2].c_str(), result[3].c_str());
    cout << "Requete : " << req << endl;
    // Lance la requete
    mysql_query(con, req);

    sprintf(req, "INSERT INTO %s (%s, ACTIF) VALUES (%s, %s)", m2.c_str(), result[4].c_str(), result[5].c_str(), result[6].c_str());
    cout << "Requete : " << req << endl;
    mysql_query(con, req);

    // Recupere le identifiant des module et des valeur dernierement aquise
    // Met en place les 2 variable qui stocke les donnés des capteurs (oxy, temp ou ph, conduct)
    // Recupere les 2 valeur
    // Insere les deux valeur des deux capteurs
    sprintf(req, "SELECT %s FROM %s ORDER BY DATE DESC", id1.c_str(), m1.c_str());
    cout << "Requete : " << req << endl;
    mysql_query(con, req);

    // Envois le resultat dans res
    res = mysql_use_result(con);

    // Affiche ligne par ligne 
    row = mysql_fetch_row(res);
    v1 = row[0];

    // Met le res a 0
    mysql_free_result(res);

    // Recommence
    sprintf(req, "SELECT %s FROM %s ORDER BY DATE DESC", id2.c_str(), m2.c_str());
    cout << "Requete : " << req << endl;
    mysql_query(con, req);
    res = mysql_use_result(con);
    row = mysql_fetch_row(res);
    v2 = row[0];
    mysql_free_result(res);

    // Prend id du module
    sprintf(req, "SELECT ID_N_MODULE FROM nom_module WHERE IP = '%s'", ip);
    cout << "Requete : " << req << endl;
    mysql_query(con, req);
    res = mysql_use_result(con);
    row = mysql_fetch_row(res);

    // Prend la premiere valeur (ID)
    string m = row[0];
    mysql_free_result(res);

    // Choisi le module que c'est en fonction de la trame
    if(result[1] == "TEMPERATURE" && result[4] == "OXYGENE")
    {
        cout << "MODULE ID : " << m << ", VALEUR1 ID : " << v1 << ", VALEUR2 ID : " << v2 << endl;
        sprintf(req, "INSERT INTO h_module_bassin (ID_N_MODULE, ID_TEMP, ID_OXY) VALUES (%s, %s, %s)", m.c_str(), v1.c_str(), v2.c_str());
        cout << "Requete : " << req << endl;
        mysql_query(con, req);
    } else {
        cout << "MODULE ID : " << m << ", VALEUR1 ID : " << v1 << ", VALEUR2 ID : " << v2 << endl;
        sprintf(req, "INSERT INTO h_module_puisard (ID_N_MODULE, ID_PH, ID_CONDUCTIVITE) VALUES (%s, %s, %s)", m.c_str(), v1.c_str(), v2.c_str());
        cout << "Requete : " << req << endl;
        cout << mysql_errno(con) << endl;
        mysql_query(con, req);
    } // ICI on peut rajouter d'autre types de module

    // Stope la BDD
    bdd.stopBDD();
    // Stoppe la classe
    bdd.~bddServeur();
}

recupModule::~recupModule() {}