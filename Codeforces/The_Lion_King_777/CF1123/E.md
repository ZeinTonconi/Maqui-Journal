# First approach:

My main approach was very direct, it was jotting down an example array 000111000111... and trying to observe patterns for each prefix 
that starts at i (so I can get n rows, each row has a prefix starting at i), and then I went through more observations (BUT ALSO THIS 
BECAME A LOT MORE COMPLEX to *HOLD ON MY WORKING MEMORY*) and then I observed cases when an element changes such as 010 101 001 110... 
This was going to work with a Segment Tree, but it was getting *TOO BIG/COMPLEX* to *KEEP TRACK OF*. <br/>

Yes, it was going to work but it was TOO HEAVY (for my MIND and for the CODE). By reading the editorial I understood that all those cases 
and ST could be *SIMPLIFIED* a lot by **SEEING FROM A DIFFERENT ANGLE** (**HIGH-LEVEL IDEA**): Instead of using the main observations and new *complex patterns*, 
etc. It uses an *XOR DIFFERENCE ARRAY*, this is because the *RANGE operations from the problem* can be *modeled as +1 MOD 2* which is the 
same as XOR. Then the problem transforms to making the diff.array ALL ZEROS. <br/>

By doing this *REPRESENTATIONAL CHANGE* of the problem, it transforms to *LOOKING FOR PATTERN IN THE DIF[L-1] AND DIF[R]* (which is **very 
common pattern also**, after the representational change to diff.array). The pattern was that it was possible to change 1 or 2 Ones from the 
diff.array, that is why the formula for the min. # of operations is ceil(count(1)/2). <br/>

OK, easy so far. Then by searching for what to do (shifting representations) one can manipulate the formula ceil(count(1)/2) with ALGEBRA (**HIGH-LEVEL IDEA**) and 
realize that if all numerators are even it's easy to just add all numerators and divide everything by 2 (**L2 LEVEL IDEA**).


## The core change from first approach to editorial's approach:

We shifted from working TOO HARD on VERY COMPLEX INFORMATION (COMPLEX PATTERNS, AND HOW THESE CONNECT WAS ALSO COMPLEX), to SIMPLER 
REPRESENTATIONS/CONNECTIONS, the key differences were:
* first approach I FELT THE NEED TO WRITE A LOT OF THINGS DOWN (*Working Memory overload* signal); editorial's approach I felt I didn't need to WRITE ANYTHING. This was obviously because of the *SEARCH OF SIMPLER REPRESENTATIONS IN LONG TERM MEMORY* so i.e. *searching to REDUCE TO THINGS I ALREADY KNOW*.
* first approach accumulates a lot of ISOLATED PARTS and THEN **CONNECT** THEM *ON PAPER*; editorial's approach felt like *EASY CONNECTING*.

## Main habit still very important to keep consistency:

There are going to be errors, that's for sure... But it should be also guaranteed by me that I DO NOT GET STUCK and *FORCE MEANINGFUL NAVIGATION* to shift between *REPRESENTATIONS* and reach **faster insights**. <br/>
L2 patterns and L3 algorithms are more concrete than L1 high level ideas... without classifying something into correct L1 idea(s), L2 and L3 *CANNOT EXIST* because they $\color{#CC2936}{\text{\bf *HANG FROM THE HIGH-LEVEL IDEA*}}$.
