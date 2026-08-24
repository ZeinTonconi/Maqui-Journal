# Core idea:
La idea principal fue NO FORZAR DEMASIADO A QUE ENCAJEN LAS PIEZAS (es decir, -- pensamiento convergente (forcing the combination) y ++ divergente (**generating patterns**) ), pero me di cuenta de la solucion acordandome que hice un problema similar de DP en Arboles en el training camp Bolivia 2026. <br/>
Entonces NO era (principalmente) un Convergent Thinking Task. <br/>
Era mas una Divergent Thinking Task. <br/>

Entonces al acordarme de dicho problema del TCBolivia 2026 era una **idea identica**: La parte **dificil era LOS ESTADOS** de la DP: <br/>
* Habia que **"Inventarse/Agregar estados"** (o sea, **la DP NO es "DIRECTAMENTE LA RESPUESTA" al problema**) para que TODO CUADRE en las Transiciones para asi poder calcular la respuesta (de un **SUBCONJUNTO de esos ESTADOS**).
* Para este problema he usado la misma idea, me "INVENTE 2 estados" pero solo 1 de ellos contenia la respuesta al problema (1 estado guardaba el maximo score en el subarbol con la arista al padre si o si apuntando hacia arriba, y el otro lo mismo pero apuntando hacia abajo).
* fue una tarea **mas DIVERGENTE** porque si **yo empezaba a buscar problemas de arboles** en mi **memoria** iba a poder encontrar **ese problema** y asi **simplemente testear (SIN HACER DEMASIADO FORCING/ACOMODACION) si la misma idea aplicaba en este problema**.
