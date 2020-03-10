CC:= gcc
CFLAGS:= -g -Wall
RM:= rm

all:  Client Server Serverv2

Client: Client.c 
	$(CC) $(CFLAGS) -Wcpp -o Client Client.c 

Server: Server.c 
	$(CC) $(CFLAGS) -Wcpp -o Server Server.c 

Serverv2: Serverv2.c 
	$(CC) $(CFLAGS) -Wcpp -o Serverv2 Serverv2.c 

clean: 
	$(RM) Client
	$(RM) Server
	$(RM) Serverv2