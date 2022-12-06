/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:31:27 by juan              #+#    #+#             */
/*   Updated: 2022/12/06 11:08:28 by jbuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	Command: KICK
	Parameters: <channel> <user> [<comment>]

	The KICK command can be  used  to  forcibly  remove  a  user  from  a
	channel.   
    It  'kicks  them  out'  of the channel (forced PART).

	Only a channel operator may kick another user out of a  channel.
	Each  server that  receives  a KICK message checks that it is valid
	(ie the sender is actually a  channel  operator)  before  removing
	the  victim  from  the channel.

	Numeric Replies:

			ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
			ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
			ERR_NOTONCHANNEL

	Examples:

	KICK &Melbourne Matthew         ; Kick Matthew from &Melbourne

	KICK #Finnish John :Speaking English
									; Kick John from #Finnish using
									"Speaking English" as the reason
									(comment).

	:WiZ KICK #Finnish John         ; KICK message from WiZ to remove John
									from channel #Finnish

	NOTE:
		It is possible to extend the KICK command parameters to the
	following:

	<channel>{,<channel>} <user>{,<user>} [<comment>]
*/

#include "../headers/headers.hpp"
#include "../headers/Kick.hpp"
#include "../headers/answer.hpp"
#include "../headers/tools.hpp"
//# define NTC_KICK(channel, usr, reason) ("KICK " + channel  + " " + usr + " " + reason)

