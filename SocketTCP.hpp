/*
 * SocketTCP.hpp
 * This file is part of vallaurisoft
 *
 * Copyright (C) 2013 - gnuze
 *
 * vallaurisoft is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * vallaurisoft is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vallaurisoft. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef SOCKETTCP_HPP
#define SOCKETTCP_HPP

#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "str.h"

#include "Address.hpp"
#include "Lista.hpp"

#define  MAX_CONNECTIONS	50

// Connessione

class Connessione: public Nodo {
private:
	int		_conn_id;
	void	foo() {}
public:
	Connessione(int);
	~Connessione();
	
	bool	invia(char* msg);
	char*	ricevi();
	void	close();
	void	show();	
};

Connessione::Connessione(int conn_id):Nodo(NULL) {	this->_conn_id=conn_id;}
Connessione::~Connessione() {}

bool	Connessione::invia(char* msg) {
	int		ret_code;
	int		len;
	
	len = len_str(msg)+1;
	ret_code = send(this->_conn_id,msg,len,0);
	return  (ret_code == len);
}

char*	Connessione::ricevi() {
	int		ret_code;
	char	buffer[MAX_STR+1];

	ret_code = recv(this->_conn_id,buffer,MAX_STR,0);
	if (ret_code==0)
		return NULL;
	
	buffer[ret_code]= '\0';	

	return cpy_str(buffer);
}	

void	Connessione::close() {	::close(this->_conn_id); }
void	Connessione::show()  {	printf("conn_id=%d\n",_conn_id); }

// ServerTCP

class ServerTCP {
private:
	Lista* 	_connessioni;
	int		_sock_id;
public:
	ServerTCP(char*, int);
	ServerTCP(Address*);
	~ServerTCP();

	Connessione*	accetta();
	Connessione*	accetta(Address*);
	bool			invia_a_tutti(char* msg);
	void			close_all();
};

ServerTCP::ServerTCP(char* ip, int port) {
	struct sockaddr_in binary;
	int					len_binary;

	this->_connessioni = new Lista();
	this->_sock_id = socket(AF_INET, SOCK_STREAM, 0);


	binary.sin_family=AF_INET;
	inet_aton(ip, &(binary.sin_addr));
	binary.sin_port=htons(port);
	for (int i=0; i<8;i++)
		binary.sin_zero[i]=0;
	len_binary = sizeof (struct sockaddr);


	bind(this->_sock_id, (struct sockaddr*) &binary, (socklen_t) len_binary);
	listen(this->_sock_id, MAX_CONNECTIONS);
}

ServerTCP::ServerTCP(Address* address) {
	struct sockaddr_in* binary;
	int					len_binary;

	this->_connessioni = new Lista();
	this->_sock_id = socket(AF_INET, SOCK_STREAM, 0);
	listen(this->_sock_id, MAX_CONNECTIONS);

	binary = address->get_binary(); 
	len_binary = sizeof (struct sockaddr);

	bind(this->_sock_id, (struct sockaddr*) binary, (socklen_t) len_binary);
	free(binary);
}

ServerTCP::~ServerTCP() {
	this->_connessioni->destroy(); 
}

Connessione*	ServerTCP::accetta() {
	struct 	sockaddr_in binary;
	int					len_binary;
	int					ret_code;
	Connessione*		ret;

	len_binary = sizeof (struct sockaddr_in);
	ret_code = accept(this->_sock_id, (struct sockaddr*) &binary, (socklen_t*) &len_binary);

	ret = new Connessione(ret_code);
	this->_connessioni->add(ret);
	return ret;
}

Connessione*	ServerTCP::accetta(Address* address) {
	struct sockaddr_in binary;
	int					len_binary;
	int					ret_code;

	len_binary = sizeof (struct sockaddr_in);
	ret_code = accept(this->_sock_id, (struct sockaddr*) &binary, (socklen_t*) &len_binary);
	this->_connessioni->add(new Connessione(ret_code));
	address->set_binary(binary);
}

bool			ServerTCP::invia_a_tutti(char* msg) {
	Iterator* 	it;
	bool		flag;

	for ( 	it = this->_connessioni->create_Iterator(), flag=true;
			flag && it->is_done();
			it->move_next() ) {
		Connessione* tmp = (Connessione*) it->get_current();
		flag =  tmp->invia(msg) ;
	}

	delete it;
	return flag;
}

void			ServerTCP::close_all() {
	Iterator* it;
	
	for ( 	it = this->_connessioni->create_Iterator();
			it->is_done();
			it->move_next() ) {
		Connessione* tmp = (Connessione*) it->get_current();
		tmp->close();
	}

	delete it;
}

// ClientTCP

class ClientTCP {
private:
	int		_sock_id;
public:
	ClientTCP();
	ClientTCP(char*,int);
	ClientTCP(Address*);
	~ClientTCP();
	
	bool	connetti(char*,int);
	bool	connetti(Address*);

	bool	invia(char* msg);
	char*	ricevi();
	bool	close_connection();		
};

ClientTCP::ClientTCP() {	this->_sock_id = socket(AF_INET, SOCK_STREAM, 0); }

ClientTCP::ClientTCP(char* ip,int port) {
	struct sockaddr_in binary;
	int					len_binary;

	this->_sock_id = socket(AF_INET, SOCK_STREAM, 0);

	binary.sin_family=AF_INET;
	inet_aton(ip, &(binary.sin_addr));
	binary.sin_port=htons(port);
	for (int i=0; i<8;i++)
		binary.sin_zero[i]=0;
	len_binary = sizeof (struct sockaddr);

	bind(this->_sock_id, (struct sockaddr*) &binary, (socklen_t) len_binary);
}

ClientTCP::ClientTCP(Address* address) {
	struct sockaddr_in* binary;
	int					len_binary;

	this->_sock_id = socket(AF_INET, SOCK_STREAM, 0);

	binary = address->get_binary(); 
	len_binary = sizeof (struct sockaddr);

	bind(this->_sock_id, (struct sockaddr*) binary, (socklen_t) len_binary);
	free(binary);
}

ClientTCP::~ClientTCP() {	this->_sock_id = socket(AF_INET, SOCK_STREAM, 0); }
	
bool	ClientTCP::connetti(char*ip,int port) {
	int		ret_code;
	struct sockaddr_in* binary;
	Address address(ip,port);

	binary = address.get_binary();

	ret_code = ::connect(	this->_sock_id,
							(struct sockaddr*)binary,
							(socklen_t)sizeof(struct sockaddr) );



	free(binary);

	return (ret_code==0);
}

bool	ClientTCP::connetti(Address* address) {
	int		ret_code;
	struct sockaddr_in* binary;

	binary = address->get_binary();
	ret_code = ::connect(	this->_sock_id,
							(struct sockaddr*)binary,
							(socklen_t)sizeof(struct sockaddr) );
	free(binary);

	return (ret_code==0);
}

bool	ClientTCP::invia(char* msg) { 
	int		ret_code;
	int		len;
	
	len = len_str(msg)+1;

	ret_code = send(this->_sock_id,msg,len,0);
	return  (ret_code == len);
}

char*	ClientTCP::ricevi() {
	int		ret_code;
	char	buffer[MAX_STR+1];

	ret_code = recv(this->_sock_id,buffer,MAX_STR,0);
	if (ret_code==0)
		return NULL;
	
	buffer[ret_code]= '\0';	
	return cpy_str(buffer);
}	

bool	ClientTCP::close_connection() { ::close(this->_sock_id); }

#endif // SOCKETTCP_HPP

