#ifndef USER_HPP
# define USER_HPP

# include "headers.hpp"

//************************************************//
//*                 User Class                   *//
//************************************************//

class User
{
    private:
        int			_fd;
        bool		        _isset;	// If USER command is been used
        std::string		_userName;
	std::string		_hostName;
	std::string		_serverName;
	std::string		_realName;
        bool			_isPassChecked;
        std::string		_nickName;
	// string		_mode;
	// string		_passwd;
	// time_t 		*_last_act;
	// bool			_ping_status;
	// bool			_isset;		// If USER command is been used
	// bool			_isIRCOper;	// If OPER command is been used
	// bool			_isAuth;
	// Channel		*_curr_chan;	// Last joined channel
	// vector<Channel*>	_channels;		// Max chans 10

    public:

        User( void );
        User( int fd );
        User( User const &src );
	~User( void );
        User			&operator=( User const &rhs );

        //getters
        int	const		&getFd( void ) const;
        bool const		&getIsSet( void ) const;
        std::string const	&getUsername( void ) const;
	std::string const	&getHostname( void ) const;
	std::string const	&getServername( void ) const;
	std::string const	&getRealName( void ) const;
	std::string const	&getNickName( void ) const;

        //setters

        void			setFd( int fd );
	void 			setUsername( std::string username );
	void			setHostname( std::string hostname );
	void			setServername( std::string servername );
	void			setRealname( std::string realname );
	void			setIsSet( bool isset );

};

#endif
