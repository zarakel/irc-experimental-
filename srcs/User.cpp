#include "headers.hpp"

User::User( void ) : _fd(-1){}
User::User( User const &src ){ *this = src;}
User::~User( void ) {}

User				&User::operator=( User const &rhs )
{
	_fd = rhs._fd;
	return (*this);
}

User				&User::operator=( User const &rhs )
{
	_fd = rhs._fd;
	_nick = rhs._nick;
	_username = rhs._userName;
	_hostname = rhs._hostName;
	_servername = rhs._serverName;
	_realname = rhs._realName;
	// _mode = rhs._mode;
	// _passwd = rhs._passwd;
	// _last_act = rhs._last_act;
	// _ping_status = rhs._ping_status;
	_isset = rhs._isset;
	// _isIRCOper = rhs._isIRCOper;
	// _curr_chan = rhs._curr_chan;
	// _channels = rhs._channels;

	return (*this);
}


//**********************************************//
//*                 getters                    *//
//**********************************************//

int	const			&User::getFd( void ) const { return _fd; }
string const		&User::getUsername( void ) const { return _userName; }
string const		&User::getHostname( void ) const { return _hostName; }
string const		&User::getServername( void ) const { return _serverName; }
string const		&User::getRealName( void ) const { return _realName; }
bool const			&User::getIsSet( void ) const { return _isset; }
bool	            User::isPassChecked() const { return _isPassChecked; }
std::string 		User::getNickname() const { return _nickName; }

//**********************************************//
//*                 setters                    *//
//**********************************************//


void 				User::setUsername( string username ) { _userName = username;}
void				User::setHostname( string hostname ) { _hostName = hostname;}
void				User::setServername( string servername ) {_serverName = servername;}
void				User::setRealname( string realname ) {_realName = realname; }
void				User::setIsSet( bool isset ) { _isset = isset;}
