
#include <chat.hpp>
#include "Sqlite3Persistor.hpp"


using json = nlohmann::json;
using namespace std;
using namespace restbed;

Sqlite3Persistor* persistor;

void post_check_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        json j;
        if(persistor->health_is_ok())
            j["health"] = "ok";
        else
            j["health"] = "fail";
        
        auto json_str = j.dump();
        session->close( OK, json_str, { { "Content-Length", to_string(json_str.size()) } } );
    } );
}

void post_createUser_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );

        string content(body.begin(), body.end());
        json json_content = json::parse(content);
        json response;
        response["id"] = persistor->create_user(json_content["username"], json_content["password"]);
        auto json_str = response.dump();
        session->close( OK, json_str, { { "Content-Length", to_string(json_str.size()) } } );
    } );
}


int main( const int, const char** )
{
    persistor = new Sqlite3Persistor();

    auto check = make_shared< Resource >( );
    check->set_path( "/check" );
    check->set_method_handler( "POST", post_check_handler );

    auto createUser = make_shared<Resource> ();
    createUser->set_path("/createUser");
    createUser->set_method_handler("POST", post_createUser_handler);

    auto settings = make_shared< Settings >( );
    settings->set_port( 8080 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( check );
    service.publish( createUser );
    service.start( settings );

    delete persistor;
    return EXIT_SUCCESS;
}