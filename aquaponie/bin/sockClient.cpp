#include <iostream>
#include <errno.h>
#include <string.h>
#include "sockClient.h"

using namespace std;

// Demmarage du Socket
sockClient::sockClient()
{
    cout << "sockClient 1.0" << endl;
}

// Crée le socket
int sockClient::createSock(int MODE)
{
    // Crée le socket
    // Mode 1 = UDP
    // Mode 0 = TCP
    if(MODE == 1)
    {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
    } else if (MODE == 0) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
    }
    // Met en place les parametre
    sin.sin_addr.s_addr = inet_addr (ip);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

    // Tente une connection
    cout << "Tentative de connexion a l'ip : " << ip << ':' << port << " ..." << endl;

    bind(sock, (struct sockaddr *) &sin, sizeof (sin));

    if (connect (sock, (struct sockaddr *) &sin,sizeof (sin)) < 0)
    {
        cout << "ERROR : Connexion echoue " << errno << " ..." << endl;
        return 0;
        
    } else {
        cout << "Connecter ..." << endl;
        return 1;
    }
}

// Envoie
void sockClient::sendTo(char const *mess)
{
    // Si il n'est pas envoyer
    if (send (sock, mess, strlen (mess), 0) >= 0)
	{
		cout << "Message '" << mess << "' , recus avec succes a l'addresse : " << ip << ":" << port << " ..." << endl;
	} else {
        cout << "ERROR : Message non envoyer ..." << endl;
    }
}

// Recois
void sockClient::recvTo()
{
    char server_reply_char[50];
    // Si il n'est pas recue
	if ( recv (sock, server_reply_char, sizeof(server_reply_char),0) >= 0)
	{ 
        server_reply = server_reply_char;
		cout << "Message recu '"<< server_reply_char << "' ..." << endl;
	} else {
        cout << "ERROR : Recv failed cause " << errno << endl;
    }
    int size = server_reply.size();
}

// Ferme le socket
void sockClient::deleteSock()
{
    // Supprime le socket
    close(sock);
}

// Change le Port
void sockClient::setPort(int PORT)
{
    port = PORT;
}

// Change l'IP
void sockClient::setIP(char const *IP)
{
    ip = IP;
}

// Renvoie la reponse du serveur
string sockClient::getServeur_reply()
{
    return server_reply;
}

// Renvoie la taille de la reponse du serveur
int sockClient::getnbOctetsS()
{
    return server_reply.size();
}

sockClient::~sockClient() {}