#ifndef SERVER_HPP
# define SERVER_HPP

#include "Stock.hpp"

void    sigchld_handler( void );
void    *get_in_addr(struct sockaddr *sa);
void    Check_ID(Stock *Stock, char *);
int     server(Stock *Stock);

#endif