int KICK(int poll_fd, Stock *Stock)
{
    std::string        channels;
    std::vector<std::string>	    toKick;  // remove an user
    std::string                     comment; //why me? give a reason
    std::vector<std::string>        victim; //select form list of User registed
    std::string                     chl; //select the one from channel to kick

	int check = 1;
    if ( Stock->line.size() < Stock->full_command["KICK"].size()) 
    {
		MessageG( poll_fd, ERR_NEEDMOREPARAMS, ":Need more parameters", Stock);
		Stock->line.clear();
		return (1);
    }
    channels = Stock->line[1];
 	toKick = ft_split(Stock->line[2], ",");

	for (size_t i = 0; i < toKick.size(); i++)
		std::cout << toKick[i] << std::endl;
    
    comment = ":";
    if (Stock->line.size() == Stock->full_command["KICK"].size() + 1)
        comment = ft_addback(Stock->line, " ", 2);

       //chl = Stock->getChannelByName( channels[i] );
        for (int a = 0; a < (int)Stock->Channels.size() ; a++)
	{
		if (Stock->Channels[a][0].compare(channels) == 0)
        	    chl = channels;
	}
        if (chl.empty())
	{
            MessageG( poll_fd, ERR_NOSUCHCHANNEL, channels, Stock);
		check = 0;
		std::cout << "la" << std::endl;
	}
        //if channel doesnt exit
        if (Stock->authentified[Stock->User] == 0)
	{
            MessageG( poll_fd, ERR_NOTREGISTERED, ":You have not registered", Stock);
		check = 0;
		std::cout << "li" << std::endl;
	}
        //if user isnt on channel
	
	std::cout << "before 1st for" << std::endl;
	
        for (size_t roll = 0; roll < Stock->Channels_Users[channels].size(); roll++)
        {
            if (Stock->Channels_Users[channels][roll] == Stock->Identities[Stock->User][0])
            {
            //if user is not channel operator
                if (Stock->Channels_Op[channels][Stock->User] == 0)
		{
                   MessageG( poll_fd, ERR_CHANOPRIVSNEEDED, channels, Stock);
			check = 0;
		std::cout << "lo" << std::endl;
		}
                //test//
               	break;
            }
            else if (roll + 1 == Stock->Channels_Users[channels].size())
		{
                	MessageG( poll_fd, ERR_NOTONCHANNEL, channels, Stock);
			check = 0;
		std::cout << "le" << std::endl;
		}
        
       } 
        //find toKick

	int a = 0;
	std::cout << "before 2nd for" << std::endl;
	std::cout << Stock->Channels_Users[channels].size() << std::endl;
        for (size_t j = 0; j < Stock->Channels_Users[channels].size(); j++)
        {
            if (Stock->Channels_Users[channels][j] == toKick[a])
		{
/*			for (size_t pou = 0; pou < Stock->Identities.size(); pou++)
			{
				if (Stock->Channels_Users[channels[0]][j]
			}*/
			std::cout << toKick[a] << std::endl;
			std::cout << Stock->Channels_Op[channels].size() << std::endl;
			std::cout << "j is " << j << std::endl;
			std::cout << toKick[a] << " is op = " << Stock->Channels_Op[channels][j] << std::endl;
		/*	if (Stock->Channels_Op[channels].size() > 2 &&
			Stock->Channels_Op[channels][j] == 1)
			{
                   		MessageG( poll_fd, ERR_CHANOPRIVSNEEDED,
				"Bad Usage: Op is alone on " + channels, Stock);
				check = 0;
			}*/
                	victim.push_back(toKick[a]);
			std::cout << victim[0] << std::endl;
		}
            // if victim is not a valid nick
			// if victim is not on channel
		else if (j + 1 == Stock->Channels_Users[channels].size()
		&& victim.size() == 0)
        	{
			MessageG( poll_fd, ERR_NOTONCHANNEL, channels, Stock );
			std::cout << "victim size is " << victim.size() << std::endl;
			check = 0;
			std::cout << "ly" << std::endl;
			break;
		}

		else if (j + 1 == Stock->Channels_Users[channels].size()
		&& a + 1 < (int)toKick.size())
		{
			j = -1;
			a++;
		}
	}
/*	a = 0;
	for (; victim[a].empty() == 0; a++)
        {
			
			MessageG( poll_fd, ERR_NOSUCHNICK, victim[a], Stock );
			check = 0;
	}
			//std::vector<User*> usrs = chl->getMembers();
	*/
	if (check == 0)
	{
		std::cout << "kilukru" << std::endl;
		channels.clear();
		comment.clear();
		chl.clear();
		victim.clear();
		toKick.clear();
       		Stock->line.clear(); 
		return (0);
	}

	std::cout << "before 3rd for" << std::endl;
	a = 0;
	int z = 0;
            for (; a < (int)victim.size();)
            {
			std::cout << "yo" << std::endl;
			while (z < (int)Stock->Identities.size())
			{
				for (int y = 0; 
				Stock->Channels_Users[channels].size() != 0 && y < 
				(int)Stock->Channels_Users[channels].size(); y++)
				{
					if (z < (int)Stock->Identities.size() &&
					Stock->Identities[z][0] ==
					Stock->Channels_Users[channels][y])
					{
					//	MessageG(Stock->client_fd[z++],
						MessageG(Stock->client_fd[z],
						channels + " " + victim[a] + " " +
						comment, "have been Kicked !", Stock);
						Stock->Channels_Invite[channels][z] = 0;
					}
				/*	if (y + 1 == (int)Stock->Channels_Users
					[channels].size() && b + 1 < channels.size())
					{
						y = -1;
						b++;
					}*/
				/*	else if (y + 1 == (int)Stock->Channels_Users
					[channels].size() && b + 1 == channels.size())
						break;
					std::cout << "forever" << std::endl;*/
				}
				std::cout << "forever2" << std::endl;
				z++;
			}
			if (a + 1 < (int)victim.size())
			{
			//	b = 0;
				z = 0;
				a++;
			}
			else if (a + 1 == (int)victim.size())
				break;
		//send_notice(user, *usrs[k], NTC_KICK(chl->getName(), victim->getNick(), comment));
		}
	std::cout << "before 4th for part 1" << std::endl;
		a = 0;	
//		z = 0;
		std::vector<std::string>::iterator it;
		it = Stock->Channels_Users[channels].begin();
		for (size_t roll = 0; roll < Stock->Channels_Users[channels].size();
		roll++)
		{
			if (victim[a] == Stock->Channels_Users[channels][roll])
			{
				std::cout << "a = " << a << std::endl;
				std::cout << "victim[" << a << "] = " << victim[a]<< std::endl;
				std::cout << "User[" << roll <<"] = " << Stock->Channels_Users[channels][roll] << " && chan is " << channels << std::endl;
			//	Stock->Channels_Users[channels][roll].clear();
			/*	for (size_t roll2 = roll; roll2 + 1 < Stock->Channels_Users[channels[z]].size() && Stock->Channels_Users[channels[z]][roll2 + 1].empty() == 0; roll2++)
				{
					Stock->Channels_Users[channels[z]][roll2 + 1].swap(Stock->Channels_Users[channels[z]][roll2]);
					Stock->Channels_Invite[channels[z]][roll2 + 1] = 
					Stock->Channels_Invite[channels[z]][roll2];
					Stock->Channels_Op[channels[z]][roll2 + 1] = 
					Stock->Channels_Op[channels[z]][roll2];
				}*/
			//	Stock->Channels_Users[channels[z]][roll].resize(0);
		//		it = Stock->Channels_Users[channels[z]][roll];
				std::cout << "Channels_users size = " << Stock->Channels_Users.size() << std::endl;
				std::cout << "CHannels_users[" << channels << "] size = " << Stock->Channels_Users[channels].size() << std::endl;
				int check_del = 0;
				int check_op = 0;
				if (Stock->Channels_Users[channels].size() > 1
				&& roll == 0)
					check_op = 1;
				if (Stock->Channels_Users[channels].size() > 0)
				{
					if (Stock->Channels_Users[channels].size() == 1)
						check_del = 1;
					std::cout << "it is " << *it << std::endl;
					Stock->Channels_Users[channels].erase(it);
					if (check_op == 1)
					{
						std::cout << "incheckop" << std::endl;
						Stock->Channels_Op[channels]
						[Stock->User] = 0;
						for (size_t a = 0; a <
						Stock->Channels_Op[channels].size();a++)
						{
							if ((int)a != Stock->User)
								Stock->Channels_Op
								[channels][a] = 1;
						}	
					}
				}
				std::cout << "User[" << roll <<"] = " << Stock->Channels_Users[channels][roll] << " && chan is " << channels << std::endl;
				std::cout << "CHannels_users size = " << Stock->Channels_Users.size() << std::endl;
				std::cout << "CHannels_users[" << channels << "] size = " << Stock->Channels_Users[channels].size() << std::endl;
				if ((check_del = 1 ||
				roll + 1 == Stock->Channels_Users[channels].size()))
			//	&& z + 1 < (int)channels.size())
				{
					std::cout << "coucou" << std::endl;
					if (Stock->Channels_Users[channels].size() == 0)
					{
						Stock->Channels_Users.erase(channels);
						for (size_t chan = 0; chan < Stock->Channels.size(); chan++)
						{
							if (Stock->Channels[chan][0] ==
							channels && 
							Stock->Channels_Users
							[channels].size() == 0)
								Stock->Channels.erase
								(chan);
							if (Stock->Channels.size() == 0)
							{
								Stock->Channel_Count = 0;
								victim.clear();
								toKick.clear();
								channels.clear();
								comment.clear();
								chl.clear();
								Stock->line.clear();
								return (0);
							}
						}
					}
				//	z++;
					it = Stock->Channels_Users[channels].begin();
					roll = 0;
					//it = Stock->Channels_Users[channels[z]].begin();
				}
				std::cout << "bout du if" << std::endl;
			}	
			it++;
			std::cout << "before raz" << std::endl;
			std::cout << "roll = " << roll << " && " << "limite = " <<
			Stock->Channels_Users[channels].size() << std::endl;
			if (roll + 1 == Stock->Channels_Users[channels].size()
			&& a + 1 < (int)victim.size())
			{
				std::cout << "raz" << std::endl;
				roll = -1;
				it = Stock->Channels_Users[channels].begin();
			//	z = 0;
				a++;
			}
		}
		// Delete chan if usr leaving is the last usr in chan
		// if (chl->getNbMembers() == 0)
		// 	chl->deleteChannel(chl, &user);
//       }
 //   }
/*	int a = 0;
	std::cout << "before 4th for part 2" << std::endl;
	for (size_t del = 0; del < Stock->Channels.size(); del++)
	{
		std::cout << "Chan is " << channels[a] << " and his size is " << Stock->Channels_Users[channels[del]].size() << std::endl;
		if (channels[a] == Stock->Channels[del][0] && Stock->Channels_Users[channels[a]].size() == 0)
		{
			std::cout << "bobo" << std::endl;
		//	Stock->Channels_Users[channels[del]].clear();
		//	Stock->Channels_Users[channels[del]].resize(0);
			//Stock->Channels_Users[Stock->Channels[del][0]].erase(del);
			while (channels[a] != Stock->Channels[del][0])
				a++;
			std::cout << "yo" << std::endl;
	//		std::vector<std::string>::iterator ite = Stock->Channels[del].begin();
//			for (size_t y = 0; y < Stock->Channels[y].size(); y++)
//				Stock->Channels[a][y].clear();
			std::cout << "yo" << std::endl;
//			Stock->Channels[a].clear();
//			std::cout << "yo" << std::endl;
			Stock->Channels[a].resize(0);
			for (size_t h = a; h + 1 < Stock->Channels.size() && Stock->Channels[h + 1].empty() == 0; h++)
			{
				Stock->Channels[h + 1].swap(Stock->Channels[h]);
				if (h + 1 == Stock->Channels.size())
					Stock->Channels.erase(h + 1);
			}
	//		Stock->Channels[del].erase(ite);
		//	Stock->Channels.resize()
			Stock->Channels.erase(del);
			std::cout << "yo" << std::endl;
		}
		std::cout << "Chan size " << Stock->Channels.size() << std::endl; 
		if (Stock->Channels.size() == 0)
			Stock->Channel_Count = 0;
		std::cout << "del " << del << std::endl;
		if (del + 1 == Stock->Channels.size() && a + 1 < (int)channels.size())
		{
			del = -1;
			a++;
		}
		else if (del + 1 == Stock->Channels.size() && a + 1 == (int)channels.size())
			break;
			
	}*/
	victim.clear();
	toKick.clear();
	channels.clear();
	comment.clear();
	chl.clear();
	Stock->line.clear();
    return (0);
}
