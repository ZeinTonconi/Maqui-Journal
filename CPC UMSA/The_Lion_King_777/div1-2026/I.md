# Abridged problem statement:
Hay un arbol con N nodos 1<=N<=10^5 y cada nodo tiene color B o I, se requiere contar todos los pares (u,v) tal que u<=v y el numero de nodos pintados con B en el camino simple de u a v es estrictamente mayor que la cantidad de nodos pintados con I.

# Solution:
The solution is quite simple if one knows the Offline Version of Centroid Decomposition (known as Divide and Conquer on Trees): https://www.youtube.com/watch?v=3pk02p1-weU <br/>
This technique is useful here because one can use the properties told there, these 3 properties are the most important ones: <br/>
* 2 nodes u and v are separated (considering the simple path from u to v) exactly once in time.
* The sum of the # of nodes of the subtrees in the same centroid-level is at most N.
* The height of the centroid tree is O(log N).

So at each centroid found we can brute force this subtree with a DFS and just combine each children with the other children, using a fenwick tree or an ordered set. <br/>

# But the most important part was not the solution:
Mainly because after solving it I observed the solving process: my mind was trying to FORCE KNOWN THINGS TOO MUCH before REACHING THE SOLUTION, by doing that I was mainly doing **DIVERGENT THINKING**:
* First I was FORCING the Small to Large technique, but I didn't find a "good fit" combination of ideas there.
* Second I was FORCING some brute force with the subtrees, but again, I didn't find a "good fit" combination of ideas there.
* Third I thought "maybe it's HLD" but couldn't connect further ideas with that main idea.
* Finally, I remembered the Divide and Conquer video that I saw a lot of time ago, and the "beautiful thing" was that I DIDN'T NEED TO FORCE TOO MUCH to connect THIS IDEA with the problem, I just **tried to do SOMETHING WITH THE IDEAS THAT WERE ALREADY THERE, NO FORCING, JUST TESTING**, and IT WORKED.

So the **KEY IDEA** for this problem was to do MORE DIVERGENT THINKING (GENERATING PATTERNS) and TESTING IF THEY ARE A GOOD FIT (straight to the point, wihtout "forcing too much" an ACCOMODATION).
