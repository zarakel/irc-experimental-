#include "../headers/headers.hpp"
#include "../headers/Privmsg.hpp"

int PRIVMSG(int poll_fd, Stock *Stock)
{
	int user_check = -1;
	int channel_check = -1;
	std::string tmp;
	size_t size = (Stock->Identities.size() <= (size_t)Stock->Channel_Count) ?
	Stock->Identities.size() : (size_t)Stock->Channel_Count;

	for (size_t search = 0; search < size; search++) // boucle user
	{
		if (search < Stock->Identities.size() && Stock->line[1] == Stock->Identities[search][0])
		{
			user_check = search;
			break;
		}

		if (search < (size_t)Stock->Channel_Count && Stock->line[1] == Stock->Channels[search][0])
		{
			channel_check = search;
			break;
		}

		else if (search + 1 == size && (user_check == -1 && channel_check == -1))
		{
			if (send(poll_fd, "Bad params: The user isn't found\r\n", 34, 0) == -1)
				perror("send :");
			Stock->line.clear();
			return (411);
		}
	}

	if (Stock->line[2] == "\0")
	{
		if (send(poll_fd, "Bad params: No text to send\r\n", 29, 0) == -1)
			perror("send :");
		Stock->line.clear();
		return (412);
	}

	if (user_check >= 0)
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
			tmp = Stock->Identities[Stock->User][0];
			tmp += ": ";
			tmp += Stock->line[2];
			tmp += "\n\r\0";
			size_t size = tmp.size();
//			std::cout << tmp << " && size = " << size << std::endl;
/*			if (send(Stock->client_fd[user_check], static_cast<void *>(&tmp), size - 1, 0) == -1)
				perror("send :");
			if (send(Stock->client_fd[user_check], "\n", 1, 0) == -1)
				perror("send :");*/
			for (size_t c = 0; c < size; c++)
			{
				if (send(Stock->client_fd[user_check], &tmp[c], 1, 0) == -1)
				perror("send :");
			}
			tmp.clear();
			Stock->line.clear();
			return (1);
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
//				std::cout << "bouh" << std::endl;
				if (send(Stock->client_fd[i], static_cast<void *>(&tmp), tmp.size() + 1, 0) == -1)
					perror("send :");
				tmp.clear();
				Stock->line.clear();
			//	return (1);
			}
			chan_roll = 0;
		}
	}
	Stock->line.clear();
	return (0);
}
