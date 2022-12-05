#include "../headers/headers.hpp"
#include "../headers/answer.hpp"
#include "../headers/Part.hpp"
#include "../headers/tools.hpp"


int PART(int poll_fd, Stock *Stock)
{
    std::vector<std::string>        channels;
    std::string                     comment; //why me? give a reason
    std::string                     chl; //select the one from channel to kick
	std::string 			victim;

	int check = 1;
    if ( Stock->line.size() < Stock->full_command["PART"].size())
    {
		MessageG( poll_fd, ERR_NEEDMOREPARAMS, ":Need more parameters", Stock);
		Stock->line.clear();
		return (1);
    }
    channels = ft_split(Stock->line[1], ",");

    comment = ":";
    if (Stock->line.size() == Stock->full_command["PART"].size() + 1)
        comment = ft_addback(Stock->line, " ", 2);

       //chl = Stock->getChannelByName( channels[i] );
	int b = 0;
        for (int a = 0; a < (int)Stock->Channels.size() ; a++)
	{
		if (Stock->Channels[a][0].compare(channels[b]) == 0)
		{
        	    chl = channels[b++];
			a = -1;
		}
	}
        if (chl.empty())
	{
            MessageG( poll_fd, ERR_NOSUCHCHANNEL, channels[b], Stock);
		check = 0;
	}
        //if channel doesnt exit
        if (Stock->authentified[Stock->User] == 0)
	{
            MessageG( poll_fd, ERR_NOTREGISTERED, ":You have not registered", Stock);
		check = 0;
	}
        //if user isnt on channel

	victim = Stock->Identities[Stock->User][0];
	b = 0;
	int match = 0;
	for (size_t j = 0; j < Stock->Channels_Users[channels[b]].size(); j++)
	{
		if (Stock->Channels_Users[channels[b]][j] == victim)
		{
			match = 1;
			continue;
		}
		else if (match == 0 && 
		j + 1 == Stock->Channels_Users[channels[b]].size())
		{
			MessageG( poll_fd, ERR_NOTONCHANNEL,
			channels[b], Stock );
			check = 0;
			break;
		}

		else if (j + 1 == Stock->Channels_Users[channels[b]].size()
		&& b + 1 < (int)channels.size())
		{
			match = 0;
			j = -1;
			b++;
		}
	}

	if (check == 0)
	{
		channels.clear();
		chl.clear();
		comment.clear();
		Stock->line.clear();
	}			

	b = 0;
	int z = 0;
	while (z < (int)Stock->Identities.size())
	{
		for (int y = 0;
		Stock->Channels_Users[channels[b]].size() != 0 && y <
		(int)Stock->Channels_Users[channels[b]].size(); z++)
		{
			if (z < (int)Stock->Identities.size() &&
			Stock->Identities[z][0] ==
			Stock->Channels_Users[channels[b]][y])
			{
				MessageG(Stock->client_fd[z],
				channels[b] + " " + victim + " " +
				comment, ":Parted !", Stock);
				y++;
			}
			if ( z + 1 == (int)Stock->Identities.size())
				break;
		}
		if ( b + 1 < (int)channels.size())
		{
			z = -1;
			b++;
		}
		else if ( b + 1 == (int)channels.size())
			break;
	}

	b = 0;
	std::vector<std::string>::iterator it;
	it = Stock->Channels_Users[channels[b]].begin();
	for (size_t roll = 0; roll < Stock->Channels_Users[channels[b]].size();
	roll++)
	{
		if (victim == Stock->Channels_Users[channels[b]][roll])
		{
			int check_del = 0;
			int check_op = 0;
			if (Stock->Channels_Users[channels[b]].size() > 1
			&& roll == 0)
				check_op = 1;
			if (Stock->Channels_Users[channels[b]].size() > 0)
			{
				if (Stock->Channels_Users[channels[b]].size()
				== 1)
					check_del = 1;
				Stock->Channels_Users[channels[b]].erase(it);
				if (check_op == 1)
				{
					Stock->Channels_Op[channels[b]]
					[Stock->User] = 0;
					for (size_t a = 0; a <
					Stock->Channels_Op[channels[b]].size();
					a++)
					{
						if ((int)a != Stock->User)
							Stock->Channels_Op
							[channels[b]][a] = 1;
					}
				}
			}
			if ((check_del = 1 ||
			roll + 1 == Stock->Channels_Users[channels[b]].size()))
			{
				if (Stock->Channels_Users[channels[b]].size() == 0)
				{
					Stock->Channels_Users.erase(channels[b]);
					for (size_t chan = 0; chan < Stock->Channels.size(); chan++)
					{
						if (Stock->Channels[chan][0] ==
						channels[b] &&
						Stock->Channels_Users
						[channels[b]].size() == 0)
							Stock->Channels.erase
							(chan);
						if (Stock->Channels.size() == 0)
						{
							Stock->Channel_Count = 0;
							victim.clear();
							channels.clear();
							comment.clear();
							chl.clear();
							Stock->line.clear();
							return (0);
						}
					}
				}
				it = Stock->Channels_Users[channels[b]].begin();
				roll = 0;
			}
		}
		it++;
		if (roll + 1 == Stock->Channels_Users[channels[b]].size()
		&& b + 1 < (int)channels.size())
		{
			roll = -1;
			b++;
			it = Stock->Channels_Users[channels[b]].begin();
		//	z = 0;
		}
	}
	
	victim.clear();
	channels.clear();
	comment.clear();
	chl.clear();
	Stock->line.clear();
	return (0);	
}	
