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
int iniciarPeticion(char *direccionIP, int numeroPuerto);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        mostrarUso(argv[0]);
    } else {
        return iniciarPeticion(argv[1], atoi(argv[2]));
    }
}

void mostrarUso(char * nombreAplicacion){
    printf("Error al ejecutar la aplicación, el número de parámetros es incorrecto.\n");
    printf("La forma correcta de ejecutar la aplicación es la siguiente:\n");
    printf("%s direccionIP numeroPuerto\n", nombreAplicacion);
    printf("En dónde:\n");
    printf("%s: Es el nombre del binario que se esta ejecutando\n", nombreAplicacion);
    printf("direccionIP: Es la dirección ip del equipo en el que fue lanzada la aplicación servidor\n");
    printf("numeroPuerto: Es el puerto por el que se realizará la escucha de peticiones\n");
    printf("Por Ejemplo:\n");
    printf("\t%s 127.0.0.1 55000\n", nombreAplicacion);
}

int iniciarPeticion(char *direccionIP, int numeroPuerto){
        int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[256];
    
    
    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        perror("Error: No se pudo crear el socket");
        return EXIT_FAILURE;
    }
        
    server = gethostbyname(direccionIP);
    
    if (server == NULL) {
        fprintf(stderr,"Error: No fue posible verificar al host\n");
        return EXIT_FAILURE;
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(numeroPuerto);
    
    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error: No se pudo realizar la conexión");
        return EXIT_FAILURE;
    }
    
    /* Now ask for a message from the user, this message
        * will be read by server
    */
        
    printf("Ingrese el mensaje que dese enviar al servidor: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    
    /* Send message to the server */
    n = write(sockfd, buffer, strlen(buffer));
    
    if (n < 0) {
        perror("Error: El cliente no pudo enviar el mensaje");
        return EXIT_FAILURE;
    }
    
    /* Now read server response */
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    
    if (n < 0) {
        perror("Error: El cliente no pudo leer el mensaje");
        return EXIT_FAILURE;
    }
        
    printf("El servidor respondío: %s\n",buffer);
    return EXIT_SUCCESS;
}