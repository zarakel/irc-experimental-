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
	~Stock( void );

	char	*port;
	std::vector<std::string> line;
	std::vector<std::string> all_commands;
	std::vector<std::string> Identity;
	std::map<std::string, std::vector<std::string> > Identities;
	std::map<std::string, std::vector<std::string> > full_command;
	std::string pass;
	std::string word;
	int	nick_already_set;
};

#endif
