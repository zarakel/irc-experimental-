#include "../headers/headers.hpp" 
#include "cmds/passCmd.cpp"
#include "cmds/nickCmd.cpp"
#include "parse_message.cpp"

#define BACKLOG 10   // how many pending connections queue will hold

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int server(char *PORT, std::string pass)
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct pollfd popoll;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
	int count = 0;

    std::cout << "Le pass est censé être : " << pass << std::endl;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    memset(&popoll, 0, sizeof popoll);
    popoll.events = POLLIN;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);
	popoll.fd = new_fd;
//	probleme : je ne suis pas sur de reussir a vraiment réaliser le test du pdf,     	a tester ! 
//	probleme 2 : j'utilise poll en mode bloquant, ca n'a pas l'air de correspondre a  l'exercice. Je peux regler ca mais est-ce optimal ?  
	std::cout << "(Bienvenue sur le serveur, veuillez taper votre pass.)" << std::endl;
	if (poll(&popoll, 1, 10000000) == 1) 
	{
	    try
	    {
//		l'ensemble de l'authentificattion est a faire avec pass et nick 
	        receive_message(popoll.fd, pass);
// avoir un vector avec toutes les commandes accessibles aux clients non enregistrés		puis comparé chaque membre du vector avec ce qui est recu de recv()
// il faut être capable de determiner si le client est connu ou pas
// sachant qu'on allumera et eteindra le serveur, chaque allumage ne contiendra aucune 	   info
				
	    }
	    catch (const std::exception & e)
	    {
		std::cerr << s << e.what() << std::endl;
		return (464);
	    }
            close(new_fd);
	    close(popoll.fd);
	}
    }
    return 0;
}
