//  Name: An Vo
//  Class: Intro to Computer Networking
//  Assignment: Lab 2
//  Client.cpp
// asdf
//  PLEASE READ: Used Hieu Nguyen's template from canvas.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "Functions.h"
#define PORT 3490 // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once
using namespace std;

int main(int argc, char *argv[])
{

//------------ESTABLISH CONNECTION TO SERVER ---------------
    int sockfd, numbytes;
    struct hostent *he;
    struct sockaddr_in their_addr; // connector's address information
    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }
    if ((he=gethostbyname(argv[1])) == NULL) {  // get the host info
        herror("gethostbyname");
        exit(1);
    }
    printf("client: get the server info \n");
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {   // get the socket file
        perror("socket");
        exit(1);
    }
    printf("client: creating socket file \n");
    their_addr.sin_family = AF_INET;    // host byte order
    their_addr.sin_port = htons(PORT);  // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)he->h_addr); // store server ip addess (from the
    // gethostbyname function)
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);
    if (connect(sockfd, (struct sockaddr *)&their_addr,     // connect to server
                sizeof their_addr) == -1) {
        perror("connect");
        exit(1); }
    printf("client: connecting to the server \n");
//------------------------------------------------------------------



// -------- ONCE CONNECTED ---------------------
    // WELCOME MESSAGE:
        cout << "WELCOME TO THE FILE TRANSFER PROGRAM" << endl;
        cout << "Commands include: " << endl;
        cout << "- 'ls' [optional args]" << endl;
        cout << "- 'pwd'" << endl;
        cout << "- 'spwd'" << endl;
        cout << "- 'catalog'" << endl;
        cout << "- 'upload' [filename]" << endl;
        cout << "- 'download' [filename]" << endl;
        cout << "- 'bye'" << endl;

    bool connection = true;
    do{
        char buffer[MAXDATASIZE];          // BUFFER TO SEND DATA
        if ((numbytes=recv(sockfd, buffer, MAXDATASIZE-1, 0)) == -1) {             //receiving data from server to check for connection
          perror("recv");
          exit(1);
          }


//------------------------------------------------------
        char* cmds[3] = {NULL, NULL, NULL};
        string cmd, args, input;
        int checkStr;
        cout << "\nTYPE COMMAND ---> ";
        getline(cin, input);
        istringstream iss(input);
        iss >> cmd >> args;
        if((checkStr = checkString(cmd)) != -1){
          if(checkStr == 0){
            cout << "Closeing Connection" << endl;
            close(sockfd);
            connection = false;
          }

          else if((checkStr < 3) && (checkStr > 0)){
            populateCommands(cmds, cmd, args);         // Populate cmd into char* cmds and fork
            forkIt(cmds);                             // THIS HANDLES ls AND pwd
            }
          else if ((checkStr >= 3) && (checkStr <= 4)){
            cout << "COMMAND SENT OVER TO SERVER" << endl;
            cout << "server is not capable of processing this command yet" << endl;
            // buffer[0] = *cmds[0];
            // buffer[1] = *cmds[1];
            // buffer[2] = *cmds[2];
            // cout <<  "SENding" << endl;
            if(send(sockfd, cmds, 3, 0) < 1){
              perror("Sending Failed: ");
            }
            // cout << "Sent" << endl;
          }
          else{
            // send over file to the server.
            cout << "UPLOAD OR DOWNLOAD FILE OVER TO THE SERVER" << endl; // PLACE HOLDER TO SEND FILE DELETE AFTER.
            cout << "server is not capable of processing this command yet" << endl;

          }
        }
        else{
            cout << "Command Not Found" << endl;
        }
            // compare string to array
            // return array position if in array
            // else return "ERROR MESSAGE"


        // print what server sends back
//------------------------------------------------------

            //if(send(sockfd, "bye", 3, 0) == -1){
             //   perror("Sending error");
              //  exit(1);
            //}
            //connection = false;
    }while(connection != false);
    close(sockfd);

    return 0;
}
