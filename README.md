# AED_Grupo3_Proyecto

Integrantes:
- Sebastian Peralta
- Franco Bolaños
- Mario Chincha
- Jose Wong

## Introduccion
Con la evolución tecnológica de los últimos años, hemos entrado a una era en la que cada vez más aplicaciones se digitalizan, o son nativas digitales. Uno de los inventos más disruptivos que acompañó esta digitalización masiva es el Blockchain. 

Opera escencialmente como una base de datos distruida que permite registrar información relevante de forma segura y transparente gracias a los algoritmos que se emplean. Desde una perspectiva técnica se puede entender como una estructura de datos que almacena información en bloques, reconocibles mediante una identificación hash, que se encuentran enlazados con el bloque creado previamente y el siguiente creado (cita a CEPAL). 


## Caso de estudio : Retiro de dinero
El caso de estudio utilizado para el desarrollo de este proyecto es el retiro de dinero en un banco desde una cuenta personal. Se plantea que la entidad bancaria guarda una cantidad "n" de registros por bloque de la cada (blockchain), cada uno de estos registros corresponden a una transacción que indica los siguientes parámetros:
- Cliente: nombre y apellido del cliente poseedor de la cuenta desde la que se realiza el retiro.
- Lugar: dirección del cajero en el que se realizó el retiro.
- Monto: cantidad en soles retirada.
- Fecha: día, mes y año en el que se realizó la transacción.



## Importancia de Bockchain
La tecnología blockchain hoy en día es sujeto de investigación en diversas disciplinas, cuya importancia des principalmente relevante para ciencias de la computación, ingeniería, telecomunicaciones, negocios y economía según Xu (xu, Chen y Kou). Algunas de sus principales ventajas, de acuerdo con Gokhan y Tektas (cita) son:
- Descentralización: utiliza transacciones peer to peer, lo que reduce la sobrecarga de una sola unidad de gestión como sucedería en un sistema centralizado. Esto mejora la eficiencia al reducir los cuellos de botella. Además permite aumentar su confiabilidad, al estar virtualmente siempre disponible al utilizar múltiples unidades de gestión.
- Ejecución automática de contratos: utiliza contratos inteligentes, los cuales pueden definirse como protocolos de la transacción que ejecutan los terminos del contrato. 
- Auditabilidad: está sustentada en la propiedad de transparencia e inmutabilidad de la red. Cada usuario (nodo) de la red contiene una copia de la cadena, por lo que puede verificar los valores de identificación de los bloques. Cada bloque en una blockchain contiene, además de su propia identificación, la de su bloque predecesor. Esto aumenta la trazabilidad del sistema en general y la detección de fraudes (cambios den las transacciones de los bloques), lo que asegura la inmutabilidad de la red.
- Anonimidad: 
- Prueba de trabajo

En este sentido tecnología blockchain se caracteriza por su descentralización, seguridad, confiabilidad y transparencia.




## Implementacion de la blockchain

Cada bloque de información en una blockchain contiene registros sobre algún evento, ordenados en una lista enlazada, como por ejemplo, votos o transacciones monetarias. Esta información es utilizada para crear un hashcode para el bloque. Además, el hashcode de un bloque también depende del hashcode del bloque previo, lo cual es una medida que permite asegurar mejor la integridad de la blockchain, al forzar el recálculo del hashcode de todos los bloques sucesores. A ello se le suma que la información de los bloques está compartida entre los diferentes usuarios de una red, por lo que si se cambia la información de un bloque, cambiaría la información de los bloques sucesores y se detectaría la modificación por comparación con las copias de los usuarios de la red. Además, se tiene la técnica de proof of work, la cual consiste en usar un algoritmo de encriptación para encontrar una clave que satisface un requerimiento definido a partir de la información contenida en el bloque y un valor adicional variable, llamado nonce.
![image](https://github.com/JoseFrancisc0/AED_Grupo3_Proyecto/assets/54275767/3a20dea7-b182-44e1-b54f-7dcd185535c0)
imagen: https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8805074

![image](https://github.com/JoseFrancisc0/AED_Grupo3_Proyecto/assets/54275767/a3a471af-e5c4-4048-9e00-362207764a7f)
imagen: https://repositorio.cepal.org/bitstream/handle/11362/47165/1/S2100364_en.pdf


### Estructuras de datos utilizadas

### Proof of work

## Indexacion de bloques

### Equal to X

### Between X and Y

## Conclusiones

## Bibliografia
Szabo, N. (2018). Smart Contracts : Building Blocks for Digital Markets.
@inproceedings{Szabo2018SmartC,
  title={Smart Contracts : Building Blocks for Digital Markets},
  author={Nick Szabo},
  year={2018}
}



