#ifndef SERVER_HPP
# define SERVER_HPP

#include "Stock.hpp"

void    sigchld_handler( void );
void    *get_in_addr(struct sockaddr *sa);
void    Check_ID(Stock *Stock, char *s, int new_fd);
int     server(Stock *Stock);

#endif
