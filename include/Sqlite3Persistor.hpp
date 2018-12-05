
#ifndef SQLITE3PERSISTOR_H
#define SQLITE3PERSISTOR_H

#include <iostream>
#include <sqlite3.h>
#include <exception>
#include <vector>
#include "Message.h"

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

	int send_text_Message(const std::string& sender_id, const std::string& receiver_id, const std::string message_content);
/*
	std::vector<Message> getMessages(long user_id, int start, int limit);
*/
};


#endif