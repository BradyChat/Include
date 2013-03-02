/** 
    20-02-2013
    Sanino Alessandro - Creazione

    27-02-2013
    Sanino Alessandro - Aggiunta Metodi

    02-03-2013
    Samuele Bonino - Correzione libreria

**/

#ifndef SERVER
#define SERVER

#include "ChatAgent.hpp"
#include "SocketTCP.hpp"

class Server : ChatAgent {
	private:
        override bool  Invia(char* Messaggio);
        override char* Ricevi();
	ServerTCP *binary;

	public:
	Server(char* Ip, int Port);
	~Server();
};

override bool Server::Invia(char* Messaggio) {
	return (this->binary->Invia(Messaggio));
}

char* Server::Ricevi() {
	return (this->binary->Ricevi());
}


void Server::Accetta() {
	this->binary->Accetta();
}
    
Server::Server(char* Ip, int Port) : ChatAgent(Ip, Port) {
	this->binary = new ServerTCP(Ip, Port);
}

Server::~Server() {
	delete(binary);
}


#endif
