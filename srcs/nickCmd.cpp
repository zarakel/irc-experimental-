#include "../headers/headers.hpp"
#include "../headers/Command.hpp"
#include "../headers/answer.hpp"

int	NICK(int poll_fd, Stock *Stock)
{
//	int yo = 0;
	std::string upper;
	std::string lower;
	std::string tmp;

// essai pour rendre nick case insensitive

/*	for (int i = 0; Stock->line[1][i], i++)
	{
		if (Stock->line[1][i] >= 97 && Stock->line[1][i] <= 122)
			
	}*/

	if (Stock->line.size() < Stock->full_command["NICK"].size() ||
    Stock->line.size() > Stock->full_command["NICK"].size())
    {
        MessageG(poll_fd, ERR_NEEDMOREPARAMS, ":Not the good amount of parameters", Stock);
        Stock->line.clear();
        return (1);
    }

	if (Stock->line[1].length() > 0 && Stock->line[2].empty()
	&& Stock->Identities.size() > 0)
	{
		for (int i = 0; i < (int)Stock->Identities.size(); i++)
		{
			if ( i == Stock->User)
				i++;
			if ( i == (int)Stock->Identities.size())
				break;
			if (Stock->Identities[i][0].compare(Stock->line[1]) == 0)
			{
				MessageG(poll_fd, ERR_NICKNAMEINUSE, ":Nick used",
				Stock);
				Stock->line.clear();
				return (0);
			}
		}
	}
	if (Stock->line[1].length() > 0 && Stock->line[2].empty() 
	&& Stock->Identities[Stock->User].size() == 0)
	{
	//	std::cout << "coucou" << std::endl;
	//	std::cout << yo++ << std::endl;
		Stock->Identities[Stock->User].push_back(Stock->line[1]);
		Stock->Nicks.push_back(Stock->line[1]);
	//	std::cout << yo++ << std::endl;
		if (send(poll_fd, "Your nick is set !\n\r", 19, 0) == -1)
			perror("send");
		Stock->line.clear();
		Stock->nick_already_set[Stock->User] = 1;
		Stock->tmp_nick[Stock->User] = 1;
		return (1);
	}
	else if (Stock->line[1].length() > 0 && Stock->line[2].empty() 
	&& Stock->Identities[Stock->User][0].empty() == 0
	&& Stock->Identities[Stock->User][0].compare(Stock->line[1]) != 0)
	{
		tmp = Stock->Identities[Stock->User][0];
		tmp += " has changed his nickname to ";
		tmp += Stock->line[1] + '\n';
		Stock->Identities[Stock->User][0] = Stock->line[1];
		Stock->Nicks[Stock->User].clear();
		Stock->Nicks[Stock->User] = Stock->line[1];
		for (size_t c = 0; c < tmp.size(); c++)
		{
			if (send(poll_fd, &tmp[c], 1, 0) == -1)
				perror("send :");
		}
		Stock->line.clear();
		return (1);
	}
	else if (Stock->line[1].length() > 0 && Stock->line[2].empty() 
	&& Stock->Identities[Stock->User][0].compare(Stock->line[1]) == 0)
	{
		MessageG(poll_fd, ERR_NICKNAMEINUSE, ":Nick used",
		Stock);
		Stock->line.clear();
		return (0);
	}
// Peut etre ajouter sécu
/*	else
	{
		if (send(poll_fd, "Bad param's: You're nick is not set !\n\r", 39, 0) == -1)
			perror("send");
		Stock->line.clear();
	}*/
	Stock->line.clear();
	return (0);
}
