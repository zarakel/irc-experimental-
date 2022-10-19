#include "../headers/headers.hpp"
#include "../headers/Command.hpp"

int	PASS(int poll_fd, Stock *Stock)
{
	if (Stock->pass.compare(Stock->line[1]) == 0)
	{
		if (send(poll_fd, "All Good: You're authorized !\n\r", 31, 0) == -1)
			perror("send");
//              authentification réussi, pour le pass en tout cas
		Stock->line.clear();
		return(3);
	}
	else
	{
//		voir comment doivent etre géré les numerics
		std::cout << "le mot de passe invalide est : " << Stock->line[1] << std::endl;
		if (send(poll_fd, "Bad Password: Casse toi pov' con !\n\r", 36, 0) == -1)
			perror("send");
		Stock->line.clear();
	//	close(poll_fd);
		return (400);
	}	
}
