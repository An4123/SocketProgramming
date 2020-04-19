#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
using namespace std;
//

void populateCommands(char* exe[], string _cmd, string _args){
    if(_args != ""){
        exe[1] = (char*) _args.c_str();
    }
    exe[0] = (char*) _cmd.c_str();
}


int checkString(string &str){
// CHECKS IF STRING USER ENTERED IS VALID BY ASSIGNING A INT VALUE
    string array[] = {"ls","pwd","spwd","catalog","upload","download"};     // array of commands
    for(int i = 0; i < 6; i++){              // checks the array for matches
        if(str == array[i]){
            if(str == "spwd"){               // translate spwd or catalog to ls or pwd for server
              str = "pwd";
            }
            if(str == "catalog"){
              str = "ls";
            }
            return i;                        // if match return the position
        }
    }
    return -1;                              // if no match then return -1
}

//void downloadFile(){}

void forkIt(char* _cmds[]){
  if(fork() == 0){
    if(execvp(_cmds[0],_cmds)){
      cout << "Command Not Found" << endl;
    }
    exit(0);
  }
  else{wait(NULL);}
}


// void sendData(int socket, char* data, int size){
//   if(send(socket, data, size, 0) < 0){
//     perror("Sending Error");
//     exit(0);
//   }
// }
//
// void recvData(int socket, char buffer, int maxSize){
//   if(recv(socket, buffer, maxSize, 0) < 0){
//     perror("Receiving Error");
//     exit(0);
//   }
// }
