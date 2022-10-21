#include "../headers/Stock.hpp"

Stock::Stock( void ){ return; }

Stock::~Stock( void ){ return; }

Stock::Stock( Stock const & ){ return; }

Stock & Stock::operator=( Stock const & cp )
{
	this->line = cp.line;
	this->all_commands = cp.all_commands;
	this->Identities = cp.Identities;
	this->full_command = cp.full_command;
	this->pass = cp.pass;
	this->word = cp.word;
	this->IP_tmp = cp.IP_tmp;
	this->User = cp.User;
	for (int i = 0; i <= User; i++)
	{
		this->nick_already_set[i] = cp.nick_already_set[i];
		this->authentified[i] = cp.authentified[i];
	}
	return *this;
}

void Stock::Init_Values( int argc, char **argv )
{
	if ( argc != 3 )
		throw errorExcute("Usage: ./ircserv <port> <password> \n");
	this->port = Check_Port(argv[1]);
//	check_password(argv[2]);
	this->pass = argv[2];

	std::string tmp = "PASS";
	this->all_commands.push_back(tmp);
	tmp.clear();

	tmp = "NICK";
	this->all_commands.push_back(tmp);
	tmp.clear();

	tmp = "USER";
	this->all_commands.push_back(tmp);
	tmp.clear();

	this->full_command["PASS"].push_back("PASS");
	this->full_command["PASS"].push_back("arguement");

	this->full_command["NICK"].push_back("NICK");
	this->full_command["NICK"].push_back("arguement");

	this->full_command["USER"].push_back("USER");
	this->full_command["USER"].push_back("username");
	this->full_command["USER"].push_back("hostname");
	this->full_command["USER"].push_back("servername");
	this->full_command["USER"].push_back("realname");

	this->User = 0;
	this->nick_already_set[this->User] = 0;
	this->authentified[this->User] = 0;
}

char	*Stock::Check_Port( char *port )
{
// est-ce qu'on rajoute une limite de la securite sur les args donnés ?
// on pourrait rajouter le nombre de caracteres, une limite au port

	int     i;

	if (!this->Is_Number(port))
		throw errorExcute("Usage: <port> must be numeric");
	i = atoi( port );
	if ( i < 0 || i > 65535 )
		throw errorExcute("Usage: <port> can't be 0, negative or more than 65535");
// peut être faire une fonction qui vérifie si les ports sont utilisés ou pas
	return (port);	
}

bool Stock::Is_Number(const std::string s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
