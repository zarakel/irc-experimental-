#include "../../headers/headers.hpp"
/*
11. PASS [ConferenceRoom]
* La commande /pass te permet d'indiquer le mot de passe de ton nickname au serveur.
En effet, certains réseaux autorisent l'enregistrement de nickname, 
protégé par mot de passe. Si c'est toi qui as enregistré le nickname que tu utilises, 
utilises la commande /pass, sinon change de nickname via la commande /nick 
(sinon tu seras déconnecté du réseau au bout de quelques secondes, Killed).
    * Syntaxe : /pass <motdepasse>
    * Example : /pass COOLPASSWORD
    * 
*/

int	PASS(int poll_fd, std::string pass, std::string rcv_pass)
{
	if (pass.compare(rcv_pass) == 0)
	{
		if (send(poll_fd, "You're authorized !\n\r", 21, 0) == -1)
			perror("send");
//              authentification réussi, pour le pass en tout cas
		return (3);
	}
	else
	{
//		voir comment doivent etre géré les numerics
		std::cout << "le mot de passe invalide est : " << rcv_pass << std::endl;
		if (send(poll_fd, "Casse toi pov' con !\n\r", 22, 0) == -1)
			perror("send");
		close(poll_fd);
		return (400);
	}	
}