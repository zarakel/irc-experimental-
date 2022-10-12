#include "../headers/headers.hpp"
#include <cstdlib>

bool isNumber(const std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int	translate_port( char *port )
{
// est-ce qu'on rajoute une limite de la securite sur les args donnés ? 
// on pourrait rajouter le nombre de caracteres, une limite au port

	int	i;

	if (!isNumber(port)) 
		throw errorExcute("Usage: <port> must be numeric");
	i = atoi( port );
	if ( i < 0 || i > 65535 )
		throw errorExcute("Usage: <port> can't be 0, negative or more
		than 65535");
// peut être faire une fonction qui vérifie si les ports sont utilisés ou pas
	return ( i );
}

std::string	password( std::string pass_tmp )
{
	std::string pass;
//	sécu potentielle à rajouter
	pass = pass_tmp;
	return ( pass );
}

int main(int argc, char **argv)
{

	int		port; //je trouve que c'est plus simple sans map
	std::string 	pass; //moins de nommage, 2 trucs c'est peu pour map

// On verfie qu'on est assez d'arguments, que l'argv1, le port, n'est pas de 
// lettre, puis on les stocks 

	try {
	if ( argc != 3 ) 
		throw errorExcute("Usage: ./ircserv <port> <password> \n");
        port = translate_port(argv[1]);
        pass = password((std::string)argv[2]);
	}
	catch (const std::exception & e) {
		std::cerr << "exception found: " << e.what() << std::endl;
		return ( 1 );
	}

// l'etape d'après est la construction du serveur, m nous servira a définir 
// le port et le mot de passe

//	server(port, pass);

	std::cout << "Port = " << port << " && Pass = " << pass << std::endl;

	return (0);
}
