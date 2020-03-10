# Genera una imagen de contenedor que contiene los sockets del tipo cliente y servidor
# Creador: Hugo German Reyes Anastacio
# Mail: hugo.reyes@cinvestav.mx
# Se indica la imagen base
FROM hgreyesa/base
# Se copia el archivo de configuración
COPY code /app/
# Se copia la aplicación del trabajador a la imagen
WORKDIR /app/
RUN make

#docker build -t demo:sockets .
