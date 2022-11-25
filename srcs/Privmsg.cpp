#include "../headers/headers.hpp"
#include "../headers/Privmsg.hpp"
#include "../headers/answer.hpp"

int PRIVMSG(int poll_fd, Stock *Stock)
{
	int user_check[15] = -1;
	int channel_check[15] = -1;
	int check = 0;
	std::string tmp;
	size_t size = (Stock->Identities.size() >= (size_t)Stock->Channel_Count) ?
	Stock->Identities.size() : (size_t)Stock->Channel_Count;
	std::vector<std::string> tmp_nicks;
	std::vector<std::string> tmp_chans;

	for (size_t i = 0; i < Stock->line[1].size(); i++)
	{
		if (Stock->line[1][i] == ',' && Stock->line[1][i + 1] != '\n' 
		&& Stock->line[1][i + 1] == '\r' && Stock->line[1][i + 1] == '\0'
		&& Stock->line[1][i + 1] == ' ' && Stock->line[1][i + 1] != '+' 
		&& Stock->line[1][i + 1] == '#' && Stock->line[1][i + 1] == '!'
		&& Stock->line[1][i + 1] == '&' )
		{
			check++;
			i++;
		}
		
			tmp_nicks[check].push_back(Stock->line[1][i]);
		if (Stock->line[1][i + 1] != '\n' 
		&& Stock->line[1][i + 1] == '\r')
		{
			tmp_nicks[check + 1].push_back("\0");
			check = 0;
			break;
		}
	}
	
	for (size_t search = 0; search < size; search++) // boucle user
	{
		if (search < Stock->Identities.size() && tmp_nicks[check] == Stock->Identities[search][0])
			user_check[check++] = search;

		if (search < (size_t)Stock->Channel_Count && Stock->line[1] == Stock->Channels[search][0])
			channel_check = search;

		else if (search + 1 == size && (user_check == -1 && channel_check == -1))
		{
		/*	if (send(poll_fd, "Bad params: The user isn't found\r\n", 34, 0) == -1)
				perror("send :");*/
			MessageG(poll_fd, ERR_NOSUCHNICK, ": No target found", Stock);
			Stock->line.clear();
			return (0);
		}
	}

/*	if (Stock->line[2].compare("\0") == 0)
	{
		if (send(poll_fd, "Bad params: No text to send\r\n", 29, 0) == -1)
			perror("send :");
		Stock->line.clear();
		return (412);
	}*/

	if (check >= 0 && user_check >= 0)
	{
//		std::cout << "l'user est " << Stock->line[1] << std::endl;
//		std::cout << "l'user check est " << Stock->Identities[user_check][0] << " et le fd est " << Stock->client_fd[user_check] << std::endl;
	/*		for (int i = 0; i <= Stock->User_Count; i++)
			{
				if (Stock->client_fd[i] == user_check)
				{
					user_check = i;
					break;
				}
			}*/
//			std::cout << "Stock->client_fd[" << user_check << "] = " << Stock->client_fd[user_check] << std::endl;
		for (size_t roll = 0; roll <= check; roll++)
		{
			tmp = Stock->Identities[Stock->User][0];
			tmp += ": ";
			tmp += Stock->line[2];
			tmp += '\n';
			size_t size = tmp.size();
//			std::cout << tmp << " && size = " << size << std::endl;
/*			if (send(Stock->client_fd[user_check], static_cast<void *>(&tmp), size - 1, 0) == -1)
				perror("send :");
			if (send(Stock->client_fd[user_check], "\n", 1, 0) == -1)
				perror("send :");*/
			for (size_t c = 0; c < size; c++)
			{
				if (send(Stock->client_fd[user_check[roll]], &tmp[c], 1, 0) == -1)
				perror("send :");
			}
			tmp.clear();
			Stock->line.clear();
			return (1);
		}
	}
	int chan_roll = 0;
	if (channel_check >= 0 && Stock->Channels_Users[Stock->Channels[channel_check][0]].size() > 0)
	{
	//		std::cout << "le chan est " << Stock->line[1] << std::endl;
	//		std::cout << "le chan check est " << Stock->Channels[channel_check][0] << std::endl;
		for( int i = 0; i < (int)Stock->Channels_Users[Stock->Channels[channel_check][0]].size(); i++)
		{
			while (Stock->Identities[i][0] != Stock->Channels_Users
			[Stock->Channels[channel_check][0]][chan_roll] &&
			(size_t)chan_roll < Stock->Channels_Users[Stock->Channels
			[channel_check][0]].size())
				chan_roll++;
			if (Stock->Identities[i][0] == Stock->Channels_Users[Stock->Channels[channel_check][0]][chan_roll])
			{
				int me_check = 0;
				while(poll_fd != Stock->client_fd[me_check])
					me_check++;
				std::string tmp = Stock->Identities[me_check][0];
				tmp += " : ";
				tmp += Stock->line[2];
				tmp += '\n';
				size_t size = tmp.size();
//				std::cout << "bouh" << std::endl;
				for (size_t c = 0; c < size; c++)
				{
					if (send(Stock->client_fd[chan_roll], &tmp[c], 1, 0) == -1)
					perror("send :");
				}
				size = 0;
		/*		if (send(Stock->client_fd[i], static_cast<void *>(&tmp), tmp.size() + 1, 0) == -1)
					perror("send :");*/
				tmp.clear();
			//	Stock->line.clear();
			//	return (1);
			}
			chan_roll = 0;
		}
	}
	Stock->line.clear();
	return (0);
}
