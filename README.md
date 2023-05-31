# AED_Grupo3_Proyecto

Integrantes:
- Sebastian Peralta
- Franco Bolaños
- Mario Chincha
- Jose Wong

## Introduccion
Con la evolución tecnológica de los últimos años, hemos entrado a una era en la que cada vez más aplicaciones se digitalizan, o son nativas digitales. Uno de los inventos más disruptivos que acompañó esta digitalización masiva es el Blockchain. Opera escencialmente como una base de datos distruida que permite registrar información relevante de forma segura y transparente gracias a los algoritmos que se emplean. Desde una perspectiva técnica se puede entender como una estructura de datos que almacena información en bloques, reconocibles mediante una identificación hash, que se encuentran enlazados con el bloque creado previamente y el siguiente creado (cita a CEPAL). 



## Caso de estudio : Retiro de dinero
El caso de estudio utilizado para el desarrollo de este proyecto es el retiro de dinero en un banco desde una cuenta personal. Se plantea que la entidad bancaria guarda una cantidad "n" de registros por bloque de la cada (blockchain), cada uno de estos registros corresponden a una transacción que indica los siguientes parámetros:
- Cliente: nombre y apellido del cliente poseedor de la cuenta desde la que se realiza el retiro.
- Lugar: dirección del cajero en el que se realizó el retiro.
- Monto: cantidad en soles retirada.
- Fecha: día, mes y año en el que se realizó la transacción.

## Importancia de Bockchain
La tecnología blockchain hoy en día es sujeto de investigación en diversas disciplinas, cuya importancia des principalmente relevante para ciencias de la computación, ingeniería, telecomunicaciones, negocios y economía según Xu (xu, Chen y Kou). Algunas de sus principales ventajas, de acuerdo con Gokhan y Tektas (cita) son:
- Descentralización
- Ejecución automática de contratos
- Auditabilidad
- Persistencia
- Anonimidad

En este sentido tecnología blockchain se caracteriza por su descentralización, seguridad, confiabilidad y transparencia.




## Implementacion de la blockchain

Cada bloque de información en una blockchain contiene registros sobre algún evento, ordenados en una lista enlazada, como por ejemplo, votos o transacciones monetarias. Esta información es utilizada para crear un hashcode para el bloque. Además, el hashcode de un bloque también depende del hashcode del bloque previo, lo cual es una medida que permite asegurar mejor la integridad de la blockchain, al forzar el recálculo del hashcode de todos los bloques sucesores. A ello se le suma que la información de los bloques está compartida entre los diferentes usuarios de una red, por lo que si se cambia la información de un bloque, cambiaría la información de los bloques sucesores y se detectaría la modificación por comparación con las copias de los usuarios de la red. Además, se tiene la técnica de proof of work, la cual consiste en usar un algoritmo de encriptación para encontrar una clave que satisface un requerimiento definido a partir de la información contenida en el bloque y un valor adicional variable, llamado nonce.

### Estructuras de datos utilizadas

### Proof of work

## Indexacion de bloques

### Equal to X

### Between X and Y

## Conclusiones

## Bibliografia


