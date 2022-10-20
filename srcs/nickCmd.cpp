#include "../headers/headers.hpp"
#include "../headers/Command.hpp"

int	NICK(int poll_fd, Stock *Stock)
{

// suite des evenements : On a capte la donnée, on doit la recracher et la remonter
// mais dans quoi ??
	if (Stock->line[1].length() > 0 && Stock->line[2].empty() && 
		Stock->nick_already_set == 0)
	{
		Stock->Identities[Stock->Identity[0]].push_back(Stock->line[1]);
		if (send(poll_fd, "All Good: You're nick is set !\n\r", 32, 0) == -1)
			perror("send");
		Stock->line.clear();
		Stock->nick_already_set = 1;
		return (0);
	}
	else if (Stock->line[1].length() > 0 && Stock->line[2].empty() && 
		Stock->nick_already_set == 1)
	{
		Stock->Identities[Stock->Identity[0]][1] = Stock->line[1];
		if (send(poll_fd, "All Good: You're new nick is set !\n\r", 36, 0) == -1)
			perror("send");
		Stock->line.clear();
		return (0);
	}
	else // 
	{
		if (send(poll_fd, "Bad param's: You're nick is not set !\n\r", 39, 0) == -1)
			perror("send");
		Stock->line.clear();
	}

// Peut etre ajouter sécu
	return (512);
}
