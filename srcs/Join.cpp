#include "../headers/headers.cpp"
#include "../headers/Join.hpp"

void	Join(int poll_fd, Stock * Stock)
{
	if (Stock->line[1][0] != '#' | Stock->line[1][0] != '&' |
		Stock->line[1][0] != '+' | Stock->line[1][0] != '!')
	{
		if (send(poll_fd, "Bad Param: # or & are not there\r\n", 33, 0)
			== -1)
			perror("send");
		Stock->line.clear();
	}
	if (Stock->line.size() > 200)
	{
		if (send(poll_fd, "Bad Param: chan name too long\r\n", 31, 0)
			== -1)
			perror("send");
		Stock->line.clear();
	}
	for ( int i = 0; Stock->line[1][i] != '\n' | Stock->line[1][i] != '\r';
		i++)
	{
		if (Stock->line[1][i] == ' ' | Stock->line[1][i] == ',' |
			Stock->line[1][i] == 7)
		{
			if (send(poll_fd, "Bad Param: chan name contain wrong 
			characters\r\n", 31, 0) == -1)
				perror("send");
			Stock->line.clear();
		}
	}
	for ( int i = 0; Stock->Channels[i].empty() != 0; i++;
	{
		if ( Stock->line[1].compare(Stock.Channels[i]) == 0)
		// si on repere un channel déja existant 	
}
