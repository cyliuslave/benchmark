#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<time.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

#define N 2000
#define M 1000

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    clock_t t1;    
    char *buffer;
    unsigned int size_buffer=1;
    double result=0;
    int i,j,k;
    

    if (argc < 4) {
       fprintf(stderr,"usage %s hostname port array_size(bytes)\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    size_buffer = atoi(argv[3]);
    if(size_buffer<255){
        printf("buffer size should be equal or larger than 255\n");    
        return -1;
    }
    buffer = (char*) malloc(size_buffer);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,size_buffer);
    sprintf(buffer,"I am a client\n");
    //fgets(buffer,255,stdin);
    n = write(sockfd,buffer,size_buffer);
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,size_buffer);

    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    free(buffer);
    return 0;
}
