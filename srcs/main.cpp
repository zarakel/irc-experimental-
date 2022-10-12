
#include <iostream>
#include "../headers/headers.hpp"

bool isNumber(const std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int	parser( int argc, char **argv)
{
	if ( argc != 3 ) {
		throw errorExcute("Usage: ./ircserv <port> <password> \n");
		return ( -1 );
	}
	if (!isNumber(argv[1])) {
		throw errorExcute("Usage: <port> must be numeric");
		return ( -1 );
	}
	int port = atoi(argv[1]);
	if (port < 1025 ||port > 65535) {
		std::cerr << "<port> must be between 1025 and 65535" << std::endl;
		return ( -1 );
	}
	return ( port );
}

int main(int argc, char **argv)
{

    int m;

	//Server	server;  pas encore faire class Server 

	try {
        m = parser( argc, argv);
		if (m == -1)
			return ( 1 );
		//Server server(av[1] av[2]);
		//connecter au server server.connect();
		// - Initializes commands
		// - Creates server socket
		// - Binds the server socket
		// - Makes it listen
		// - Initilizes the file descriptors structure
	}
	catch (const std::exception & e) {
		std::cerr << "exception found: " << e.what() << std::endl;
	}
	return ( 0 );
}