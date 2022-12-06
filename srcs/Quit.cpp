#include "../headers/headers.hpp"
#include "../headers/answer.hpp"
#include "../headers/Quit.hpp"
#include "../headers/Server.hpp"

int QUIT(int poll_fd, Stock *Stock)
{
	std::string reason = "Quit : ";
	
	if (Stock->line.size() > 1)
		reason += Stock->line[1];

	for (size_t i = 0; i < reason.size(); i++)
	{
		if (send(poll_fd, &reason[i], 1, 0) == -1)
			perror("send :");
	}

	for (int a = 0; Stock->Channel_Count > 0 &&
	a < Stock->Channel_Count; a++)
	{
		Stock->Channels_Users[Stock->Channels[a][0]][Stock->User].clear();
		Stock->Channels_Users[Stock->Channels[a][0]][Stock->User].resize(0);
		Stock->Channels_Invite[Stock->Channels[a][0]][Stock->User] = 0;
		Stock->Channels_Op[Stock->Channels[a][0]][Stock->User] = 0;
	}
	if (Stock->Identities.size() > 0)
	{
	/*	Stock->Identities[Stock->User].clear();
		Stock->Identities[Stock->User].resize(0);*/
		Stock->Identities.erase(Stock->User);
	}
	if (Stock->Users.size() > 0)
	{
		/*Stock->Users[Stock->User].clear();
		Stock->Users[Stock->User].resize(0);*/
		Stock->Users.erase(Stock->User);
	}
	Stock->tmp_pass[Stock->User] = 0;
	Stock->tmp_nick[Stock->User] = 0;
	Stock->tmp_user[Stock->User] = 0;
	Stock->authentified[Stock->User] = 0;
	close(Stock->client_fd[Stock->User]);
	Stock->line.clear();
	return (0);
}
