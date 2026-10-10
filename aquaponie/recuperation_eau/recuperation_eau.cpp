#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../bin/bddServeur.h"
#include <mysql/mysql.h>
#include <iostream>

int main()
{
    int res = 0; //Définition du niveau
	int gpio = 4; //Définition de la GPIO 
	wiringPiSetup(); //Initialisation
	//Met la gpio en resistance pull_up
	pinMode(gpio, PUD_UP);

	//Lecture de la GPIO
	res = digitalRead(gpio);
	if(res == 1)
	{
		printf("Niveau trop bas\n");
	}
	else if(res == 0)
	{
		printf("Niveau correct\n");
	}

    //Création d'une nouvelle instance "test"
    //Définition des paramètre de connexion à la base de donnée
    bddServeur test("127.0.0.1", "admin", "Aquaponie", "aquaponie");

    //Connexion
    test.connectBDD();

    //Récupère dans connect la connexion à la BDD
    MYSQL *connect = test.getConnexion();
    //Variable qui va récupérer la requete SQL
    char niveau[1000];
    //On écrit dans la variable niveau la requête SQL
    sprintf(niveau, "INSERT INTO capteur_eau (ACTIF) VALUES (%d)\n", res);

    mysql_query(connect, niveau); //Envoi de la requête 
    mysql_errno(connect); //Si erreur détecté

    test.stopBDD(); //Fermeture connexion 
}