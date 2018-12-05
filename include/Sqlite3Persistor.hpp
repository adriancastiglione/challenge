
#ifndef SQLITE3PERSISTOR_H
#define SQLITE3PERSISTOR_H

#include <iostream>
#include <sqlite3.h>
#include <exception>
#include <vector>

class Sqlite3Persistor{

	sqlite3 *db;

public:

	Sqlite3Persistor();

	~Sqlite3Persistor();

	bool health_is_ok();
	
	int64_t create_user(const std::string& user_name, const std::string& password);

	bool user_exists(const std::string& user_name);

	int token_exists(const std::string& user, const std::string& password);

	void save_token(int64_t token);
	bool token_exists(int64_t token);
/*
	int sendMessage(long sender_id, long receiver_id, Message message);

	std::vector<Message> getMessages(long user_id, int start, int limit);
*/
};


#endif