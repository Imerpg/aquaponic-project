#include <iostream>
#include "../bin/recupModule.h"
#include "../bin/bddServeur.h"
#include <time.h>
#include <unistd.h>

using namespace std;

int main()
{
    // Variable utiles
    bddServeur serveur("127.0.0.1", "admin", "Aquaponie", "aquaponie");
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Connecte le serveur
    serveur.connectBDD();

    // Recupere la varable qui contient la connexion
    MYSQL *con = serveur.getConnexion();

    // Lui demande tout les IP qui sont actif
    mysql_query(con, "SELECT IP FROM nom_module");

    // Prend les valeur
    res = mysql_use_result(con);
    int i = 0;
    // Prend les ligne
    MYSQL_ROW ip;

    // Chaque ligne il recommence jusqu'a ce qu'il n'y en ai plus
    while (row = mysql_fetch_row(res))
    {
        // Appelle la classe
        recupModule recup(row[0], 3000, "127.0.0.1", "admin", "Aquaponie", "aquaponie");
        cout << "ok" << endl;
        // Lance la classe avec une verification d'erreur
        int ok = recup.startModule();

        // Si l'erreur est 11 alors met le Actif a 0 de l'IP traiter
        MYSQL *con2 = mysql_init(NULL);
        mysql_real_connect(con2, "127.0.0.1", "admin", "Aquaponie", "aquaponie", 0, NULL, 0);
        char req[1000];
        if (ok == 11)
        {
            sprintf(req, "UPDATE nom_module SET ACTIF = 0 WHERE IP = '%s'", row[0]);
            cout << req << endl;
            if (mysql_query(con2, req))
            {
                cout << mysql_errno(con) << endl;
            }
        } else {
            sprintf(req, "UPDATE nom_module SET ACTIF = 1 WHERE IP = '%s'", row[0]);
            cout << req << endl;
            if (mysql_query(con2, req))
            {
                cout << mysql_errno(con) << endl;
            }
        }
        mysql_close(con2);
        i++;
        recup.~recupModule();
    }

    serveur.stopBDD();

    serveur.~bddServeur();

    return 0;
}