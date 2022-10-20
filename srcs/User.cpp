#include "headers.hpp"

User::User( void ) : _fd(-1)
{}

User::User( User const &src ){
	*this = src;
}

User::~User( void ) {}

User				&User::operator=( User const &rhs )
{
	_fd = rhs._fd;
	return (*this);
}

int	const				&User::getFd( void ) const
{
	return _fd;
}

bool const				&User::getIsSet( void ) const
{
	return _isset;
}