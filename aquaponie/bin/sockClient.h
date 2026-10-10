#ifndef SOCKCLIENT_H
#define SOCKCLIENT_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

class sockClient
{
private:
    // Definition des variable utile
	int sock;
	struct sockaddr_in sin;
	std::string server_reply;

    // Addresse 
    int port = 23;
    char const *ip = "127.0.0.1";

public:
    sockClient();

    // Change le port
    void setPort(int PORT);

    // Change l'ip
    void setIP(char const *IP);

    // Get Données
    std::string getServeur_reply();

    // Crée le socket
    int createSock(int MODE);

    // Envoie un message a l'hote distant
    void sendTo(char const *mess);

    // Recois un message de l'hote distant
    void recvTo();

    // GET seerveur reply nb octetr
    int getnbOctetsS();

    // Supprime le socket
    void deleteSock();

    ~sockClient();
};

#endif // sockClient_H