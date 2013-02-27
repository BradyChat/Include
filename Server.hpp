/** 
    20-02-2013
    Sanino Alessandro - Creazione

    27/02/2013
	Sanino Alessandro - Aggiunta Metodi

**/

#include "ChatAgent.hpp"
#include "ServerTCP.hpp"

class Server : ChatAgent {
	private:
	sealed override bool  Invia(char* Messaggio);
	sealed override char* Ricevi();
	ServerTCP *binary;

	public:
	Server(char* Ip, int Port);
	~Server();
}

bool Server::Invia(char* Messaggio) {
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

