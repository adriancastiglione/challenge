
restbed_files_for_linker = "/usr/local/library"

all:
	mkdir -p bin
	g++ src/chat.cpp -o bin/chat -I"include" -L$(restbed_files_for_linker) -lrestbed -lsqlite3 -lcurl -lcurlpp

tests:
	mkdir -p bin
	g++ test/*.cpp -o bin/chat-tests -I"include" -L$(restbed_files_for_linker) -lrestbed -lsqlite3 -lcurl -lcurlpp
	./run-tests.sh

clean:
	rm -rf bin

.PHONY: all test clean