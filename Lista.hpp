/*
 * Lista.hpp
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

#ifndef LISTA_HPP
#define LISTA_HPP

class Nodo {
private:    
    Nodo * _next;
    virtual void foo() =0;
public:
    Nodo(Nodo*);
    ~Nodo();

  void	set_next(Nodo*);
    Nodo*	get_next();
};

class Lista;

class Iterator {
private:
	Lista*	_lista;
	Nodo*	_current;
public:
	Iterator(Lista*);
	~Iterator();
	
	bool	move_next();		
	bool	is_done();
	bool	move_first();
	Nodo*	get_current();	
};

class Lista {
private:
	Nodo*	_first;
	void	destroy(Nodo*);
public:
	Lista();
	~Lista();

	Nodo*		get_first();
	void		destroy();
	Iterator*	create_Iterator();
	void		add(Nodo*);
};

// class Iterator

Iterator::Iterator(Lista*lista) { 
	this->_lista = lista; 
	this->_current = lista->get_first(); }

Iterator::~Iterator() { }
	
bool	Iterator::move_next() {
	if (this->_current) 
		this->_current = this->_current->get_next();
	return (this->_current? true:false); 
}	

bool	Iterator::is_done() { return this->_current? true:false; }

bool	Iterator::move_first() { 
	this->_current = this->_lista->get_first();
	return (this->_current? true:false); 
}

// class Nodo

Nodo*	Iterator::get_current() { return _current; }

Nodo::Nodo(Nodo* next)		 		{	this->_next=next; }
Nodo::~Nodo()						{ }

void	Nodo::set_next(Nodo * next) {	this->_next=next; }  
Nodo*	Nodo::get_next() 			{	return this->_next; }

// class Lista

void	Lista::destroy(Nodo* nodo)	{
	if (nodo) {
		destroy(nodo->get_next());
		delete(nodo);
	}
}

Lista::Lista() 						{	this->_first=NULL; }
Lista::~Lista() 					{	this->destroy(); }

Nodo*		Lista::get_first()		{	return this->_first; }
void		Lista::destroy()		{	this->destroy(this->_first); }
Iterator*	Lista::create_Iterator(){ 	return new Iterator(this); }

void		Lista::add(Nodo* nodo) {
	nodo->set_next(this->_first);
	this->_first = nodo;
}

#endif // LISTA_HPP
