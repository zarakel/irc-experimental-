#include "../headers/headers.hpp"
#include "../headers/Join.hpp"

int	JOIN(int poll_fd, Stock * Stock)
{
	std::vector<std::string > tmp_Channel;
	std::vector<std::string > tmp_Key;
	std::string tmp;
	int	it = 0;
	int	o = 0;
	//int	tmp_Channel_Check[10];

// vérif si le 1er caractère est conforme
	if (Stock->line[1][0] != '#' && Stock->line[1][0] != '&' &&
		Stock->line[1][0] != '+' && Stock->line[1][0] != '!')
	{
		if (send(poll_fd, "Bad Param: +, !, # or & are not there\r\n",
		39, 0) == -1)
			perror("send");
		Stock->line.clear();
		return (83);
	}

// vérif si la ligne est plus grande que 50 caracteres
	if (Stock->line.size() > 50)
	{
		if (send(poll_fd, "Bad Param: chan name too long\r\n", 31, 0)
			== -1)
			perror("send");
		Stock->line.clear();
		return (862);
	}

// vérif si plusieurs channels sont donnés et stockage
	for ( int i = 0; Stock->line[1][i]; i++)
	{
		if (Stock->line[1][i] == ' ' | Stock->line[1][i] == 7)
		{
			if (send(poll_fd, "Bad Param: chan name contain wrong characters\r\n", 48, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (882);
		}
		tmp.push_back(Stock->line[1][i]);
		if ( Stock->line[1][i + 1] == '\0'
		| Stock->line[1][i + 1] == ',' )
		{
			tmp_Channel.push_back(tmp);
			tmp.clear();
		}
		if (Stock->line[1][i + 1] == ',' &&
		(Stock->line[1][i + 2] == '#' | Stock->line[1][i + 2] == '&'
		| Stock->line[1][i + 2] == '+' | Stock->line[1][i + 2] == '!'))
		{
			i++;
			it++;
		}
		else if (Stock->line[1][i + 1] == ',' &&
	(Stock->line[1][i + 2] != '#' | Stock->line[1][i + 2] != '&'
	| Stock->line[1][i + 2] != '+' | Stock->line[1][i + 2] != '!'))
		{
			if (send(poll_fd, "Bad Param: chan name contain wrong characters\r\n", 48, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (882);
		}
	}
	tmp_Channel.push_back("\0");
	tmp.clear();
	for (int i = 0; i <= it; i++)
		tmp_Key.push_back("\0");
	it = 0;
// vérif des keys
	for ( int i = 0; Stock->line[2][i] && 
	Stock->line[2][i] != '\n' | Stock->line[2][i] != '\r'; i++)
	{
		if (Stock->line[2][i] == ' ' | Stock->line[2][i] == 7)
		{
			if (send(poll_fd, "Bad Param: key contain wrong characters\r\n", 41, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (883);
		}
		tmp.push_back(Stock->line[2][i]);
		it++;
		if ( Stock->line[2][i + 1] == '\0'
		| Stock->line[2][i + 1] == ',' )
		{
			tmp_Key[o].replace(0, it, tmp);
			std::cout << "key = "<< tmp_Key[o] << std::endl;
			tmp.clear();
		}
//		tmp_Key[it] = Stock->line[2][i];
		if (Stock->line[2][i + 1] == ',' &&
		Stock->line[2][i + 2] == ',')
		{
			it = 0;
			i++;
			o++;
		}
	}
	o = 0;
// vérif si channel existe déja
	for ( int i = 0; Stock->Channel_Count > 0 && i <= Stock->Channel_Count
	&& tmp_Channel[o].compare("\0") != 0; i++)
	{
		// si on repere un channel déja existant
		if ( i < Stock->Channel_Count && 
		tmp_Channel[o] == Stock->Channels[i][0] &&
		tmp_Key[o] == Stock->Channels[i][1])
// l'idée, c'est que si key n'existe pas, on mets '\0'
		{
// On part du postulat qu\'on a toujours le meme nombre d'info et que l'ordre desdonnées utilisateurs (ip, nick, user) n'a pas d'importance
			if (Stock->Identities[Stock->User][0] != 
			Stock->Channels_Users[Stock->Channels[i][0]][0])
			{
				Stock->Channels_Users
				[Stock->Channels[i][0]].push_back
				(Stock->Identities[Stock->User][0]);
				if (send(poll_fd,
				"JOIN (existing channel) complete\n\r", 34, 0)
				== -1)
					perror("send");
				it =
				Stock->Channels_Users
				[Stock->Channels[i][0]].size();
				for (int z =
				Stock->Identities[Stock->User].size(); 
				z >= it; it++)
				{
					Stock->Channels_Users
					[Stock->Channels[i][0]].push_back
					(Stock->Identities[Stock->User][it]);
				}
			}
// le if enregistre l'ip de l'user actuel si il ne l'a pas déja
// probleme : Je n'enregistre pas le nick et le user 

			/*tmp = Stock->line[0];
			tmp += ' ';
			tmp += tmp_Channel[o];
			if (send(poll_fd, static_cast<void *>(&tmp), tmp.length(), 0) == -1)
				perror("send");
			tmp.clear();*/
			else if (Stock->Identities[Stock->User][0] == 
			Stock->Channels_Users[Stock->Channels[i][0]][0])
			{
				if (send(poll_fd,
				"You are already connected\n\r", 27, 0)
				== -1)
					perror("send");
			}
			
			if (Stock->Channels[i][2].compare("\0") != 0)
// 			Channels[i][1] == key
// 			Channels[i][2] == topic 
			{
				if (send(poll_fd, const_cast<char*>(Stock->Channels[i][2].c_str()),
				Stock->Channels[i][2].size(), 0) == -1)
					perror("send");
			}
			else
			{
				if (send(poll_fd, "RPL No Topic\r\n", 14,
				0) == -1)
					perror("send");
			}
			o++;
			if (o == (int)tmp_Channel.size())
			{
				tmp_Channel.clear();
				tmp_Key.clear();
				Stock->line.clear();
				return (1239);
			}
		}
		else if ( i < Stock->Channel_Count &&
		tmp_Channel[o] == Stock->Channels[i][0] &&
		tmp_Key[o] != Stock->Channels[i][1])
		{
			if (send(poll_fd, "Bad param: Key is wrong\r\n",
			25, 0) == -1)
				perror("send");
			tmp_Channel.clear();
			tmp_Key.clear();
			Stock->line.clear();
			return (5874);	
		}
		else if ( i == Stock->Channel_Count &&
		o <= (int)tmp_Channel.size() )
		{
			Stock->Channels[i].push_back(tmp_Channel[o]);
			Stock->Channels[i].push_back("\0");
			Stock->Channels[i].push_back("\0");
			tmp = Stock->line[0];
			tmp += ' ';
			tmp += tmp_Channel[o];
			if (send(poll_fd, const_cast<char*>(tmp.c_str()), tmp.size(), 0) == -1)
				perror("send");
			tmp.clear();
			if (send(poll_fd, "RPL No Topic\r\n", 14, 0) == -1)
				perror("send");
			it =
			Stock->Channels_Users[Stock->Channels[i][0]].size()+ 1;
			for (int z = Stock->Identities[Stock->User].size();
			z > it; it++)
			{
				
				Stock->Channels_Users
				[Stock->Channels[i][0]].push_back
				(Stock->Identities[Stock->User][it]);
				if (send(poll_fd,
				"JOIN (known channel) complete\n\r", 31, 0)
				== -1)
					perror("send");
			}
			Stock->Channel_Count++;
			o++;
			i = -1;
		}
	}
// Continuer le traitement de JOIN - Ici, gérer cas création due a channel 
// non trouvé
	if ( Stock->Channel_Count == 0 )
	{
		for (int i = 0; i < (int)tmp_Channel.size() &&
		tmp_Channel[i].compare("\0") != 0; i++)
		{
			if (tmp_Key[i].compare("\0") != 0)
			{
				if (send(poll_fd, "Bad param: Key is wrong\r\n",
				25, 0) == -1)
					perror("send");
				tmp_Channel.clear();
				tmp_Key.clear();
				Stock->line.clear();
				return(5874);	
			}
			Stock->Channels[i].push_back(tmp_Channel[i]);
			Stock->Channels[i].push_back(tmp_Key[i]);
			Stock->Channels[i].push_back("\0");
			tmp = Stock->line[0];
			tmp += ' ';
			std::cout << tmp_Channel[i] << std::endl;
			tmp += tmp_Channel[i];
			if (send(poll_fd, const_cast<char*>(tmp.c_str()), tmp.size(), 0) == -1)
				perror("send");
			tmp.clear();
			if (send(poll_fd, "RPL No Topic\r\n", 14, 0) == -1)
				perror("send");
			Stock->Channels_Users
			[Stock->Channels[i][0]].push_back
			(Stock->Identities[Stock->User][0]);
			Stock->Channel_Count++;
		}
	}
	tmp_Channel.clear();
	tmp_Key.clear();
	Stock->line.clear();
	return (0);
}
