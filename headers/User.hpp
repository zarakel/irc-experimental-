#ifndef USER_HPP
# define USER_HPP

# include "headers.hpp"

class User
{
    private:
        int         _fd;
        bool		_isset;			// If USER command is been used

    public:

        User( void );
        User( int fd );
        User( User const &src );
		~User( void );


        int	const				&getFd( void ) const;
        bool const				&getIsSet( void ) const;
}




#endif