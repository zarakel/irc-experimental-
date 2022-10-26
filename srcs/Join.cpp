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
			if (send(poll_fd, "Bad Param: chan name contain wrong characters\r\n", 31, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (882);
		}
		if ( Stock->line[1][i] != 0 )
			tmp.push_back(Stock->line[1][i]);
		if ( Stock->line[1].compare(tmp) == 0 )
			tmp_Channel.push_back(tmp);
		if (Stock->line[1][i + 1] == ',' &&
		(Stock->line[1][i + 2] == '#' && Stock->line[1][i + 2] == '&'
		&& Stock->line[1][i + 2] == '+' && Stock->line[1][i + 2] == '!'))
		{
			i++;
			it++;
		}
		else if (Stock->line[1][i + 1] == ',' &&
	(Stock->line[1][i + 2] != '#' | Stock->line[1][i + 2] != '&'
	| Stock->line[1][i + 2] != '+'| Stock->line[1][i + 2] != '!'))
		{
			if (send(poll_fd, "Bad Param: chan name contain wrong characters\r\n", 31, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (882);
		}
	}
	tmp.clear();
	for (int i = 0; i <= it; i++)
		tmp_Key.push_back("\0");
	it = 0;
// vérif des keys
	for ( int i = 0; Stock->line[2].empty() == 0 && 
	Stock->line[2][i] != '\n' | Stock->line[2][i] != '\r'; i++)
	{
		if ( i == 0 )
			tmp_Key[it].clear();
		if (Stock->line[2][i] == ' ' | Stock->line[2][i] == 7)
		{
			if (send(poll_fd, "Bad Param: key contain wrong characters\r\n", 31, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (883);
		}
		if ( Stock->line[2][i + 1] != 0 )
			tmp.push_back(Stock->line[1][i]);
		if ( Stock->line[2][i + 1] == 0 && tmp.empty() != 0 )
			tmp_Key[it].push_back(Stock->line[1][i]);
//		tmp_Key[it] = Stock->line[2][i];
		if (Stock->line[2][i + 1] == ',')
		{
			i++;
			it++;
		}
	}
// vérif si channel existe déja
	for ( int i = 0; Stock->Channel_Count > 0 && i < Stock->Channel_Count
		&& Stock->Channels[i][0].empty() == 0; i++)
	{
		// si on repere un channel déja existant	
		std::cout << "Tour = " << i << std::endl;
		if ( tmp_Channel[o] == Stock->Channels[i][0] && tmp_Key[o]
		== Stock->Channels[i][1])
// l'idée, c'est que si key n'existe pas, on mets '\0'
		{
			for( int a = 0; 
			Stock->Identities[Stock->User][a].empty() == 0; a++)
			{
				if (Stock->Identities[Stock->User][0] == 
				Stock->Channels_Users[Stock->Channels[i][0]][0])
					break;
				Stock->Channels_Users[Stock->Channels[i][0]].
				push_back(Stock->Identities[Stock->User][a]);
			}
// la boucle for enregistre l'identité de l'ip, du nickname, du username de 	l'user actuel
			/*tmp = Stock->line[0];
			tmp += ' ';
			tmp += tmp_Channel[o];
			if (send(poll_fd, static_cast<void *>(&tmp), tmp.length(), 0) == -1)
				perror("send");
			tmp.clear();*/
			if (send(poll_fd, "(known channel)JOIN complete\n\r",
			30, 0) == -1)
				perror("send");
			if (Stock->Channels[i][2].empty() == 0)
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
	//		tmp_Channel_Check[o] = 1;
		}
		else if ( tmp_Channel[o] == Stock->Channels[i][0] && tmp_Key[o]
		!= Stock->Channels[i][1])
		{
			if (send(poll_fd, "Bad param: Key is wrong\r\n",
			25, 0) == -1)
				perror("send");
			return(5874);	
		}
		if ( Stock->Channels[i + 1][0].empty() != 0 )
		{
			int yo = 0;
			std::cout << "yo = " << yo << std::endl;
			Stock->Channels[i].push_back(tmp_Channel[o]);
/*			tmp = Stock->line[0];
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
			i = 0;
			for( int a = 0; 
			Stock->Identities[Stock->User][a].empty() == 0; 				a++)
			{
				std::cout << "blague" << std::endl;
				Stock->Channels_Users
				[Stock->Channels[i][0]].push_back
				(Stock->Identities[Stock->User][a]);
			}
			std::cout << "fin" << std::endl;
			Stock->Channel_Count++;
			o++;
		}
		if ( tmp_Channel[o].empty() != 0 )
		{
			std::cout << "fin de la fin" << std::endl;
			tmp.clear();
			break;
		}
	}
// Continuer le traitement de JOIN - Ici, gérer cas création due a channel 
// non trouvé
	if ( Stock->Channel_Count == 0 )
	{
		for (int i = 0; tmp_Channel[i].empty() == 0; i++)
		{
			if (tmp_Key[i].compare("\0") != 0)
			{
				if (send(poll_fd, "Bad param: Key is wrong\r\n",
				25, 0) == -1)
					perror("send");
				return(5874);	
			}
			Stock->Channels[i].push_back(tmp_Channel[i]);
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
			tmp.clear();
			if (send(poll_fd, "RPL No Topic\r\n", 14, 0) == -1)
				perror("send");
			for( int a = 0; 
			Stock->Identities[Stock->User][a].empty() == 0; 				a++)
			{
				Stock->Channels_Users
				[Stock->Channels[i][0]].push_back
				(Stock->Identities[Stock->User][a]);
			}
			Stock->Channel_Count++;
		}
	}
	tmp_Channel.clear();
	tmp_Key.clear();
	Stock->line.clear();
	return (0);
}
