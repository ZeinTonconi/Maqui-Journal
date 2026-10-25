# Interesting first idea:
I was thinking and I remembered the slope problem that I solved in Alcaldia's contest few years ago, and I remembered that I used the slopes 
to compare something, and I used the slopes as "unique IDs" in that problem. <br/>

So I actually used the "unique ID" idea for the slopes to do something *NEW* with that for THIS problem, which was to CLASSIFY VECTORS WITH 
THE SAME DIRECTIONS (WITH THE SLOPE, using GCD). <br/>

The interesting thing was that the sorting with the angles worked (using my function "angle" from geometry lib), BUT IN A LATER PROBLEM 
THIS DIDN'T WORK BECAUSE OF THE PRECISION ERRORS, EVEN WITH LONG DOUBLE (see problem E and my submissions from ABC481) so I used the 
approach that was told in the editorial of this problem (ABC442 E) that used CROSS PRODUCT INSTEAD OF "pure angles". To see the intuition 
of the case where this fails, I can build a case where the angles are "very close" from 2 different vectors but NOT the same, so there can 
be precision errors, I think this is the reason of why *in convex hull from cp algorithms they also use cross product instead of pure angles*. <br/>

# The "second" main lesson:
The second main lesson was that the polar sorting can be done using *upper and lower half-planes and cross product within those half-planes* instead 
of using "pure angles".
