/*
    https://www.techbull.com/techbull/guide/internet/irccommande.html#users
	http://www.iprelax.fr/irc/irc_rfcus4.php
*/

#include "../headers/User.hpp"
//#include "../headers/error.hpp"
// #include "../headers/Command.hpp"
// #include "../headers/User.hpp"
#include "../headers/tools.hpp"
// #include "../headers/Server.hpp"

// bool    check_password( User &user, Stock *Stock)
// {
//     if (user.getPasswd() == Stock->pass )
//         return true;

//     std::string         error;
//     std::ostringstream   s;

//     if (user.getPasswd() == "")
//         error = "Log in Server needs password ";
//     else
//         error = "Wrong password";
//     s << "Error: "<< user.getUsername() << "@" << Stock->getHost() << "[" << error << "]\r\n";

//     return false;
// }

User::User( void ) 
{  
	this->_fd = -1;
	this->_nick = "";
	this->_passwd = "";
	this->_userName = "";
	this->_hostName = "";
	this->_serverName = "";
	this->_realName = "";
	this->_isSet = false;
	// this->_mode = "";
	// this->_ping_status = false;
}

User::User( int fd )
{
	this->_fd = fd;
	this->_nick = "";
	this->_passwd = "";
	this->_userName = "";
	this->_hostName = "127.0.0.1";
	this->_serverName = "";
	this->_realName = "";
	this->_isSet = false;
	//this->_isaccepted = false;
	this->_mode = "";
	this->_ping_status = false;
}

// User::User( int fd, std::string nick, std::string userName, std::string hostName,
// 	std::string serverName, std::string realName, std::string mode, bool ping_status )
// {
// 	this->_fd = fd;
// 	this->_nick = nick;
// 	this->_userName = userName;
// 	this->_hostName = hostName;
// 	this->_serverName = serverName;
// 	this->_realName = realName;
// 	this->_isSet = false;
// 	this->_mode = mode;
// 	this->_ping_status = ping_status;
// }

User::User( User const &src ) { *this = src; }
User::~User( void ) {}
User	&User::operator=( User const &rhs )
{
	//_fd = rhs._fd;
	_nick = rhs._nick;
	_passwd = rhs._passwd;
	_userName = rhs._userName;
	_hostName = rhs._hostName;
	_serverName = rhs._serverName;
	_realName = rhs._realName;
	_mode = rhs._mode;
	_ping_status = rhs._ping_status;
	_isSet = rhs._isSet;
	return (*this);
}

int	const			    &User::getFd( void ) const { return _fd; }
bool const			    &User::getIsSet( void ) const { return _isSet; }
//bool const				&User::isConnected(void) { return _connected; }
// bool const				&User::getPingStatus( void ) const { return _ping_status; }
std::string const 		&User::getPasswd( void ) const { return _passwd; }
std::string const		&User::getUsername( void ) const { return _userName; }
std::string const		&User::getHostname( void ) const { return _hostName; }
std::string const		&User::getServername( void ) const { return _serverName; }
std::string const		&User::getRealName( void ) const { return _realName; }
std::string const	    &User::getNick() const { return _nick; }

//void	User::setFd( int fd) {_fd = fd; }
void	User::setNick( std::string nick ) { _nick = nick; }
void 	User::setUsername( std::string username ) { _userName = username;}
void	User::setHostname( std::string hostname ) { _hostName = hostname;}
void	User::setServername( std::string servername ) { _serverName = servername;}
void	User::setRealname( std::string realname ) { _realName = realname; }
void	User::setIsSet( bool isset ) { _isSet = isset;}

int USER(int poll_fd, Stock *Stock)
{
    User user;

    if (Stock->line.size() < Stock->full_command["USER"].size())
    {
        errorMessage(poll_fd, ERR_NEEDMOREPARAMS, ": Need more parameters ");
        return (1);
    }
    if (user.getIsSet())
    {
        errorMessage(poll_fd, ERR_ALREADYREGISTRED, user.getNick());
        return (1);
    }
	user.setUsername(Stock->line[1]);
	user.setHostname(Stock->line[2]);
	user.setServername(Stock->line[3]);
        user.setRealname(Stock->line[4]);
	user.setIsSet(true);
	std::cout << "Name is " << user.getUsername() << std::endl;
	std::cout << "Host is " << user.getHostname() << std::endl;
	std::cout << "Server is " << user.getServername() << std::endl;
	std::cout << "Realname is "<< user.getRealName() << std::endl;
	std::cout << "set is " << user.getIsSet() << std::endl;
	Stock->tmp_authentified[Stock->User] = 3;
	Stock->line.clear();
//	exit(0);
    return (0);
}
