#include "../headers/headers.hpp"
#include "../headers/Command.hpp"

int	NICK(int poll_fd, Stock *Stock)
{
//	int yo = 0;
	std::string upper;
	std::string lower;

// essai pour rendre nick case insensitive

/*	for (int i = 0; Stock->line[1][i], i++)
	{
		if (Stock->line[1][i] >= 97 && Stock->line[1][i] <= 122)
			
	}*/
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
				if (send(poll_fd, "Your nick is already taken !\n\r", 30, 0) == -1)
					perror("send");
				Stock->line.clear();
				return (12349);
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
//		if (send(poll_fd, "All Good: Your nick is set !\n\r", 29, 0) == -1)
//			perror("send");
		Stock->line.clear();
		Stock->nick_already_set[Stock->User] = 1;
		Stock->tmp_nick[Stock->User] = 1;
		return (20);
	}
	else if (Stock->line[1].length() > 0 && Stock->line[2].empty() 
	&& Stock->Identities[Stock->User][0].empty() == 0
	&& Stock->Identities[Stock->User][0].compare(Stock->line[1]) != 0)
	{
		Stock->Identities[Stock->User][0] = Stock->line[1];
		Stock->Nicks[Stock->User].clear();
		Stock->Nicks[Stock->User] = Stock->line[1];
		if (send(poll_fd, "All Good: Your nick have changed !\n\r", 35, 0) == -1)
			perror("send");
		Stock->line.clear();
		return (60);
	}
	else if (Stock->line[1].length() > 0 && Stock->line[2].empty() 
	&& Stock->Identities[Stock->User][0].compare(Stock->line[1]) == 0)
	{
		if (send(poll_fd, "Bad Param': Same nick\n\r", 23, 0) == -1)
			perror("send");
		Stock->line.clear();
		return (76);
	}
// Peut etre ajouter sécu
	else
	{
		if (send(poll_fd, "Bad param's: You're nick is not set !\n\r", 39, 0) == -1)
			perror("send");
		Stock->line.clear();
	}
	Stock->line.clear();
	return (0);
}
