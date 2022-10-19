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
/*	void Set_Pass( const std::string );
	void Set_Word( const std::string );
	void Set_Current_Line( const std::vector<std::string> );
	std::string Get_String( void ) const;
	std::vector<std::string> Get_VectorStr( void ) const;*/
	~Stock( void );

//	private :
	
	char	*port;
	std::vector<std::string> line;
	std::vector<std::string> all_commands;
	std::string pass;
	std::string word;
};

#endif
