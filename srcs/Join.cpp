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
		(Stock->line[1][i + 2] == '#' || Stock->line[1][i + 2] == '&'
		|| Stock->line[1][i + 2] == '+' || Stock->line[1][i + 2] == '!'))
		{
			i++;
			it++;
		}
		else if (Stock->line[1][i + 1] == ',' &&
	(Stock->line[1][i + 2] != '#' || Stock->line[1][i + 2] != '&'
	|| Stock->line[1][i + 2] != '+' || Stock->line[1][i + 2] != '!'))
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
		if (Stock->line[2][i] == ' ' || Stock->line[2][i] == 7)
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
	for ( int i = 0; Stock->Channel_Count > 0 && i < (Stock->Channel_Count + 1)
	&& tmp_Channel[o].compare("\0") != 0; i++)
	{
		// si on repere un channel déja existant
		// check_debug	
		int yo = 0;
		std::cout << "yo = " << yo++ << std::endl;
		std::cout << "Tour = " << i << std::endl;
		std::cout << "Cannel_Count = " << Stock->Channel_Count << std::endl;
		std::cout << "Chan = " << (int)tmp_Channel.size() << std::endl;
		std::cout << "o = " <<  o << std::endl;
		if (i < Stock->Channel_Count)
		{
			std::cout << "chan = " << tmp_Channel[o] << " && " <<
			Stock->Channels[i][0] << std::endl;
			std::cout << "mdp = " << tmp_Key[o] << " && " <<
			Stock->Channels[i][1] << std::endl;
		}
		// fin check debug
		if ( i < Stock->Channel_Count && 
		tmp_Channel[o] == Stock->Channels[i][0] &&
		tmp_Key[o] == Stock->Channels[i][1])
// l'idée, c'est que si key n'existe pas, on mets '\0'
		{
			std::cout << "yo = " << yo++ << std::endl;
			std::cout << "Stock->User = " << Stock->User << std::endl;
// On part du postulat qu'on a toujours le meme nombre d'info et que l'ordre desdonnées utilisateurs (ip, nick, user) n'a pas d'importance
			if (Stock->Channels_Users
			[Stock->Channels[i][0]][Stock->User] != 
			Stock->Identities[Stock->User][0])
			{
				if (send(poll_fd,
				"JOIN (existing channel) complete\n\r", 34, 0)
				== -1)
					perror("send");
				Stock->Channels_Users
				[Stock->Channels[i][0]].push_back
				(Stock->Identities[Stock->User][0]);
				std::cout << "Le dernier utilisateur est : " <<
				Stock->Channels_Users[Stock->Channels[i][0]][Stock->User] <<
				std::endl;
			}
		/*		it = -----------           BADLY DESIGNED
				Stock->Channels_Users
				[Stock->Channels[i][0]].size();
				std::cout << "theree" << std::endl;
				for (int z =
				Stock->Identities[Stock->User].size(); 
				z > it; it++)
				{
					Stock->Channels_Users
					[Stock->Channels[i][0]].push_back
					(Stock->Identities[Stock->User][it]);
				}*/
// le if enregistre l'ip de l'user actuel si il ne l'a pas déja
// probleme : Je n'enregistre pas le nick et le user 

			/*tmp = Stock->line[0];
			tmp += ' ';
			tmp += tmp_Channel[o];
			if (send(poll_fd, static_cast<void *>(&tmp), tmp.length(), 0) == -1)
				perror("send");
			tmp.clear();*/
			else if (Stock->Identities[Stock->User][0] == 
			Stock->Channels_Users[Stock->Channels[i][0]][Stock->User])
			{
				std::cout << "yo = " << yo++ << std::endl;
				if (send(poll_fd,
				"You are already connected\n\r", 27, 0)
				== -1)
					perror("send");
			}

			if (Stock->Channels[i][2].compare("\0") != 0)
// 			Channels[i][1] == key
// 			Channels[i][2] == topic 
			{
			//	if (send(poll_fd, static_cast<void *>(&Stock->Channels[i][2]), Stock->Channels[i][2].length() - 1, 0) == -1)
				if (send(poll_fd, "Topic opif\n\r", 12, 0)
				== -1)
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
	//		tmp_Channel_Check[o] = 1;
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
		o < (int)tmp_Channel.size() )
		{
			for (int check = 0; check <= Stock->Channel_Count; check++)
			{
				std::cout << "coucou" << std::endl;
				std::cout << "channel is " << tmp_Channel[o] << std::endl;
				std::cout << "Stock->Channel = " << Stock->Channels[check][0] << std::endl;
				if (tmp_Channel[o] == Stock->Channels[check][0])
				{
					i = -1;
					break;
				}
				else if (check + 1 == Stock->Channel_Count)
				{
					Stock->Channels[i].push_back(tmp_Channel[o]);
					Stock->Channels[i].push_back("\0");
					Stock->Channels[i].push_back("\0");
	/*				tmp = Stock->line[0];
					tmp += ' ';
					tmp += tmp_Channel[o];
					if (send(poll_fd, static_cast<void *>(&tmp),
					tmp.length(), 0) == -1)
						perror("send");
					tmp.clear();*/
					if (send(poll_fd, "(new)JOIN complete\n\r", 20, 0) == -1)
						perror("send");
					if (send(poll_fd, "RPL No Topic\r\n", 14, 0) == -1)
						perror("send");
		//     mis a jour des données utilisateurs
					Stock->Channels_Users
					[Stock->Channels[i][0]].push_back
					(Stock->Identities[Stock->User][0]);
					Stock->Channel_Count++;
					if (o + 1 < (int)tmp_Channel.size() )
					{
						o++;
						i = -1;
						break;
					}
					else 
						tmp_Channel.clear();
						tmp_Key.clear();
						Stock->line.clear();
						return (123456);
				}
			}
	/*		int turn = 0; --------  Commenté parce que je ne sais pas ou je vais avec ca, dans le cas ou on doit utiliser tout les id d'un user
			it =
			Stock->Channels_Users[Stock->Channels[i][0]].size();
			for (int z = Stock->Identities[Stock->User].size();
			z > it; it++)
			{
				if (turn == 0)
				{
					Stock->Channels_Users
					[Stock->Channels[i][0]].push_back
					(Stock->Identities[Stock->User][it]);
					if (send(poll_fd,
					"JOIN (known channel) complete\n\r", 31, 0)
					== -1)
						perror("send");
			}*/
		/*	if (Stock->Identities[Stock->User][0].empty() == 0)
			{
				std::cout << "blague" << std::endl;
				Stock->Channels_Users
				[Stock->Channels[i][0]].push_back
				(Stock->Identities[Stock->User][0]);
			}*/
			std::cout << "fin" << std::endl;
		}
	/*	if ( o == (int)tmp_Channel.size() )
		{
			std::cout << "fin de la fin" << std::endl;
			tmp.clear();
			break;
		}*/
		std::cout << "fin de boucle" << std::endl;
	}
// Continuer le traitement de JOIN - Ici, gérer cas création due a channel 
// non trouvé
	int tour = 0;
	int yo = 0;
	std::cout << "post boucle check channel" << std::endl;
	std::cout << "tmp_Channel = " << (int)tmp_Channel.size() << std::endl;
	if ( Stock->Channel_Count == 0 )
	{
		std::cout << "boucle new channel" << std::endl;
		for (int i = 0; i < (int)tmp_Channel.size() &&
		tmp_Channel[i].compare("\0") != 0; i++)
		{
			std::cout << "Tour " << tour++ << std::endl;
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
/*			tmp = Stock->line[0]; doit servir a send une phrase							composé
			tmp += ' ';
			std::cout << tmp_Channel[i] << std::endl;
			tmp += tmp_Channel[i];*/
/*			if (send(poll_fd, static_cast<void *>(&tmp),
			tmp.length() + 1, 0) == -1)
				perror("send");*/
			if (send(poll_fd, "JOIN complete\r\n", 15, 0) == -1)
				perror("send");
//			tmp.clear();
			if (send(poll_fd, "RPL No Topic\r\n", 14, 0) == -1)
				perror("send");
			std::cout << "yo = " << yo++ << std::endl;
			Stock->Channels_Users
			[Stock->Channels[i][0]].push_back
			(Stock->Identities[Stock->User][0]);
			Stock->Channel_Count++;
		}
	}
	std::cout << "Clean Step" << std::endl;
	std::cout << "Stock->Channel_Count =" << Stock->Channel_Count << std::endl;
	tmp_Channel.clear();
	tmp_Key.clear();
	Stock->line.clear();
	return (0);
}
