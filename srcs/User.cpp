#include "../headers/User.hpp"

User::User( void ) : _fd(-1){}
User::User( User const &src ){ *this = src;}
User::~User( void ) {}

User		&User::operator=( User const &rhs )
{
	this->_fd = rhs._fd;
	this->_nickName = rhs._nickName;
	this->_userName = rhs._userName;
	this->_hostName = rhs._hostName;
	this->_serverName = rhs._serverName;
	this->_realName = rhs._realName;
	// this->_mode = rhs._mode;
	// this->_passwd = rhs._passwd;
	// this->_last_act = rhs._last_act;
	// this->_ping_status = rhs._ping_status;
	this->_isset = rhs._isset;
	// this->_isIRCOper = rhs._isIRCOper;
	// this->_curr_chan = rhs._curr_chan;
	// this->_channels = rhs._channels;

	return (*this);
}


//**********************************************//
//*                 getters                    *//
//**********************************************//

int	const		&User::getFd( void ) const{ return _fd; }
std::string const	&User::getUsername( void ) const { return _userName; }
std::string const	&User::getHostname( void ) const { return _hostName; }
std::string const	&User::getServername( void ) const { return _serverName; }
std::string const	&User::getRealName( void ) const { return _realName; }
bool const		&User::getIsSet( void ) const { return _isset; }
//bool			User::isPassChecked() const { return _isPassChecked; }
std::string const	&User::getNickName( void ) const { return _nickName; }

//**********************************************//
//*                 setters                    *//
//**********************************************//


void 				User::setUsername( std::string username ) { _userName = username;}
void				User::setHostname( std::string hostname ) { _hostName = hostname;}
void				User::setServername( std::string servername ) {_serverName = servername;}
void				User::setRealname( std::string realname ) {_realName = realname; }
void				User::setIsSet( bool isset ) { _isset = isset;}
