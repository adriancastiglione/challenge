
DEPENDENCIES:
	*libcurl4-openssl-dev
	*libcurlpp-dev
	*restbed
	*sqlite3
	*libsqlite3-dev


HOW TO EXECUTE:
	*compile with make
	*execute run.sh

REMARKS:
	I found restbed installation to be problematic. It installs fine, but in non-standard places. Make sure compiler find
	restbed files. Also make sure shared library is found.
	In my computer, i had to provide restfiles path to linker during compilation (if you cant compile go change that variable
	in Makefile) and for execution i had to provide the path to the shared library files (see run.sh)