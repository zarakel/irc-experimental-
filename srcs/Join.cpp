#include "../headers/headers.cpp"
#include "../headers/Join.hpp"

void	Join(int poll_fd, Stock * Stock)
{
	std::vector<std::string > tmp_Channel;
	std::vector<std::string > tmp_Channel_Verified;
	std::vector<std::string > tmp_Key;
	std::string tmp;
	int	it = 0;
	int	o = 0;
	int	tmp_Channel_Check[10];

	if (Stock->line[1][0] != '#' | Stock->line[1][0] != '&' |
		Stock->line[1][0] != '+' | Stock->line[1][0] != '!')
	{
		if (send(poll_fd, "Bad Param: # or & are not there\r\n", 33, 0)
			== -1)
			perror("send");
		Stock->line.clear();
		return (83);
	}
	if (Stock->line.size() > 50)
	{
		if (send(poll_fd, "Bad Param: chan name too long\r\n", 31, 0)
			== -1)
			perror("send");
		Stock->line.clear();
		return (862);
	}
	for ( int i = 0; Stock->line[1][i] != '\n' | Stock->line[1][i] != '\r';
		i++)
	{
		if (Stock->Identities[Stock->User][0] ==
		Stock->Channels_Users[Stock->Channels[i][0]][0])
			break;
		if (Stock->line[1][i] == ' ' | Stock->line[1][i] == 7)
		{
			if (send(poll_fd, "Bad Param: chan name contain wrong 
			characters\r\n", 31, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (882);
		}
		tmp_Channel[it].push_back(Stock->line[1][i]);
		if (Stock->line[1][i + 1] == ',' &&
		(Stock->line[1][i + 2] == '#' | Stock->line[1][i + 2] == '&'
		| Stock->line[1][i + 2] == '+' | Stock->line[1][i + 2] == '!'))
			it++;
		else if (Stock->line[1][i + 1] == ',' &&
	(Stock->line[1][i + 2] != '#' | Stock->line[1][i + 2] != '&'
	| Stock->line[1][i + 2] != '+'| Stock->line[1][i + 2] != '!'))
		{
			if (send(poll_fd, "Bad Param: chan name contain wrong 
			characters\r\n", 31, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (882);
		}
	}
	for ( int i = 0; i < this->Channel_Count
		&& Stock->Channels[i][0].empty() == 0; i++)
	{
		// si on repere un channel déja existant	
		if ( tmp_Channel[o] == Stock.Channels[i][0] && tmp_Key[o]
		== Stock.Channels[i][1])
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
			tmp == Stock->line[0];
			tmp += ' ';
			tmp += tmp_Channel[o];
			if (send(poll_fd, tmp, tmp.length(), 
			0) == -1)
				perror("send");
			tmp.clear();
			if (Stock->Channels[i][2].empty() == 0)
// 			Channels[i][1] == key
// 			Channels[i][2] == topic 
			{
				if (send(poll_fd, Stock->Channels[i][2],
				Stock->Channels[i][2].length(), 0) == -1)
					perror("send");
			}
			else
			{
				if (send(poll_fd, "RPL No Topic\r\n", 14,
				0) == -1)
					perror("send");
			}
			tmp_Channel_Check[o] = 1;
		}
		else if ( tmp_Channel[o] == Stock.Channels[i][0] && tmp_Key[o]
		!= Stock.Channels[i][1])
		{
			if (send(poll_fd, "Bad param: Key is wrong\r\n",
			25, 0) == -1)
				perror("send");
			return(5874);	
		}
		if ( Stock->Channels[i][0].empty() != 0 )
		{
			Stock->Channels[i + 1].push_back(tmp_Channel[o]);
			tmp == Stock->line[0];
			tmp += ' ';
			tmp += tmp_Channel[o];
			if (send(poll_fd, tmp, tmp.length(), 0) == -1)
				perror("send");
			tmp.clear();
			if (send(poll_fd, "RPL No Topic\r\n", 14, 0) == -1)
				perror("send");
			i = 0;
			o++;
		}
		if ( tmp_Channel[o].empty() != 0 )
		{
			tmp.clear();
			tmp_Key.clear();
			Stock->line.clear();
			break;
		}
	}
// Continuer le traitement de JOIN - Ici, gérer cas création due a channel 
// non trouvé
	if ( Stock->Channel_Count == 0 )
	{
		for (int i = 0; tmp_Channel[i].empty() == 0; i++)
		{
			Stock->Channels[i].push_back(tmp_Channel[i]);
			tmp == Stock->line[0];
			tmp += ' ';
			tmp += tmp_Channel[i];
			if (send(poll_fd, tmp, tmp.length(), 0) == -1)
				perror("send");
			tmp.clear();
			if (send(poll_fd, "RPL No Topic\r\n", 14, 0) == -1)
				perror("send");
			if (tmp_Channel[i].empty() == 0)
			{
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
	}
// Créer cas ou Channel_Count n'est pas vide mais qu'on ne repere rien a l'interieur en comparant avec le channel entré
}
