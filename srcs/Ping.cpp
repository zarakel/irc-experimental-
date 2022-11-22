#include "../headers/Ping.hpp"
#include "../headers/Command.hpp"

int PING(int poll_fd, Stock *Stock)
{
//	std::cout << "User IRSSI = " <<  Stock->User << std::endl;
	
	if(send(poll_fd, "PONG :ft_irc\n", 13, 0) != -1)
	{
		Stock->line.clear();
		return(1);
	}
	Stock->line.clear();
	return(0);
/*	for (int check = 0; check < Stock->User_Count; check++)
	{
		if (poll_fd == Stock->client_fd[check])
			Stock->User = check;
	}*/
}
