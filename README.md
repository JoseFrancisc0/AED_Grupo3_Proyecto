# AED_Grupo3_Proyecto

Integrantes:
- Franco Bolaños
- Mario Chincha
- Sebastian Peralta
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
La tecnología blockchain fue creada como una respuesta hacia la necesidad de establecer confianza en sistema distribuido de confianza. Concretamente, la tecnología blockchain es una herramienta que ofrece la posibilidad de implementar sistemas que aseguren la válidez e inalterabilidad de documentos con sellos temporales (indicando la fecha de su existencia y de realización de la transacción) (cita a Pierro). 
La tecnología blockchain hoy en día es sujeto de investigación en diversas disciplinas, cuya importancia des principalmente relevante para ciencias de la computación, ingeniería, telecomunicaciones, negocios y economía (citar xu, Chen y Kou). Algunas de sus principales ventajas son (cita Gokhan y Tektas):
- Descentralización: utiliza transacciones peer to peer, lo que reduce la sobrecarga de una sola unidad de gestión como sucedería en un sistema centralizado. Esto mejora la eficiencia al reducir los cuellos de botella. Además permite aumentar su confiabilidad, al estar virtualmente siempre disponible al utilizar múltiples unidades de gestión.
- Ejecución automática de contratos: utiliza contratos inteligentes, los cuales pueden definirse como protocolos de la transacción que ejecutan los terminos del contrato. 
- Auditabilidad: está sustentada en la propiedad de transparencia e inmutabilidad de la red. Cada usuario (nodo) de la red contiene una copia de la cadena, por lo que puede verificar los valores de identificación de los bloques. Cada bloque en una blockchain contiene, además de su propia identificación, la de su bloque predecesor. Esto aumenta la trazabilidad del sistema en general y la detección de fraudes (cambios den las transacciones de los bloques), lo que asegura la inmutabilidad de la red.
- Anonimidad: los usuarios pueden interactuar con la red a partir de una dirección generada al azar. Dado su carácter descentralizado, no existe una autoridad central que fiscalice su registro. En este sentido un usuario puede usar múltiples direcciones dentro de la red para mantener cierto nivel de privacidad en sus transacciones y evitar exponer su identidad.
En este sentido tecnología blockchain se caracteriza por su descentralización, seguridad, confiabilidad y transparencia.


## Implementacion de la blockchain
Cada bloque de información en una blockchain contiene registros sobre algún evento, ordenados en una lista enlazada, como por ejemplo, votos o transacciones monetarias. Esta información es utilizada para crear un hashcode para el bloque. Además, el hashcode de un bloque también depende del hashcode del bloque previo, lo cual es una medida que permite asegurar mejor la integridad de la blockchain, al forzar el recálculo del hashcode de todos los bloques sucesores. A ello se le suma que la información de los bloques está compartida entre los diferentes usuarios de una red, por lo que si se cambia la información de un bloque, cambiaría la información de los bloques sucesores y se detectaría la modificación por comparación con las copias de los usuarios de la red. Además, se tiene la técnica de proof of work, la cual consiste en usar un algoritmo de encriptación para encontrar una clave que satisface un requerimiento definido a partir de la información contenida en el bloque y un valor adicional variable, llamado nonce.

De forma resumida la tecnología blockchain presenta una serie de 3 mecanismos principales para proteger la integridad de la data y evitar fraude. Dichos mecanismos son los siguientes:
- Verificación de identificaciones hash: cada bloque dentro de la cadena cuenta con un codigo hash que calcula a partir de los datos de las transacciones en el bloque y el valor nonce, pero adicionalmente el sistema blockchain añade en cada bloque la identificación hash del bloque predecesor. Esto hace que cada vez que alguien quiera modificar un bloque de la cadena se vea a obligado a modificar también todos los bloques siguientes y realizar un mayor número de cálculos.
- Proof of work: implementa un retraso temporal forzado al crear cada nuevo bloque y agregarlo a la cadena. Esto se hace para evitar el fraude aún si se tuviese suficiente capacidad computacional para recalcular las identificaciones para cada bloque de la cadena.
- Consenso: tercer y definitivo mecanismo que utiliza las propiedades de la red descentralizada y distribuida (peer to peer) para verificar la integridad de los bloques en la cadena. Para cada bloque que se añade a la cadena se debe enviar una copia del bloque a cada uno de los usuarios de la red (nodos de la red peer to peer). Entonces, dado que todos los nodos tienen acceso a la cadena completa, se realiza una votación al añadir cada nuevo bloque para verificar su integridad. Si la votación sobrepasa el 50% + 1 votos del total de miembros, entonces el bloque se admite como válido. 

![image](https://github.com/JoseFrancisc0/AED_Grupo3_Proyecto/assets/54275767/3a20dea7-b182-44e1-b54f-7dcd185535c0)

imagen: https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8805074

![image](https://github.com/JoseFrancisc0/AED_Grupo3_Proyecto/assets/54275767/a3a471af-e5c4-4048-9e00-362207764a7f)

imagen: https://repositorio.cepal.org/bitstream/handle/11362/47165/1/S2100364_en.pdf


### Estructuras de datos utilizadas
- Tablas Hash: 
- AVL Tree: 


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

@ARTICLE{8024092,
  author={Di Pierro, Massimo},
  journal={Computing in Science & Engineering}, 
  title={What Is the Blockchain?}, 
  year={2017},
  volume={19},
  number={5},
  pages={92-95},
  doi={10.1109/MCSE.2017.3421554}}


