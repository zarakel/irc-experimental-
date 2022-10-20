/*
https://www.techbull.com/techbull/guide/internet/irccommande.html#users

/*
    USER <username> <hostname> <servername> <realname>

	The USER message is used at the beginning of connection to specify
	the username, hostname, servername and realname of s new user.  It is
	also used in communication between servers to indicate new user
	arriving on IRC, since only after both USER and NICK have been
	received from a client does a user become registered.

	Numeric Replies:

        ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
*/

void USER(Server &server, User &user, vector<string> args)
{
    if (args.size() < 5)
    {
        errorMessage(user, ERR_NEEDMOREPARAMS, ":Need more parameters")
        return ;
    }

    if (user.getIsSet())  //check if the 
	{
		errorMessage(user, ERR_ALREADYREGISTRED, usr.getNick());
		return ;
	}

}


