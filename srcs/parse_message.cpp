#include "../headers/headers.hpp"
#include "../headers/Command.hpp"
#include "../headers/parse_message.hpp"

int	command_check(int poll_fd, Stock *Stock)
{
//	cette fonction nous permettra de séparer les instructions d'un message envoyé		par un client afin de repérer la commande et ces paramètres ainsi que de repérer 	les potentielles erreurs --- Suite de receive_message

// il faudra créer une fonction fill_cmd ou quelque chose du genre
	int i = 0;
	int yo = 0;
	std::cout << "before boucle " << yo++ << std::endl;
	while (!Stock->all_commands[i].empty())
	{	
		std::cout << "iinside " << yo++ << " && line = " << Stock->line.size() << std::endl;
		if (Stock->line[0] == Stock->all_commands[i])  
		{
			if (Stock->line[1].size() > 0)
			{		
				std::cout << "before pass " << yo++ << std::endl;
				if (Stock->line[0] == Stock->all_commands[0]
				&& Stock->line.size() == Stock->full_command["PASS"].size())
				{
					std::cout << "inside pass " << yo++ << std::endl;
					PASS(poll_fd, Stock);
					return (0);
				}
				if (Stock->line[0] == Stock->all_commands[1]
				&& Stock->line.size() == Stock->full_command["NICK"].size()
				&& (Stock->tmp_authentified[Stock->User] == 1
				| Stock->authentified[Stock->User] == 1))
				{
					std::cout << "inside nick " << yo++ << std::endl;
					NICK(poll_fd, Stock);
					return (0);
				}
/* condition supposé de user if (Stock->line[0] == Stock->all_commands[1]
				&& Stock->line[2].empty() != 0
				&& (Stock->tmp_authentified[Stock->User] == 2
				| Stock->authentified == 1))*/

// une fois pass, nick et user de fait, authentified = 1
		//		if (Stock->tmp_authentified[Stock->User] = 3
				if (Stock->tmp_authentified[Stock->User] == 2)
				{
					Stock->authentified[Stock->User] = 1;
// on doit ajouter un null a la fin de Identities pour le rendre viable
					Stock->Identities[Stock->User].push_back("\0");
				}

				if ((Stock->line[0] == Stock->all_commands[3]
				&& Stock->line.size() == Stock->full_command["JOIN"].size() - 1
				&& Stock->authentified[Stock->User] == 1) |
				(Stock->line[0] == Stock->all_commands[3]
				&& Stock->line.size() == Stock->full_command["JOIN"].size()
				&& Stock->authentified[Stock->User] == 1))
				{
					JOIN(poll_fd, Stock);
					return (0);
				}

				if (Stock->authentified[Stock->User] == 0)
				{
					if (send(poll_fd, "Bad Usage: You're not authorized !\n\r", 37, 0) == -1)
						perror("send");
					Stock->line.clear();
					return (565);
				}
			}
			else
			{
				if (send(poll_fd, "Bad Param': On refait bien la, oh !\n\r", 37, 0) == -1)
					perror("send");
				Stock->line.clear();
				return (598);
			}
		}
		i++;
	}
	/*std::cout << "fin boucle" << std::endl;
	std::cout << "ce fameux poll = " << poll_fd << std::endl; 
	if (send(poll_fd, "Bad Command: Faites un effort, voyons.\n\r", 40, 0) == -1)
	{
		std::cout << "la" << std::endl;
		perror("send");*/
		Stock->line.clear();
		return (458);	
}

int	receive_message(int poll_fd, Stock *Stock)
{
	std::cout << "start receive message" << std::endl;
	char		buf[9999];	

	if (recv(poll_fd, buf, 9999, 0) == -1)
	{
		perror("recv :");
		return (10);
	}
	for (int it = 0; ((buf[it] != '\n' | buf[it] != '\r') && it <= 512) ; 			it++)
	{
		if (buf[it] == ':' && (buf[it + 1] != ' ' | buf[it + 1] != '\n'
			| buf[it + 1] != '\r'))
		{
			if (send(poll_fd, "Bad Message: Deux points, c'est zéro.\n\r", 39, 0) == -1)
				perror("send");
			Stock->word.clear();
			Stock->line.clear();
			return (12);
		}	
		Stock->word.push_back(buf[it]);
		if (buf[it + 1] == ' ')
		{
			while (buf[it + 1] == ' ')
				it++;
	//		word.push_back('\0'); Inutile de conclure par NULL
			Stock->line.push_back(Stock->word);
			Stock->word.clear();
			if (buf[it + 2] == '\n' | buf[it + 2] == '\r')
				break;
		}
		if (buf[it + 1] == ':')
		{
			if (send(poll_fd, "Bad Message: Deux points, c'est zéro.\n\r", 39, 0) == -1)
				perror("send");
			Stock->word.clear();
			Stock->line.clear();
			return (11);
		}	
		if (buf[it + 1] == '\n' | buf[it + 1] == '\r')
		{
			Stock->line.push_back(Stock->word);
			Stock->line.push_back("\0"); // NULL pour savoir quand fin vector
			Stock->word.clear();
		//	memset(&tmp, 0, sizeof buf); NE SURTOUT PAS REINITIALISER LE BUF
//  LA SOCKET SE FERMERAIT 
			break;
		}
		else if (buf[it + 1] == '\0')
			it += 2;
/*		if (it > 512)
		{
			if (send(poll_fd, "Message too long: C'est plus que Levis quand même\n\r", 50, 0) == -1)
				perror("send");
			Stock->word.clear();
			Stock->line.clear();
			return (19);
		}	*/
	}
	command_check(poll_fd, Stock);
	return (0);
}
