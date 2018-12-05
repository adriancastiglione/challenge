
restbed_files_for_linker = "/usr/local/library"

all:
	mkdir -p bin
	g++ src/*.cpp -o bin/chat --std=c++11 -I"include" -L$(restbed_files_for_linker) -lrestbed -lsqlite3 -lcurl -lcurlpp

tests:
	mkdir -p bin
	g++ test/*.cpp src/Sqlite3Persistor.cpp  -o bin/chat-tests --std=c++11 -I"include" -L$(restbed_files_for_linker) -lrestbed -lsqlite3 -lcurl -lcurlpp
	./run-tests.sh

clean:
	rm -rf bin

.PHONY: all test clean
