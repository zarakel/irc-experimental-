/*#include "../../headers/headers.hpp"

char	*NICK()
{
	char buf[9999];
//      probleme : meme prblm qu'avec poll, c'est plus simple d'utiliser recv en mode           bloquant mais est-ce une bonne solution ?
        if (recv(poll_fd, buf, 9999, MSG_WAITALL) == - 1)
                perror("recv");
        for (int it = 0; buf[it] != '\n'; it++)
        {
                if (buf[it + 1] == '\n')
                {
                        buf[it + 1] = '\0';
                        break;
                }
        }
// suite des evenements : On a capte la donnée, on doit la recracher et la remonter
// mais dans quoi ??

// Peut etre ajouter sécu
	return (buf);
}*/
