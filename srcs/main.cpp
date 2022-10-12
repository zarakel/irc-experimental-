#include "../headers/headers.hpp"



bool isNumber(const std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

map<string, string> parser( int argc, char **argv)
{

	map<string, string> word;

	if ( argc != 3 ) {
		throw errorExcute("Usage: ./ircserv <port> <password> \n");
	}
	if (!isNumber(argv[1])) {
		throw errorExcute("Usage: <port> must be numeric");
	}
	word["PORT"] = argv[1];
	word["SERVER_PWD"] = argv[2];
	return ( word );
}


int main(int argc, char **argv)
{

    map<string, string> m;

	//Server	server;

	try {
        m = parser( argc, argv);
	}
	catch (const std::exception & e) {
		std::cerr << "exception found: " << e.what() << std::endl;
	}
	return (0);
}