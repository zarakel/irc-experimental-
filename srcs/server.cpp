/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:32:46 by juan              #+#    #+#             */
/*   Updated: 2022/11/28 18:08:05 by juan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/headers.hpp" 
#include "../headers/parse_message.hpp"
#include "../headers/Server.hpp"
#include "../headers/User.hpp"
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

int Check_FD(Stock *Stock)
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
	for (int i = 0; i < Stock->User_Count; i++)
	{
//		if (((popoll + i)->revents & POLLIN) == POLLIN)
//		{
	//		Stock->User = i;
	//			std::cout << "User is " << i << std::endl;
			if (recv(Stock->client_fd[i], NULL,1, MSG_PEEK | MSG_DONTWAIT) == 0)
			{	
				for (int a = 0; Stock->Channel_Count > 0 && a < Stock->Channel_Count; a++)
					Stock->Channels_Users[Stock->Channels[a][0]][i].clear();
				if (Stock->Identities.size() > 0)
				{
					Stock->Identities[i].clear();
					Stock->Identities[i].resize(0);
				}
				if (Stock->Users.size() > 0)
				{
					Stock->Users[i].clear();
					Stock->Users[i].resize(0);
				}
//				if (Stock->Nicks.size() > 0)
//					Stock->Nicks[i] = "\0";
				Stock->tmp_pass[i] = 0;
				Stock->tmp_nick[i] = 0;
				Stock->tmp_user[i] = 0;
				Stock->authentified[i] = 0;
//				std::cout << "héhé boy " << i << std::endl;
				close(Stock->client_fd[i]);
		//		Stock->client_fd[i] = 0;
			//		free(popoll + i);
				//	Stock->User_Count--;
			}
		}
	//		}
//		}
//	}
	return (1);
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
	Stock->sockfd = sockfd;
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
			continue;
		//	perror("poll :"); 
		for (int i = 0; i < (nfds + 1); i++)
		{
	//		std::cout << "i en cours " << i << std::endl;
			sin_size = sizeof their_addr;
			int new_fd;
		/*	if ((new_fd = accept((popoll + i)->fd,
			(struct sockaddr *)&their_addr,
			&sin_size)) == -1 )
				perror("accept :"); 
				continue;*/
			Check_FD(Stock);
			new_fd = accept((popoll + i)->fd,
			(struct sockaddr *)&their_addr,
			&sin_size);
			inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
		//	printf("server: got connection from %s\n", s);
			if (new_fd != -1)
			{
				Check_FD(Stock);
				for (int a = 0; a < Stock->User_Count; a++)
				{
					if (new_fd == (popoll + a)->fd)
					{
			//			std::cout << "discover fd is " << new_fd << std::endl;
			//			std::cout << "a is " << a << std::endl;
				(popoll + a)->fd = new_fd;
				(popoll + a)->events = POLLIN;
				(popoll + a)->revents = 0;
/*				for (int b = 0; Stock->client_fd[b] != new_fd; b++)*/
					Stock->client_fd[a - 1] = new_fd;
				Stock->User = a - 1;
						break;
					}
					if (a + 1 == Stock->User_Count)
					{
			//			std::cout << "attribute" << std::endl;
			//	std::cout << "before = " << Stock->User_Count - 2 << std::endl;
				Stock->User_Count++;
				//std::cout << "after = " << Stock->User_Count - 2 << std::endl;
			/*	(popoll + Stock->User_Count - 1)->fd = new_fd;
				(popoll + Stock->User_Count - 1)->events = POLLIN;
				(popoll + Stock->User_Count - 1)->revents = 0;*/
				(popoll + a + 1)->fd = new_fd;
				(popoll + a + 1)->events = POLLIN;
				(popoll + a + 1)->revents = 0;
				Stock->client_fd[a] = new_fd;
				Stock->User = a;
			Check_FD(Stock);
					break;
					}
				}
				
			//	Stock->Nicks.push_back("\0");
			//	Stock->Identities[Stock->User_Count - 2].push_back("\0");
			//	std::cout << "new fd is " << new_fd << std::endl;

			}
		/*	else
			{
				for (int a = 0; a < Stock->User_Count; a++)
				{
					if (a != 0 && ((popoll + a)->revents & POLLIN) == POLLIN)
					{
						Stock->User = a - 1;
			Check_FD(Stock);
			//			std::cout << "pollfd is " << (popoll + a)->fd << std::endl;
						std::cout << "User check = " << Stock->User << std::endl;
						break;
					}
				}
		//	}*/
			Check_FD(Stock);
	/*		for (int a = 0; a < Stock->User_Count; a++)
			{
				if ((popoll + a)->revents & POLLIN)// == POLLIN)
				{
					Stock->User = a - 1;
			//			std::cout << "pollfd is " << (popoll + a)->fd << std::endl;
			//		std::cout << "User check = " << a << std::endl;
					break;
				}
			}*/
			if (recv(Stock->client_fd[i], NULL,1, MSG_PEEK | MSG_DONTWAIT) != 0)
			{
				Stock->User = i;
				if (receive_message(Stock->client_fd[i], Stock) == 0)
				{
					command_check(Stock->client_fd[i], Stock);
				}
			}
			Check_FD(Stock);
				
				//	break;
		}
//				break;
//	}
//			break;
	//	}
	}
	return 0;
}

