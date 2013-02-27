/**

	SQLIteManager.hpp
	Libreria Wrapper di sqlite3.h per semplificare ulteriormente la 
	Gestione di un Database SQLite

	---------------------------------------------------------------------------
	
	20-02-2013
	Sanino Alessandro - Create

	21-02-2013
	Sanino Alessandro - Refactoring, Quasi Completamento e Aggiunta Commenti
						(Mancano ExecuteSQLNonQuery e ExecuteScalarQuery!!!)
**/

#ifndef SQLITE_MANAGER
#define SQLITE_MANAGER

#include "sqlite3.h"

class SQLiteManager {
	private:
	char*    dbPath = NULL;     //percorso db (Relatico/Assoluto)
	sqlite3* Database = NULL;   //puntatore a db
	char**   Table = NULL;      //qui finiscono i risultati delle query
	
	public:
	int TableRowCount = 0, TableColumnCount = 0; // numero righe e colonne della tabella
	bool isConnected;           //ottiene il valore che indica se la connessione è attualmente impostata

	void Open(char*);           //--> Apre   Il Db
	bool Close();               //--> Chiude Il Db
	SQLiteManager(char*);
	~SQLiteManager();

	bool ExecuteSQLQuery(char* SQL_Statements);        //|
 	bool ExecuteSQLNonQuery(char* SQL_Statements);     //|----> Funzioni per Eseguire le Query 
	void* ExecuteScalarQuery(char* SQL_Statements);    //|
}

SQLiteManager::SQLiteManager(char* Database_Path) {
	this->dbPath = Database_Path;
	Open(dbPath);
}

SQLiteManager::~SQLiteManager() {
	free(dbPath);
	sqlite3_free(Database);
	if(Table != NULL)
		sqlite3_free_table(Table);
	free(Table);
	
}

void SQLiteManager::Open(char* Path) { //Apre una Connessione Con Un Database
	if(this.isConnected == true)
		if(Close() == true) 
		{
			sqlite3_open(Path, *(this->Database));
			if(sqlite3_errcode(this->Database) == SQLITE_OK) { // Avvenuta La Connessione Con Successo
				this->dbPath = Path;
				this.isConnected = true;
			}
			else                         //ERROR A CASO!
				this.isConnected = false;
		}
		else // Se non Riesco Chiudo Non Riapro Un Nuovo Database (Non Riesco a Liberare la Memoria = MEMORY LEAK)
			this.isConnected = false;
}

bool SQLiteManager::Close() { //Chiude La Connessione
	sqlite3_finalize();
	if(sqlite3_close(this->Database) == SQLITE_OK) { //Riesco a chiudere
		this.isConnected = false;
		return true;
	}
	else //Se Ci sono Richieste Pendenti Al DB non Si Riesce A Chiudere
		return false;
}


bool SQLiteManager::ExecuteSQLQuery(char* SQL_Statements) {
	char* MessaggiErrore; //temporanea
	bool ret;
	if(this.isConnected == true) {    // se non sono connesso al DB come minchia faccio a passargli le query?!?!
		if(Table != NULL)             //se no perdo il riferimento istanziando una nuova tabella = MEMORY LEAK
			sqlite_free_table(Table);
		if(sqlite3_get_table(this->Database, SQL_Statements, *(this->Table), *(this.TableRowCount), *(this.TableColumnCount), MessaggiErrore) == SQLITE_OK) {
			ret = true;
		}
		else //something gone wrong
			ret = false;
		free(MessaggiErrore);
		return ret;
	}
	else
		return false;
}

#endif
