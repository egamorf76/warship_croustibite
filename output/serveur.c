#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
const int port = 8000;
int main(int argc, char **argv)
{

    struct sockaddr_in my_adr;
    struct sockaddr_in serveur_adr;
    char buf[1234];
    int sz_buf;
    socklen_t sz_sock_serveur;
    int sock, sock_distante;
    /* ouverture d'une socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* cration d'une adresse locale */
    memset(&my_adr, '\0', sizeof(my_adr));
    my_adr.sin_family = AF_INET;
    my_adr.sin_port = htons(port);
    my_adr.sin_addr.s_addr = INADDR_ANY;
    /* association de l'adresse locale a la socket */
    bind(sock, (struct sockaddr *)&my_adr, sizeof(struct sockaddr_in));
    /* attente des clients */
    listen(sock, 1);
    while (1)
    {
        sz_sock_serveur = sizeof(serveur_adr);
        /* recupere les donnes du client */
        sock_distante = accept(sock, (struct sockaddr *)&serveur_adr, &sz_sock_serveur);
        /* lecture de la chaine */
        sz_buf = read(sock_distante, buf, 1234);
        buf[sz_buf] = '\0';
        printf("%s\n", buf);
        close(sock_distante);
    }
    close(sock);
    return 0;