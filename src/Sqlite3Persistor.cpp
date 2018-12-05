
#include "Sqlite3Persistor.hpp"

using namespace std;

/*
class Sqlite3Persistor{

public:

	bool health_is_ok();
	
	int create_user(const string& user, const string& password);

	int authenticate(const string& user, const string& password);

	int sendMessage(long sender_id, long receiver_id, Message message);

	std::vector<Message> getMessages(long user_id, int start, int limit);

};
*/

Sqlite3Persistor::Sqlite3Persistor(){

	
	char *zErrMsg = 0;
	vector<string> statements;
	int rc;
  
	rc = sqlite3_open("chat.db", &db);

	if( rc )
	{
		cout<<"Can't open database: "<<sqlite3_errmsg(db)<<"\n";
	} 
	else
	{
		cout<<"Open database successfully\n\n";
	}

	statements.push_back(string("create table if not exists users(id integer primary key autoincrement, user_name string, password string)"));
	statements.push_back(string("create table if not exists tokens(id integer primary key autoincrement, token string)"));
	statements.push_back(string("create table if not exists text_message(id integer primary key autoincrement, sender_id integer, receiver_id integer, message_content string, date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)"));

	for(int i = 0; i < statements.size(); i++)
	{
		rc = sqlite3_exec(db, statements[i].c_str(), 0, 0, &zErrMsg);
		if( rc!=SQLITE_OK )
		{
			cout<<"SQL error: "<<sqlite3_errmsg(db)<<"\n";
			sqlite3_free(zErrMsg);
		}
	}

	
}

Sqlite3Persistor::~Sqlite3Persistor(){
	sqlite3_close(db);
}

bool Sqlite3Persistor::health_is_ok(){

	char *zErrMsg = 0;
	try{
		int rc = sqlite3_exec(db, "SELECT 1", 0, 0, &zErrMsg);
		if( rc!=SQLITE_OK ) throw std::exception();
		return true;
	}
	catch(std::exception e){
		sqlite3_free(zErrMsg);
		return false;
	};
}

int64_t Sqlite3Persistor::create_user(const std::string& user_name, const std::string& password){

	if (user_exists(user_name)) throw std::exception();

	char *zErrMsg = 0;
	sqlite3_exec(db, string("INSERT INTO users(user_name, password) VALUES('" + user_name + "','" + password + "' )").c_str(), 0, 0, &zErrMsg);
	return (int64_t) sqlite3_last_insert_rowid(db);
}

int last_query_row_count = 0;
int count_rows(void *NotUsed, int argc, char **argv, char **azColName)
{
	last_query_row_count = argc;
	std::cout << last_query_row_count << endl;
	return 0;
}

bool Sqlite3Persistor::user_exists(const std::string& user_name){
	char * zErrMsg = 0;
	sqlite3_exec(db, string("select * from users where user_name = '" + user_name + "'").c_str(), count_rows, 0, &zErrMsg);
	return last_query_row_count != 0;
}


void Sqlite3Persistor::save_token(const std::string& token){
	char *zErrMsg = 0;
	sqlite3_exec(db, string("INSERT INTO tokens(token) VALUES("+ token + ")").c_str(), 0, 0, &zErrMsg);
}

bool Sqlite3Persistor::token_exists(const std::string& token){
	char * zErrMsg = 0;
	sqlite3_exec(db, string("select * from tokens where token = '" + token + "'").c_str(), count_rows, 0, &zErrMsg);
	return last_query_row_count != 0;
}

std::string message_timestamp = "";
int Sqlite3Persistor::send_text_Message(const std::string& sender_id, const std::string& receiver_id, const std::string message_content){

	char *zErrMsg = 0;
	sqlite3_exec(db, string("INSERT INTO text_message(sender_id, receiver_id, message_content) VALUES('" + sender_id + "','" + receiver_id + "','" + message_content +")").c_str(), 0, 0, &zErrMsg);
	int64_t id = (int64_t) sqlite3_last_insert_rowid(db);

}