# Chat entre computadoras en la misma red
## Noble Team
### Planteamiento del problema 
###### Satisfacer y cumplir con las necesidades de cliente, mantener la transparencia en los procesos, son objetivos que tiene una empresa para su relación empresa-cliente para ello existen medios de comunicación como el teléfono, un dispositivo de respuesta instantánea, el correo electrónico el medio de comunicación más utilizado por las empresas ya que brinda almacenamiento, clasificación y transferencia rápida de archivos a través de internet.
###### Para este proyecto orientamos la importancia de mantener a una corporación unida y en comunicación en los procesos de la empresa para el intercambio de información y transferencia de datos o archivos, así como, la agilidad y disponibilidad en el trabajo de equipo buscando su valor y crecimiento. 
###### Se planea construir un programa para el intercambio de información y comunicación entre dos computadoras implementando un chat de manera local, es decir en la misma red. A partir de la necesidad de facilitar la comunicación y la interoperalidad entre dispositivos, pero para lograr este objetivo se tendrá que considerar ciertas cosas a nivel sistema operativo para que no sucedan algunos problemas o errores al momento de la conexión y comunicación entre computadoras.
###### Uno de los problemas puede ser la definición de un socket incorrecto por lo cual es muy importante verificar y asegurarse de tener los datos correctos de origen y destino. Los recursos no disponibles pueden ser otro de los problemas por lo que se necesita verificar los recursos disponibles en cada dispositivo. Existen otros problemas cómo: \cite{ibm:2014}
  * Un argumento que se pasa una función específica no sea válido o el socket este cerrado.
  * Demasiados archivos abiertos en el sistema pueden no alcanzar los recursos.
  * Un proceso interrumpido.
  * El nombre de sistema principal o la dirección IP que se ha especificado no está disponible desde el sistema local.
  * Que no haya una ruta hacia el sistema principal.
  * La conexión ha sobrepasado el tiempo de espera.
  * Una sobregrabación de memoria o de desbordamiento de almacenamiento intermedio.
  * En la función de conexión, que se agote el rango asignado para los puertos temporales TCP/UDP.
###### Este proyecto será compartido con la materia de Protocolos y Comunicación de Datos y Control Digital. La aportación que tendrá este proyecto con base al módulo de sistemas operativos será la parte de programación y configuración de los sockets en servidor/cliente a través de línea de comando a nivel de sistema operativo para la configuración en el reconocimiento entre IP’s para que se vean entre dispositivos y establecer una comunicación entre una computadora y otra  resaltando el uso de la librería de Open MPI para realizar la interfaz en el paso de mensajes y algunos comandos para visualizar ciertos estados de la red.

