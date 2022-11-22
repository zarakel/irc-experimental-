#include "../headers/headers.hpp"
#include "../headers/Command.hpp"
#include "../headers/parse_message.hpp"

int	command_check(int poll_fd, Stock *Stock)
{
//	cette fonction nous permettra de séparer les instructions d'un message envoyé		par un client afin de repérer la commande et ces paramètres ainsi que de repérer 	les potentielles erreurs --- Suite de receive_message

// il faudra créer une fonction fill_cmd ou quelque chose du genre
//	int yo = 0;
//	std::cout << "before boucle " << yo++ << std::endl;
//	for (size_t i = 0; i <= Stock->all_commands.size(); i++)
//	{	
//		receive_message(poll_fd, Stock);
//		std::cout << "iinside " << yo++ << " && line = " << Stock->line.size() << std::endl;
//		if (Stock->line[1].size() > 0 && i < Stock->all_commands.size())
//		{		
//			std::cout << "before pass " << yo++ << std::endl;
//			for (size_t a = 0; a < Stock->line.size(); a++)
//				std::cout << Stock->line[a] << std::endl;
	/*		if (Stock->line[0] == "CAP" && Stock->line[1] == "LS")
			{
				//Stock->line.clear();
				if (send(poll_fd, "CAP * LS :\n", 11, 0) == -1)
					perror("send: ");
				Stock->line.clear();
		//		receive_message(poll_fd, Stock);
				for (size_t a = 0; a < Stock->line.size(); a++)
					std::cout << Stock->line[a] << std::endl;
			//	exit(0);
			}*/
		//	receive_message(poll_fd, Stock);
//		for (size_t a = 0; a < Stock->line.size(); a++)
//				std::cout << Stock->line[a] << std::endl;
			
	/*		for (size_t a = 0; a < Stock->line.size(); a++)
				std::cout << Stock->line[a] << std::endl;
			std::cout << "size is " << Stock->line.size() << std::endl;
			std::cout << "sizef is " << Stock->full_command["PING"].size() << std::endl;*/
			if (Stock->line[0] == Stock->all_commands[6])
//			&& Stock->line.size() == Stock->full_command["PING"].size())
			{
				PING(poll_fd, Stock);
			//	return (0);
			}

			if (Stock->line[0] == Stock->all_commands[0]
			&& Stock->line.size() == Stock->full_command["PASS"].size())
			{
//				std::cout << "inside pass " << std::endl;
				PASS(poll_fd, Stock);
				if (Stock->tmp_pass[Stock->User] == 1 && Stock->tmp_nick[Stock->User] == 1 && Stock->tmp_user[Stock->User] == 1 && Stock->authentified[Stock->User] == 0)
			{
				Stock->authentified[Stock->User] = 1;
// on doit ajouter un null a la fin de Identities pour le rendre viable
				Stock->Identities[Stock->User].push_back("\0");
				Stock->Flag.push_back("\0");
				std::string tmp = ":ft_irc 001 ";
				tmp += Stock->Identities[Stock->User][0];
				tmp += " :Welcome to the IRC !\n";
				for (size_t b = 0; b < tmp.size(); b++)
				{
					if (send(poll_fd, (&tmp[b]), 1, 0) == -1)
						perror("send: ");
				}
			/*	std::cout << "fd is " << Stock->client_fd[Stock->User]
				<< std::endl;*/
				tmp.clear();
			}
				return (1);
			}
	//		Stock->tmp_authentified[Stock->User] = 1;
//			std::cout << "lo " << yo++ << std::endl;
			if (Stock->line[0] == Stock->all_commands[1]
			&& Stock->line.size() == Stock->full_command["NICK"].size())
	//		&& (Stock->tmp_authentified[Stock->User] == 1
	//		| Stock->authentified[Stock->User] == 1))
			{
//				std::cout << "inside nick " << std::endl;
				NICK(poll_fd, Stock);
					if (Stock->tmp_pass[Stock->User] == 1 && Stock->tmp_nick[Stock->User] == 1 && Stock->tmp_user[Stock->User] == 1 && Stock->authentified[Stock->User] == 0)
			{
				Stock->authentified[Stock->User] = 1;
// on doit ajouter un null a la fin de Identities pour le rendre viable
				Stock->Identities[Stock->User].push_back("\0");
				Stock->Flag.push_back("\0");
				std::string tmp = ":ft_irc 001 ";
				tmp += Stock->Identities[Stock->User][0];
				tmp += " :Welcome to the IRC !\n";
				for (size_t b = 0; b < tmp.size(); b++)
				{
					if (send(poll_fd, (&tmp[b]), 1, 0) == -1)
						perror("send: ");
				}
				std::cout << "fd is " << Stock->client_fd[Stock->User]
				<< std::endl;
				tmp.clear();
			}
				return (1);
			}
			if (Stock->line[0] == Stock->all_commands[2]
			&& Stock->line.size() == Stock->full_command["USER"].size())
//			&& (Stock->tmp_authentified[Stock->User] == 2
//			| Stock->authentified[Stock->User] == 1))
			{
//				std::cout << "inside user" << std::endl;
				USER(poll_fd, Stock);
				if (Stock->tmp_pass[Stock->User] == 1 && Stock->tmp_nick[Stock->User] == 1 && Stock->tmp_user[Stock->User] == 1 && Stock->authentified[Stock->User] == 0)
			{
				Stock->authentified[Stock->User] = 1;
// on doit ajouter un null a la fin de Identities pour le rendre viable
				Stock->Identities[Stock->User].push_back("\0");
				Stock->Flag.push_back("\0");
				std::string tmp = ":ft_irc 001 ";
				tmp += Stock->Identities[Stock->User][0];
				tmp += " :Welcome to the IRC !\n";
				for (size_t b = 0; b < tmp.size(); b++)
				{
					if (send(poll_fd, (&tmp[b]), 1, 0) == -1)
						perror("send: ");
				}
				tmp.clear();
				std::cout << "fd is " << Stock->client_fd[Stock->User]
				<< std::endl;
			}
				return (1);
			}
// une fois pass, nick et user de fait, authentified = 1
//			std::cout << "li " << yo++ << std::endl;
//			if (Stock->tmp_authentified[Stock->User] == 2)
// tant que user marche pas	
			

//			std::cout << "la " << yo++ << std::endl;
			else if ((Stock->line[0] == Stock->all_commands[3]
			&& Stock->line.size() == Stock->full_command["JOIN"].size() - 1
			&& Stock->authentified[Stock->User] == 1) ||
			(Stock->line[0] == Stock->all_commands[3]
			&& Stock->line.size() == Stock->full_command["JOIN"].size()
			&& Stock->authentified[Stock->User] == 1))
			{
//				std::cout << "inside join " << yo++ << std::endl;
				JOIN(poll_fd, Stock);
				return (1);
			}

//			std::cout << "le " << yo++ << std::endl;
			else if ((Stock->line[0] == Stock->all_commands[4]
			&& Stock->line.size() == Stock->full_command["PRIVMSG"].size()
			&& Stock->authentified[Stock->User] == 1))
			{
//				std::cout << "inside privmsg " << yo++ << std::endl;
				PRIVMSG(poll_fd, Stock);
				return (1);
			}

//			std::cout << "ly " << yo++ << std::endl;
			else if ((Stock->line[0] == Stock->all_commands[5]
			&& Stock->line.size() == Stock->full_command["MODE"].size()
			&& Stock->authentified[Stock->User] == 1))
			{
		//		std::cout << "inside mode" << std::endl;
				MODE(poll_fd, Stock);
				return (1);
			}
//			std::cout << "lp " << yo++ << std::endl;
/*			if (Stock->authentified[Stock->User] == 0)
			{
//				std::cout << "inside 0 auth " << yo++ << std::endl;
				if (send(poll_fd, "Bad Usage: You're not authorized !\n\r", 37, 0) == -1)
					perror("send");
				for (size_t a = 0; a <= Stock->line.size(); a++)
					std::cout << Stock->line[a] << std::endl;
				Stock->line.clear();
				return (565);
			}
//			std::cout << "coucou bl" << std::endl;*/
/*			if (i == Stock->all_commands.size())
			{
				std::cout << "coucou last" << std::endl;
				if (send(poll_fd, "Bad Param': On refait bien la, oh !\n\r", 37, 0) == -1)
					perror("send");
				Stock->line.clear();
				return (598);
			}
		}
		else 
		{
			std::cout << "else end " << std::endl;
			if (send(poll_fd, "Bad Command: Faites un effort, voyons.\n\r", 40, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (598);
//		}
//		std::cout << "i = " << i++ << std::endl;
//	}
	std::cout << "fin boucle" << std::endl;
	std::cout << "ce fameux poll = " << poll_fd << std::endl; 
	if (send(poll_fd, "Bad Command: Faites un effort, voyons.\n\r", 40, 0) == -1)
	{
		std::cout << "la" << std::endl;
		perror("send");
//		std::cout << "fin" << yo++ << std::endl;
		Stock->line.clear();*/
		return (0);
}

