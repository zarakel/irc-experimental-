#include "../headers/headers.hpp"

int	command_check(int poll_fd, std::vector<std::string> line, std::string pass)
{
//	cette fonction nous permettra de séparer les instructions d'un message envoyé		par un client afin de repérer la commande et ces paramètres ainsi que de repérer 	les potentielles erreurs --- Suite de receive_message

	std::vector<std::string> cmd;
	//std::string tmp;

// il faudra créer une fonction fill_cmd ou quelque chose du genre

	cmd.push_back("PASS");
	if (line[0] == cmd[0])  
	{
		if (line[1].size() > 0 && line[2] == "\0")
		{
			PASS(poll_fd, pass, line[1]);
			return (0);
		}
		else
		{
			if (send(poll_fd, "On refait bien la, oh !\n\r", 25, 0) == -1)
				perror("send");
				return (598);
		}				
	}
	if (send(poll_fd, "Faites un effort, voyons.\n\r", 27, 0) == -1)
		perror("send");
	return (458);	
}

int	receive_message(int poll_fd, std::string pass)
{
	int		i = 0;
	int		it = 0;
	char		*tmp;
	std::string	word;
	std::vector<std::string> line;
	char		buf[9999];	

	if (recv(poll_fd, buf, 9999, MSG_WAITALL) == - 1)
		perror("recv");
	for (int it = 0; buf[it] != '\n'; it++)
	{
		word.push_back(buf[it]);
		if (buf[it + 1] == ' ')
		{
	//		word.push_back('\0'); Inutile de conclure par NULL
			line.push_back(word);
			word.clear();
			if (buf[it + 2] == '\n')
				break;
			it++;
		}
		if (buf[it + 1] == '\n')
		{
			line.push_back(word);
			line.push_back("\0"); // NULL pour savoir quand fin vector
			word.clear();
		//	memset(&tmp, 0, sizeof buf); NE SURTOUT PAS REINITIALISER LE BUF
//  LA SOCKET SE FERMERAIT 
			break;
		}
		else if (buf[it + 1] == '\0')
		{
			std::cerr << " : No Chariot Return detected" << std::endl;
			return (456); //chercher le bon numéric
		}
	}
	command_check(poll_fd, line, pass);
	return (-1);
}
