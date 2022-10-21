#ifndef USER_HPP
# define USER_HPP

# include "headers.hpp"

//************************************************//
//*                 User Class                   *//
//************************************************//

class User
{
    private:
        int                  _fd;
        bool		        _isset;			// If USER command is been used
        string				_userName;
		string				_hostName;
		string				_serverName;
		string				_realName;
        bool				_isPassChecked;
        string			    _nickName;
		// string				_mode;
		// string				_passwd;
		// time_t 				*_last_act;
		// bool				_ping_status;
		// bool				_isset;			// If USER command is been used
		// bool				_isIRCOper;		// If OPER command is been used
		// bool				_isAuth;
		// Channel				*_curr_chan;	// Last joined channel
		// vector<Channel*>	_channels;		// Max chans 10

    public:

        User( void );
        User( int fd );
        User( User const &src );
		~User( void );
        User				&operator=( User const &rhs );

        //getters
        int	const				&getFd( void ) const;
        bool const				&getIsSet( void ) const;
        string const			&getUsername( void ) const;
		string const			&getHostname( void ) const;
		string const			&getServername( void ) const;
		string const			&getRealName( void ) const;

        //setters

        void					setFd( int fd );
		void 					setUsername( string username );
		void					setHostname( string hostname );
		void					setServername( string servername );
		void					setRealName( string realname );

};

#endif