int	receive_message(int poll_fd, Stock *Stock)
{
//	std::cout << "start receive message" << std::endl;
	char		buf[9999];

	if (recv(poll_fd, buf, 9999, 0) == -1)
	{
	//	perror("recv :");
		return (10);
	}
	for (int it = 0; ((buf[it] != '\n' | buf[it] != '\r') && it <= 512) ; it++)
	{
		if (buf[it] == ':' && (buf[it + 1] == ' ' | buf[it + 1] == '\n'
			| buf[it + 1] == '\r'))
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
		if (buf[it + 1] == ':' && buf[it + 2] != '\0')
		{
			it += 2 ;
			for (size_t end = it; buf[end] != '\n'; end++)
				Stock->word.push_back(buf[end]);
//			Stock->word += "\n\r";
			Stock->line.push_back(Stock->word);
			Stock->line.push_back("\0"); // NULL pour savoir quand fin vector
			Stock->word.clear();
			break;
		}	
		if (buf[it + 1] == '\n' | buf[it + 1] == '\r')
		{
//			Stock->word += "\n\r";
			Stock->line.push_back(Stock->word);
			Stock->line.push_back("\0"); // NULL pour savoir quand fin vector
			Stock->word.clear();
		//	memset(&tmp, 0, sizeof buf); NE SURTOUT PAS REINITIALISER LE BUF
//  LA SOCKET SE FERMERAIT 
			break;
		}
		else if (buf[it + 1] == '\0')
			it += 2;
		if (it > 512)
		{
			if (send(poll_fd, "Message too long: C'est plus que Levis quand même\n\r", 50, 0) == -1)
				perror("send");
			Stock->word.clear();
			Stock->line.clear();
			return (19);
		}	
	}
//	command_check(poll_fd, Stock);
	Stock->word.clear();
	for (size_t c = 0; c <= Stock->all_commands.size(); c++) 
	{
		if (Stock->line[0] == Stock->all_commands[c])
//	std::cout << Stock->line[c] << std::endl;
			return (0);
	}
	Stock->line.clear();
//	if (send(poll_fd, "Bad command: Try better\n\r", 25, 0) == -1)
//		perror("send: ");
	return(1);
}

