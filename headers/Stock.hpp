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
	std::map<int, std::vector<std::string> > Channels;
	// Channels[i][0] = Nom du channel
	// Channels[i][1] = key
	// Channels[i][2] = topic
	
	std::map<std::string, std::vector<std::string> > Channels_Users;
	// A coupler avec nom de channel en 1er argument 
	
	std::map<int, std::vector<std::string> > Identities; 
	// Identities[Stock->User][0] = IP
	// Identities[Stock->User][1] = Nick
	// Identities[Stock->User][2] = Username

	std::vector<std::string> Nicks; // a coupler avec Stock->User
	std::map<int, std::vector<std::string> > Usernames; // a coupler avec Stock->User
	std::map<std::string, std::vector<std::string> > full_command;
	std::string pass;
	std::string word;
	std::string IP_tmp;
	int	nick_already_set[100];
	int	tmp_authentified[100];
	int	authentified[100];
	int	User;
	int	Channel_Count; // Channel_Count commencera par 1 pour dire qu'1 	channel a été crée, nous dit comebien de channels sont crées
	int	User_Count; // Pareil qu'au dessus
};

#endif
