//Dependencias para uso de funciones básicas en c
#include <stdio.h>
#include <stdlib.h>
//Dependencuas para el uso de sockets
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
//Dependencias para el manejo de funciones sobre cadenas de texto
#include <string.h>


void mostrarUso(char * nombreAplicacion);
int iniciarEscucha(int numeroPuerto, int numeroPeticiones);

int atenderPeticion (int sock);

int main( int argc, char *argv[] ) {

    if (argc != 3) {
        mostrarUso(argv[0]);
    } else {
        return iniciarEscucha(atoi(argv[1]), atoi(argv[2]));
    }

}


void mostrarUso(char * nombreAplicacion){
    printf("Error al ejecutar la aplicación, el número de parámetros es incorrecto.\n");
    printf("La forma correcta de ejecutar la aplicación es la siguiente:\n");
    printf("%s numeroPuerto numeroPeticiones\n", nombreAplicacion);
    printf("En dónde:\n");
    printf("%s: Es el nombre del binario que se esta ejecutando\n", nombreAplicacion);
    printf("numeroPuerto: Es el puerto por el que se realizará la escucha de peticiones\n");
    printf("numeroPeticiones: Es la cantidad de máxima de peticiones concurrentes que aceptará este servidor\n");
    printf("Por Ejemplo:\n");
    printf("\t%s 55000 100\n", nombreAplicacion);
}

int iniciarEscucha(int numeroPuerto, int numeroPeticiones){ 
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int pid;
    
   /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        perror("ERROR opening socket");
        return EXIT_FAILURE;
    }
    
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(numeroPuerto);
    
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        return EXIT_FAILURE;
    }
    
    /* Now start listening for the clients, here
        * process will go in sleep mode and will wait
        * for the incoming connection
    */

    listen(sockfd, numeroPeticiones);
    clilen = sizeof(cli_addr);
    
    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        
        if (newsockfd < 0) {
            perror("ERROR on accept");
            return EXIT_FAILURE;
        }
        
        /* Create child process */
        pid = fork();
            
        if (pid < 0) {
            perror("ERROR on fork");
            return EXIT_FAILURE;
        }
        
        if (pid == 0) {
            /* This is the client process */
            close(sockfd);
            return atenderPeticion(newsockfd);
        }
        else {
            close(newsockfd);
        }
            
    } /* end of while */
}



int atenderPeticion (int sock) {

    int n;
    char buffer[256];
    bzero(buffer,256);
    n = read(sock,buffer,255);
    
    if (n < 0) {
        perror("Error: El servidorv2 no pudo realizar la lectura del mensaje\n");
        return EXIT_FAILURE;
    }
    
    printf("El mensaje recibido desde el cliente es: %s\n",buffer);
    n = write(sock,"Recibí tu mensaje correctamente",31);
    
    if (n < 0) {
        perror("Error: El servidorv2 no pudo enviar el mensaje\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}