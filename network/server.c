/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<time.h>
#include<math.h>


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
    char *buffer;
    unsigned size_buffer=1;

     struct sockaddr_in serv_addr, cli_addr;
     double result=0;
     int i,j,k;
    clock_t t1;  
    unsigned int N=1,M=1;
     int n;
     if (argc < 4) {
         fprintf(stderr,"Usage : ./server port matrix_width(sqrt(i*j+j*0.01) size_buffer\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     N = atoi(argv[2]);
     M = atoi(argv[2]);
     size_buffer = atoi(argv[3]);
    if(size_buffer<255){
        printf("buffer size should be equal or larger than 255\n");    
        return -1;
    }
    buffer = (char*) malloc(size_buffer);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
    do{
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
        if (newsockfd < 0) 
             error("ERROR on accept");
        bzero(buffer,256);
        n = read(newsockfd,buffer,size_buffer);
        t1 = clock();
        if (n < 0) error("ERROR reading from socket");

        for(i=0;i<M;i++){
           for(j=0;j<N;j++){
              result = sqrt(i*j + j*0.001);
           }
        }
        printf("dt = %f\n",(clock()-t1)/(float)CLOCKS_PER_SEC);


        printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",255);
        if (n < 0) error("ERROR writing to socket");
        close(newsockfd);
    }while(0);
    close(sockfd);
    return 0; 
}
