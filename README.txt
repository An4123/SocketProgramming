Name: An Vo
Class: Intro to Computer Networking
Project: Lab2

- READ THIS: TO AVOID PLAGERISM, IM LETTING YOU KNOW THAT I USED THE CODE FROM CANVAS
             TO START AND MAKE A CONNECTION BETWEEN THE SERVER AND CLIENT.
             ALSO RESEARCHED ONLINE MORE ABOUT SOCKET PROGRAMMING.
- This can process 'ls' 'pwd' and 'bye' on the client side, and can send bytes to the server.
- Did not have enough time to finish on server side.
- Will display appropriete messages for easy navigation for the user.
- DID NOT KNOW HOW TO MAKE A MAKE FILE FOR THIS LAB.


ORGANIZATION:
---Client.cpp---
- Connects to server and can handle 'ls' and 'pwd' and 'bye'
- Can send data to server
- can print out info for the user.


---Server.cpp---
- Server can recieve bytes, but does not process the commands. (still figuring it out and did not have enough time)
- Notifies when an event is happening.

---Functions.h---
- Functions used for both server and client.


STATUS:
- Everything works and runs, getting commands to run and print takes a little.
- FORSURE "ls --a" works (will provide screenshot).

SOFT/HARDWARE:
- Tested on: CSEGRID.
- Tested on my Linux machine



HOW TO COMPILE
- unZip file.
- Run Terminal (multiple terminals for multiple clients)
- cd into unzipped file.
- run ./server first
- run ./client [ip address]
