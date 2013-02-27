/**
    20-02-2013
    Sanino Alessandro - Create

    27-02-2013
	Sanino Alessandro - Aggiunta Metodi

**/

class ChatAgent {
	private:
	char* myIp;
	int myPort;
	virtual bool Invia(char* Messaggio) { }
	virtual char* Ricevi() { return null; }

	public:
	ChatAgent(char* Ip, int port);
	~ChatAgent();
}

ChatAgent::ChatAgent(char* Ip, int Port) {
	this->myIp = Ip;
	this->myPort = Port;
}

ChatAgent::~ChatAgent() {
	free(this->myIp);
}
