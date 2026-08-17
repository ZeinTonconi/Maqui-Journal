# 1. Tiempo de lectura:
he necesitado **8 minutos** para ENTENDER el problema.<br/>
principalmente porque solo leyendo sin tener una **representacion <br/>
visual clara** (MODELO MATEMATICO) tuve que volver a leer varias veces diferentes <br/>
parrafos del statement.

## Solucion para evitar leer DEMASIADAS veces el statement:
Hacer una **representacion visual del MODELO MATEMATICO mas CONCRETO Y COMPLEJO** y en base a este <br/>
dibujo **hacer MATCHEAR las palabras del statement con el dibujo**. <br/>
**Rehacer el MODELO hasta lograr el MATCH**: Un modelo matematico es NO ambiguo.

# 2. Tiempo de pensamiento:
**16 minutos**, esto fue para "demostrar que mi Core idea funciona", sin embargo <br/>
en un punto dije "lo demas parece un Problema de implementacion, entonces voy <br/>
a codear y averiguarlo durante el camino"... Error GRAVISIMO. <br/>

# 3. Tiempo de implementacion:
**46 minutos**, esto fue por delegar un problema que era de estructurar bien los casos <br/>
(deberia ir en el "Tiempo de pensamiento") a un "Problema de implementacion", basicamente <br/>
me quede estancado como MEDIA HORA tratando de $\color{#CC2936}{\text{\bf ORGANIZAR LOS PASOS Y PIEZAS}}$ para la dimension Y. <br/>
(Primero hacia la dimension X, luego la Y), entonces he confundido un "Problema de Implementacion" <br/>
con lo que deberia haber sido un "Problema de Estructuracion Logica". <br/>


Especificamente con "Problema de Estructuracion Logica" aca me refiero a: <br/>

## 3.1. (que deberia ser 2.1. en realidad) Profundidad de pensamiento Logico: <br/>

* Se usa un FLOWCHART https://en.wikipedia.org/wiki/Flowchart para ORGANIZAR INFORMACION LOGICA.
* Sacado del link: "Two of the many benefits are that flaws and bottlenecks may become apparent.".
* POR QUE podemos darnos cuenta de fallas/bottlenecks en las flowcharts? porque en realidad un flowchart contiene INFORMACION LOGICA (CASOS, PROCESOS...).
* En este caso particular, el "Problema de Estructuracion Logica" encaja perfectamente con que en Flowcharts podemos hacer CASOS (if) pero no de la forma "convencional" sino que estos CASOS contienen INFORMACION MATEMATICA (particularmente en este problema es util PARTICIONAR el "Espacio Muestral de Posibilidades" en dichos CASOS y se pueden ver las cajitas de "PROCESO" como una "TRANSFORMACION de un OBJETO/FUNCION" (un ejemplo de esto es una Transformacion Lineal) y por lo tanto luego de aplicar esta "FUNCION" nosotros SABEMOS LO QUE NOS VA A DEVOLVER ESA FUNCION, en este problema particular se podria observar que primero se transforma el objeto "px" en la suma del prefijo hasta la coordenada x de la query).
* En resumen, el flowchart contiene INFORMACION LOGICA MATEMATICA que nos ayuda a debugear nuestra PROPIA LOGICA (INTERNA).

* Una observacion particular de este problema tambien es que le ponemos de nombre "Profundidad de pensamiento Logico" porque en el mismo proceso de crear la flowchart se obtuvo la solucion, pero como en todo, hubo un GRADO DE INCERTIDUMBRE: No obtuvimos la solucion completa hasta completar la flowchart... si, obtuvimos soluciones a problemas "PARCIALES/SIMILARES" al original (ejemplo: la parte donde se soluciona para cuando y=infinito y x puede ser cualquier numero que el input lo permite), pero solo al completarlo se obtuvo la "full solution".

* Por lo tanto es cierto: no era un problema de implementacion, era un problema de estructuracion logica (si estructuraba bien y $\color{#CC2936}{\text{\bf COMPLETO}}$ el proceso en un flowchart, la implementacion era traducir esa logica a c++).
