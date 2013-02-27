/**
    20-02-2013
    Sanino Alessandro - Create

    27-02-2013
	Sanino Alessandro - Aggiunta Metodi

**/

#ifndef CLIENT
#define CLIENT

#include "ChatAgent.hpp"
#include "ClientTCP.hpp"

class Client : ChatAgent {
	private:
	char* ServerIp;
	int ServerPort;
	ClientTCP *binary;

	public:
	sealed override bool Invia(char* Messaggio);
	sealed override char* Ricevi();

	Client(char* myIp, int myPort, char* ServerIp, int ServerPort);
	~Client();
}

Client::Client(char* myIp, int myPort, char* ServerIp, int ServerPort) : ChatAgent(myIp, myPort) {
	this->ServerIp = ServerIp;
	this->ServerPort = ServerPort;
}

Client::~Client() {
	free(this->ServerIp);
	delete(binary);
}

sealed override bool Client::Invia(char* Messaggio) {
	return this->binary->Invia(Messaggio);
}

sealed override char* Client::Ricevi() {
	return (this->binary->Ricevi());
}

#endif
