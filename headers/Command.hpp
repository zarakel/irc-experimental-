#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Stock.hpp"

int		PASS(int poll_fd, Stock *Stock);
int		NICK(int poll_fd, Stock *Stock);
int		JOIN(int poll_fd, Stock *Stock);
int		PRIVMSG(int poll_fd, Stock *Stock);


#endif
