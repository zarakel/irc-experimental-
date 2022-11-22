#ifndef SERVER_HPP
# define SERVER_HPP

#include "Stock.hpp"

void    sigchld_handler( void );
void    *get_in_addr(struct sockaddr *sa);
int    Check_FD(Stock *Stock, struct pollfd *popoll);
int     server(Stock *Stock);

#endif
