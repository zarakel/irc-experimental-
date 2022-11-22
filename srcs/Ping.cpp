#include "../headers/Ping.hpp"
#include "../headers/Command.hpp"

int PING(int poll_fd, Stock *Stock)
{
//	std::cout << "User IRSSI = " <<  Stock->User << std::endl;
	int a;
	
	a = Stock->User;
	a++;
	if(send(poll_fd, "PONG :ft_irc\n", 13, 0) != -1)
		return(1);
/*	for (int check = 0; check < Stock->User_Count; check++)
	{
		if (poll_fd == Stock->client_fd[check])
			Stock->User = check;
	}*/
	return (0);
}
