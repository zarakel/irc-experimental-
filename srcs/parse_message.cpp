#include "../headers/headers.hpp"
#include "../headers/Command.hpp"
#include "../headers/parse_message.hpp"

int	command_check(int poll_fd, Stock *Stock)
{
//	cette fonction nous permettra de séparer les instructions d'un message envoyé		par un client afin de repérer la commande et ces paramètres ainsi que de repérer 	les potentielles erreurs --- Suite de receive_message

	std::vector<std::string> cmd;
	//std::string tmp;

// il faudra créer une fonction fill_cmd ou quelque chose du genre

	cmd.push_back("PASS");
	if (Stock->line[0] == cmd[0])  
	{
		if (Stock->line[1].size() > 0 && Stock->line[2] == "\0")
		{
			PASS(poll_fd, Stock);
			return (0);
		}
		else
		{
			if (send(poll_fd, "Bad Param': On refait bien la, oh !\n\r", 37, 0) == -1)
				perror("send");
			Stock->line.clear();
			return (598);
		}				
	}
	if (send(poll_fd, "Bad Command: Faites un effort, voyons.\n\r", 40, 0) == -1)
		perror("send");
	Stock->line.clear();
	return (458);	
}

int	receive_message(int poll_fd, Stock *Stock)
{
	char		buf[9999];	

	if (recv(poll_fd, buf, 9999, 0) == -1)
		perror("send :");
	for (int it = 0; buf[it] != '\n'; it++)
	{
		Stock->word.push_back(buf[it]);
		if (buf[it + 1] == ' ')
		{
	//		word.push_back('\0'); Inutile de conclure par NULL
			Stock->line.push_back(Stock->word);
			Stock->word.clear();
			if (buf[it + 2] == '\n')
				break;
			it++;
		}
		if (buf[it + 1] == '\n')
		{
			Stock->line.push_back(Stock->word);
			Stock->line.push_back("\0"); // NULL pour savoir quand fin vector
			Stock->word.clear();
		//	memset(&tmp, 0, sizeof buf); NE SURTOUT PAS REINITIALISER LE BUF
//  LA SOCKET SE FERMERAIT 
			break;
		}
		else if (buf[it + 1] == '\0')
		{
		/*	std::cerr << " : No Chariot Return detected" << std::endl;
			Stock->line.clear();
			return (456); //chercher le bon numéric*/
			it += 2;
		}
	}
	command_check(poll_fd, Stock);
	return (-1);
}
