#include "../headers/headers.hpp"
#include "../headers/Privmsg.hpp"

int PRIVMSG(int poll_fd, Stock *Stock)
{
	int user_check = -1;
	int channel_check = -1;
	std::string tmp;

	for (int search = 0; search < (int)Stock->Identities.size() + Stock->Channel_Count; search++) // boucle user
	{
		if (search < (int)Stock->Identities.size() && Stock->line[1] == Stock->Identities[search][0])
		{
			user_check = search;
			break;
		}

		if (search < Stock->Channel_Count && Stock->line[1] == Stock->Channels[search][0])
		{
			channel_check = search;
			break;
		}

		else if (search + 1 == (int)Stock->Identities.size() + Stock->Channel_Count && (user_check == -1 && channel_check == -1))
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
		std::cout << "l'user est " << Stock->line[1] << std::endl;
		std::cout << "l'user check est " << Stock->Identities[user_check][0] << " et le fd est " << Stock->client_fd[user_check] << std::endl;
	/*		for (int i = 0; i <= Stock->User_Count; i++)
			{
				if (Stock->client_fd[i] == user_check)
				{
					user_check = i;
					break;
				}
			}*/
			std::cout << "Stock->client_fd[" << user_check << "] = " << Stock->client_fd[user_check] << std::endl;
			std::cout << Stock->Identities[user_check][0] << std::endl;
			std::cout << Stock->line[2] << std::endl;
			tmp = Stock->Identities[user_check][0];
			tmp += ": ";
			tmp += Stock->line[2];
			tmp += "\n\r\0";
			size_t size = tmp.size();
			std::cout << tmp << " && size = " << size << std::endl;
/*			if (send(Stock->client_fd[user_check], static_cast<void *>(&tmp), size - 1, 0) == -1)
				perror("send :");
			if (send(Stock->client_fd[user_check], "\n", 1, 0) == -1)
				perror("send :");*/
			for (size_t c = 0; c < size; c++)
			{
				if (send(Stock->client_fd[user_check], &tmp[c], 1, 0) == -1)
				perror("send :");
			}
	}
	int chan_roll = 0;
	if (channel_check >= 0)
	{
			std::cout << "le chan est " << Stock->line[1] << std::endl;
			std::cout << "le chan check est " << Stock->Channels[channel_check][0] << std::endl;
			for( int i = 0; i < (int)Stock->Channels_Users[Stock->Channels[channel_check][0]].size(); i++)
			{	
				while (Stock->Identities[i][0] != Stock->Channels_Users[Stock->Channels[channel_check][0]][chan_roll])
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
					if (send(Stock->client_fd[i], static_cast<void *>(&tmp), tmp.size() + 1, 0) == -1)
						perror("send :");
				}
			}
	}
	Stock->line.clear();
	return (0);
}
