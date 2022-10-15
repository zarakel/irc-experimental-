#include "../../headers/headers.hpp"

int	PASS(int poll_fd, std::string pass, std::string rcv_pass)
{
	if (pass.compare(rcv_pass) == 0)
	{
		if (send(poll_fd, "You're authorized !\n\r", 21, 0) == -1)
			perror("send");
//              authentification réussi, pour le pass en tout cas
		return(3);
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
