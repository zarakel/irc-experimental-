#ifndef STOCK_HPP
# define STOCK_HPP
# include "headers.hpp"
# include <iostream>

class Stock
{

	public :

	Stock( void );
	Stock( Stock const & );
	Stock & operator=( Stock const & cp );
	void Init_Values( int argc, char **argv );
	char *Check_Port( char *port );
	bool Is_Number( const std::string s );
	~Stock( void );

	char	*port;

	std::vector<std::string> line;
	std::vector<std::string> all_commands;
	std::vector<std::string> Nicks;

	std::map<int, std::vector<std::string> > Channels; // le int correspond a l'ordre de création des channels
//	[0] = nom de chan, [1] = key, [2] = topic

	std::map<std::string, std::vector<std::string> > Channels_Users; // string fait reference a un nom de channel connu
//  chaque instance du vector représente les utilisateurs qui y sont présents, par ordre de connexion
//	potentiellement, le [0] est d'office un operator ? 

	std::map<int, std::vector<std::string> > Identities; // int correspond a l'ordre de connexion des clients
//	[0] représente le Nick, les suivant peuvent représenter les informations de USER
//	peut-être qu'on peut set le dernier pour le flag de mode ? 

	std::map<std::string, std::vector<std::string> > full_command; // string représente le nom d'une commande
//	les autres arguements correspondent aux paramètres obligatoires

	std::string pass;
	std::string word;
	int	nick_already_set[100]; // Chaque [int] est à associé à Stock->User, qui permet d'associé les données d'un client à un int dédié
	int	tmp_authentified[100];
	int	authentified[100];
	int	client_fd[100];
	int	User;
	int	Channel_Count; // Channel_Count commencera par 1 pour dire qu'1 	channel a été crée, nous dit comebien de channels sont crées
	int	User_Count; // Pareil qu'au dessus
	int	fd_count;
};

#endif
