#include "../headers/headers.hpp"
#include "../headers/Privmsg.hpp"
#include "../headers/answer.hpp"
#include "../headers/tools.hpp"

int PRIVMSG(int poll_fd, Stock *Stock)
{
	int user_check[15];
	int channel_check[15];
	int check_n = 0;
	int check_c = 0;
	int roll_n = 0;
	int roll_c = 0;
	std::string tmp;
	size_t size_c = (size_t)Stock->Channel_Count;
	size_t size_n = Stock->Identities.size();
	std::vector<std::string> tmp_nicks;
	std::vector<std::string> tmp_chans;
	int s = 0;

	user_check[0] = -1;
	channel_check[0] = -1;
	for (size_t c = 0; c < Stock->line[1].size(); c++)
	{
		if (Stock->line[1][c] == ',')
			c++;
		if ((Stock->line[1][s] == '#' || Stock->line[1][s] == '+'
		|| Stock->line[1][s] == '&' || Stock->line[1][s] == '!')
		&& (Stock->line[1][s + 1] != '\0' || Stock->line[1][s] == ' '))
		{
			for (; Stock->line[1][c]; c++)
			{
				tmp.push_back(Stock->line[1][c]);
				if (Stock->line[1][c + 1] == ','
				|| Stock->line[1][c + 1] == '\0')
					break;
			}
			tmp_chans.push_back(tmp);
			if (Stock->line[1][c + 1] == ',')
				s = c + 2;
			roll_c++;
			tmp.clear();
		}
		else if (Stock->line[1][s] && Stock->line[1][s] != '#' &&
		Stock->line[1][s] != '+' && Stock->line[1][s] != '&'
		&& Stock->line[1][s] != '!')
		{
			for (; Stock->line[1][c]; c++)
			{
				tmp.push_back(Stock->line[1][c]);
				if (Stock->line[1][c + 1] == ','
				|| Stock->line[1][c + 1] == '\0')
				//	tmp.push_back('\0');
					break;
			}
			tmp_nicks.push_back(tmp);
			if (Stock->line[1][c + 1] == ',')
				s = c + 2;
			roll_n++;
			tmp.clear();
		}
		if (c + 1 >= Stock->line[1].size())
			break;
	}  

/*	for (size_t roll = 0; roll < tmp_chans.size(); roll++)
		std::cout << tmp_chans[roll] << std::endl;*/
	if (roll_n > 0)
	{
		for (size_t search = 0; search < size_n; search++) // boucle user
		{
			if (tmp_nicks[check_n] == Stock->Identities[search][0])
			{
				user_check[check_n++] = search;
				search = -1;
			}
		}
	}

	if (roll_c > 0 && Stock->Channels.size() > 0)
	{
		for (size_t search = 0; search < size_c; search++) // boucle chan 
		{
			if (tmp_chans[check_c] == Stock->Channels[search][0])
			{
				channel_check[check_c++] = search;
				search = -1;
			}
	
		}
	}

	if (user_check[0] == -1 && channel_check[0] == -1)
	{
		/*	if (send(poll_fd, "Bad params: The user isn't found\r\n", 34, 0) == -1)
				perror("send :");*/
		MessageG(poll_fd, ERR_NOSUCHNICK, ": No target found", Stock);
		Stock->line.clear();
		return (0);
	}
/*	if (Stock->line[2].compare("\0") == 0)
	{
		if (send(poll_fd, "Bad params: No text to send\r\n", 29, 0) == -1)
			perror("send :");
		Stock->line.clear();
		return (412);
	}*/
	if (user_check[0] >= 0)
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
		for (size_t roll = 0; roll < (size_t)check_n; roll++)
		{
			tmp = ':' + Stock->line[1] + ' ' + Stock->line[0];
			tmp += ' ' + Stock->Identities[Stock->User][0];
			tmp += " :" + Stock->line[2];
			tmp += '\n';
			size_t size = tmp.size();
//			std::cout << tmp << " && size = " << size << std::endl;
/*			if (send(Stock->client_fd[user_check], static_cast<void *>(&tmp), size - 1, 0) == -1)
				perror("send :");
			if (send(Stock->client_fd[user_check], "\n", 1, 0) == -1)
				perror("send :");*/
			for (size_t c = 0; c < size; c++)
			{
				if (send(Stock->client_fd[user_check[roll]], &tmp[c],
				1, 0) == -1)
				perror("send :");
			}
			tmp.clear();
		}
	}
/*	int chan_roll = 0;
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
				if (send(Stock->client_fd[i], static_cast<void *>(&tmp), tmp.size() + 1, 0) == -1)
					perror("send :");
				tmp.clear();
			//	Stock->line.clear();
			//	return (1);
			}
			chan_roll = 0;
		}
	}*/
	int a = 0;
	if (channel_check[0] >= 0)
	{
		for (size_t roll = 0; a <
		(int)Stock->Channels.size(); roll++)
		{
			if (Stock->Identities[Stock->User][0] ==
			Stock->Channels_Users[tmp_chans[a]][roll])
			{
				break;
			}
			else if ( roll + 1 ==
			Stock->Channels_Users[tmp_chans[a]].size() &&
			a + 1 < (int)tmp_chans.size())
			{
				a++;
				roll = -1;
			}
			else if  ( roll + 1 ==
			Stock->Channels_Users[tmp_chans[a]].size() &&
			a + 1 == (int)tmp_chans.size())
			{
				MessageG(poll_fd, ERR_CANNOTSENDTOCHAN,
				"Bad Usage: You're not in the channel", Stock);
				tmp.clear();
				tmp_nicks.clear();
				tmp_chans.clear();
				Stock->line.clear();
				return (1);
			}
		}
		while ( a < (int)tmp_chans.size())
		{		
			for (size_t roll = 0; roll <
			(size_t)Stock->Channels_Users[tmp_chans[a]].size(); roll++)
			{
				tmp = ':' + Stock->line[1] + ' ';
				tmp += Stock->line[0] + ' ';
				tmp += Stock->Identities[Stock->User][0];
				tmp += " :" + Stock->line[2] + '\n';
				size_t size = tmp.size();
//		std::cout << tmp << " && size = " << size << std::endl;
/*		if (send(Stock->client_fd[user_check], static_cast<void *>(&tmp), size - 1, 0) == -1)
			perror("send :");
		if (send(Stock->client_fd[user_check], "\n", 1, 0) == -1)
			perror("send :");*/
				int tmp_fd = -1;
				for (size_t z = 0; z < Stock->Identities.size(); z++)
				{
					if (Stock->Identities[z][0] ==
					Stock->Channels_Users[tmp_chans[a]][roll])
					{
						tmp_fd = z;
						break;
					}
				}
				for (size_t c = 0; c < size && tmp_fd != -1; c++)
				{
					if (send(Stock->client_fd[tmp_fd], &tmp[c], 1, 0) == -1)
					perror("send :");
				}
				tmp.clear();
			}
			a++;
		}
	}
	tmp.clear();
	tmp_nicks.clear();
	tmp_chans.clear();
	Stock->line.clear();
	return (0);
}
