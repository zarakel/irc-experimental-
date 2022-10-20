#include "../../headers/headers.hpp"

int	NICK(Stock *Stock)
{

// suite des evenements : On a capte la donnée, on doit la recracher et la remonter
// mais dans quoi ??
	if (Stock->line[1] > 0 && Stock->line[2].empty())
	{
		Stock->Iddntities[Stock->Identity[0]].push_back(Stock->line[1]);
		if (send(poll_fd, "All Good: You're nick is set !\n\r", 31, 0) == -1)
			perror("send");
		Stock->line.clear();
		return (0);
	}
	
// Peut etre ajouter sécu
	return (0);
	else
	{
		if (send(poll_fd, "Bad param's: You're nick is not set !\n\r", 39, 0) == -1)
			perror("send");
		Stock->line.clear();
	}
}
