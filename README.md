# c-socket-example-with-docker
Contains a client type socket and server type sockets in c language with the dockerfile required to produce the docker image and te command required to make a test

## About this repository

* Client.c: Contains the client socket implementation (use the ./Client command to see the correct usage)
* Server.c: Contains a server socket implementation that receives one petition (use the ./Server command to see the correct usage).
* Serverv2.c: Contains a server socket implementation that receives multiples petitions (use the ./Serverv2 command to see the correct usage).
* Makefile: The **makefiles** are the text files used by the make application to manage the compilation of programs.
* LICENSE
* README.md: This file.

## Create the docker image

1. Download the repository

2. Open a terminal in the downloaded repository

3. Execute the next command 

   ```
   docker build -t demo:sockets .
   ```

### Make a test

1. Run the Server application

   1. Open a terminal and run the following command:

      ```
      #Show the correct usage
      docker run --rm -ti --name tests1 -p 51000:51000 demo:sockets ./Server
      #Run a correct server
      docker run --rm -ti --name s1 -p 51000:51000 demo:sockets ./Server 51000
      #Wait for a client petition and see the message
      ```

   2. Open a new terminal and run

      ```
      #Show the correct usage
      docker run --rm -ti --name testclient demo:sockets ./Client 172.17.0.1
      docker run --rm -ti --name client demo:sockets ./Client 172.17.0.1 51000
      #Writes a message and press enter
      ```

2. Run the Serverv2 application (this application can receive multiple petitions)

   1. Open a terminal and run the following command:

      ```
      #Show the correct usage
      docker run --rm -ti --name tests2 -p 52000:52000 demo:sockets ./Serverv2
      #Run a correct server
      docker run --rm -ti --name s2 -p 52000:52000 demo:sockets ./Serverv2 52000 100
      #Wait and see the received messages
      ```

   2. Open a new terminal and run the following command:

      ```
      docker run --rm -ti --name client demo:sockets ./Client 172.17.0.1 52000
      #Writes a message and press enter
      ```

      