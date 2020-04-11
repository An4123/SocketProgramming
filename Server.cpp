//  Name: An Vo
//  Class: Intro to Computer Networking
//  Assignment: Lab 2
//  Server.cpp
//  
//  PLEASE READ: Adaptation of Hieu Nguyen's and Beej's Guide to Network Programming

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define MYPORT 3490 // the port users will be connecting to
#define BACKLOG 10   // how many pending connections queue will hold
#define MAXDATASIZE 100 // max number of bytes we can get at once
using namespace std;

void sigchld_handler(int s)
{
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


int main(void)
{
    int serverSocket, clientSocket, received;                  // Lisening on sock_fd, and a new connection will be made on clientSocket
    struct sockaddr_in serverAddress;          // My address information information
    struct sockaddr_in clientAddress;       // Clients's address information
    socklen_t sin_size;
    struct sigaction sa;

    int yes=1;

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  // get the socket file
        perror("socket");
        exit(1);
    }

    printf("server: creating socket file \n");
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    serverAddress.sin_family = AF_INET;        // host byte order
    serverAddress.sin_port = htons(MYPORT);    // short, network byte order
    serverAddress.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);


    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof serverAddress) == -1) {
        perror("bind");
        exit(1);    
    }


    printf("server: binding the socket file to the local machine \n");

    if (listen(serverSocket, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    printf("server: listening for incomming connections \n");

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1); 
    }


    while(1) {  // main accept() loop
        sin_size = sizeof clientAddress;

        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &sin_size)) == -1) {
            perror("accept");
            continue;
        }

        printf("server: got connection from %s\n", inet_ntoa(clientAddress.sin_addr));


        // Child Process
        if (!fork()) {  
            close(serverSocket);                                          // child doesn't need the listener
            if(send(clientSocket, "Hello\n",6,0) == -1){
                perror("Connection Error");
                exit(1);
            }
            
            bool conn = true;
            int MaxDataSize = MAXDATASIZE;
            do{
                char buf[MaxDataSize];
                int recieved, checkConnection;
      
                // check to see if the connection is there by sending a message.
                checkConnection = send(clientSocket, buf, recieved,0);                
                if(checkConnection < 0){
                    close(clientSocket);
                    printf("server: close connection from %s\n", inet_ntoa(clientAddress.sin_addr));
                    exit(0);
                    conn = false;
                }

                // if the connection is there open to recieve messages
                recieved = recv(clientSocket, buf, MAXDATASIZE-1,0);
                if(recieved > -1){
                    buf[recieved-1] = '\0';
                    cout << "Recieved: " << buf << " from " << inet_ntoa(clientAddress.sin_addr) << endl;
                }
                else{
                    perror("Receiving Failed");
                    close(clientSocket);
                    conn = false;    
                }

            }while(conn != false);

            close(clientSocket);
            printf("server: close connection from %s\n", inet_ntoa(clientAddress.sin_addr));
            exit(0);
        }
    }
    return 0; 
}
