
#include "catch.hpp"
#include "Sqlite3Persistor.hpp"
#include <string>

TEST_CASE( "Persistor is ready to work when created", "[Sqlite3Persistor]" ) {

	Sqlite3Persistor persitor;
	REQUIRE(persitor.health_is_ok());
}


TEST_CASE( "Can create new user with new name", "[Sqlite3Persistor]"){

	Sqlite3Persistor persistor;
	persistor.create_user("pepe", "1234");
	
	REQUIRE(persistor.user_exists("pepe"));
}

TEST_CASE( "Cant create new user with repeated name", "[Sqlite3Persistor]"){

	Sqlite3Persistor persistor;
	persistor.create_user("pepe", "1234");
	
	CHECK_THROWS(persistor.create_user("pepe", "1234"));
}
