#include "../headers/Stock.hpp"
#include "../headers/headers.hpp"
#include <cstdlib>
#include "../headers/Server.hpp"

bool isNumber(const std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

char	*check_port( char *port )
{
// est-ce qu'on rajoute une limite de la securite sur les args donnés ? 
// on pourrait rajouter le nombre de caracteres, une limite au port

	int	i;

	if (!isNumber(port)) 
		throw errorExcute("Usage: <port> must be numeric");
	i = atoi( port );
	if ( i < 0 || i > 65535 )
		throw errorExcute("Usage: <port> can't be 0, negative or more than 65535");
// peut être faire une fonction qui vérifie si les ports sont utilisés ou pas
	return (port);
}

/*void	check_password( std::string pass_tmp ) -- Secu a ajouter 
{

}*/

int main(int argc, char **argv)
{

//	char		*port; //je trouve que c'est plus simple sans map
//	std::string	pass; //moins de nommage, 2 trucs c'est peu pour map

// On verfie qu'on est assez d'arguments, que l'argv1, le port, n'est pas de 
// lettre, puis on les stocks 

	Stock Stock;

	try {
	if ( argc != 3 ) 
		throw errorExcute("Usage: ./ircserv <port> <password> \n");
	Stock.port = check_port(argv[1]);
//      check_password(argv[2]);
	Stock.pass = argv[2];
	}
	catch (const std::exception & e) {
		std::cerr << "exception found: " << e.what() << std::endl;
		return ( 1 );
	}

	std::string tmp = "PASS";
	Stock.all_commands.push_back(tmp);
	
	tmp = "NICK";
	Stock.all_commands.push_back(tmp);
	tmp.clear();

	Stock.full_command["PASS"].push_back("PASS");
	Stock.full_command["PASS"].push_back("arguement");

	Stock.full_command["NICK"].push_back("NICK");
	Stock.full_command["NICK"].push_back("arguement");

	Stock.User = 0;
	Stock.nick_already_set[Stock.User] = 0;
	Stock.authentified[Stock.User] = 0;
	
	server(&Stock);

	std::cout << "Port = " << Stock.port << " && Pass = " << Stock.pass << std::endl;
	return (0);
}
