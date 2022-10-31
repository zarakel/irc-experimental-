#include "../headers/Command.hpp"
#include "../headers/Privmsg.hpp"

int PRIVMSG(int poll_fd, Stock *Stock)
{
	if (send(poll_fd, const_cast<char*>(Stock->line[2].c_str()),
	Stock->line[2].size(), 0) == -1)
		perror("send");
	return (45676);
}
