/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:32:46 by juan              #+#    #+#             */
/*   Updated: 2022/11/10 16:54:12 by operculesangu    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/headers.hpp" 
#include "../headers/parse_message.hpp"
#include "../headers/Server.hpp"
#include <stdlib.h> 

#define BACKLOG 10   // how many pending connections queue will hold

void sigchld_handler( int s )
{
	// waitpid() might overwrite errno, so we save and restore it:
	int saved_errno = errno;

	std::cout << s << std::endl;
	while(waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	return &(((struct sockaddr_in*)sa)->sin_addr);

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void Check_FD(Stock *Stock, struct pollfd *popoll)
{
// a arranger !
/*	std::cout << "yo" << std::endl;
	if (Stock->Nicks.empty() == 0 && Stock->Identities
	[Stock->User].empty() == 0)
	{
		std::cout << "ipayo" << std::endl;
		for (int i = 0; i < Stock->User; i++)
		{
			if (Stock->client_fd[i] == new_fd)
			{
				Stock->User = i;
				break;
			}
			else if (Stock->client_fd[i + 1] == 0)
			{*/
				for (int a = 0; (((popoll + a)->events & POLLIN) != POLLIN); a++)
				{
					if (((popoll + a)->events & POLLIN) == POLLIN)
					{
						Stock->User = a;
						std::cout << "t qui toi la (fd in check) = " <<
						(popoll + a)->fd << std::endl;
					}
				}
	//		}
/*		}
	}*/
}
				

int server(Stock *Stock)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	struct pollfd *popoll;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
char s[INET6_ADDRSTRLEN];
int rv;

std::cout << "Le pass est censé être : " << Stock->pass << std::endl;
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE; // use my IP

if ((rv = getaddrinfo(NULL, Stock->port, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol)) == -1) 
		{
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
		sizeof(int)) == -1) 
		{
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sockfd);
			perror("server: bind");
			continue;
		}

        	break;
    }

	freeaddrinfo(servinfo); // all done with this structure

	if (p == NULL)
	{
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}

	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	if ((popoll = (struct pollfd *)malloc(10 * sizeof(popoll))) == NULL)
		perror("malloc");
	popoll->fd = sockfd;
	popoll->events = POLLIN;
	popoll->revents = 0;	
	Stock->User_Count++;
	printf("server: waiting for connections...\n");
	int nfds = 0;
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
//	int otherfd = 0;
	while(1)
	{  // main accept() loop
		nfds = Stock->User_Count;
		if (poll(popoll, nfds, 0) == -1)
			perror("poll"); 
		for (int i = 0; i < (nfds + 1); i++)
		{
			std::cout << "start for" << std::endl;
			std::cout << "never" << std::endl;
			sin_size = sizeof their_addr;
			int new_fd;
			if ((new_fd = accept((popoll + i)->fd,
			(struct sockaddr *)&their_addr,
			&sin_size)) == -1 )
				perror("accept");
			std::cout << "new_fd 0= " << new_fd << std::endl;
			inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
			printf("server: got connection from %s\n", s);
			std::cout <<
			"(Bienvenue sur le serveur, veuillez taper votre pass.)" << std::endl;
			if (new_fd != -1)
			{
					for (int a = 0; a < Stock->User_Count; a++)
					{
						if (new_fd == (popoll + a)->fd)
							break;
					}
					Stock->User_Count++;
					(popoll + Stock->User_Count - 1)->fd = new_fd;
					(popoll + Stock->User_Count - 1)->events = POLLIN;
					(popoll + Stock->User_Count - 1)->revents = 0;
					Stock->client_fd[Stock->User_Count - 2]  = new_fd;
					Stock->User = Stock->User_Count - 2;
				std::cout << "new_fd attribution= " << new_fd << std::endl;
			}
			else
			{
				// j'imagine plusieurs choses pour gérer le cas ou un ctr + c est fait d'un terminal :
				// Avec signal, transformer les ctrl+c en kill ou close du fd utilisé
				// Utiliser un Ping/Pong like pour determiner que le fd ne fonctionne plus correctement (?)
				// le probleme actuel est que le serveur passe par le else direct et ainsi crée des erreurs potentielles
				// cas étrange, si on recoit d'autre connection, elles ne sont pas reconnues
				for (int a = 0; a < Stock->User_Count; a++)
				{
					if (((popoll + a)->revents & POLLIN) == POLLIN)
					{
						Stock->User = a - 1;
						break;
					}
				}
			}
			std::cout << "stockfd(b) 2 = " << Stock->client_fd[Stock->User] << std::endl;
			if (Stock->User_Count > 1)
			{
				receive_message(Stock->client_fd[Stock->User], Stock);
				break;
			}
		}
	}
	return 0;
}

