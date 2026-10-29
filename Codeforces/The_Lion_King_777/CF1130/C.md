# Understanding the problem statement:

Sometimes the statement alone is not enough to understand what the problem is asking for, so one can try to understand it by 
*looking at the examples* or *looking at the "Notes" section* instead of re-reading the same parts. <br/>

# Thinking the solution:

I got the correct main idea for binary searching the answer, but I didn't prove my first try, so it failed on the final testcase of the 
examples, then I drew that specific example to see what was going on with it, and I realized that I could do a smaller k by cutting some 
unnecessary "bridge points". <br/>

OK, after this I thought that I could come up with a DP solution, and I did, but it took too long, but why?

# Why the second solution (but the first submission) took too long:

I think it was because of the *cognitive load theory*... <br/>

What do I mean by this? One can model the brain as a **Graph** where the nodes are the neurons and edges are the synapses between 
neurons... by connecting DIFFERENT neurons in DIFFERENT WAYS, one can invoke DIFFERENT representations/ideas/behaviors, etc. So 
one can view the brain as a plastic machine that can focus on a small set of ideas at the same time, and this set gives some 
RESPONSE to that set of stimuli (this "REDUCTION"/SYNTHESIS SYSTEM can be seen as the CORE PART of CONVERGENT THINKING). <br/>

So the actual *DEADLY PATTERN* that occurred here is that I was thinking in CYCLES... like *I was repeating myself too much*. <br/>

How did I overcome this? By *loading my working memory a little bit more/or with a different set of ideas*. <br/>

To give the example, I had a flash of an idea of "I can separate some black points by not using all "bridge" points, maybe" and then 
I saw at my example in the paper, and suddenly I came up with the correct k for that example, but I think it was because I SAW 
"THE EXAMPLE" AND "THE IDEA OF I CAN SEPARATE SOME BLACK POINTS BLA BLA..." TOGETHER (*at the same time*). <br/>

This made me remember of the definition of creativity: "It's the NOVEL combination of PAST IDEAS/EVENTS/CONCEPTS that reveal 
something USEFUL/TRUE", now by looking at this event I understand the IMPORTANCE OF CONVERGENT THINKING. <br/>

In the review of problem B (Latin America phase-Santa Cruz 2025) I also noticed this detail about convergent thinking: simply by 
SHIFTING MY VIEW TO OTHER PARTS OF THE STATE OF THE PROBLEM and NAVIGATING THROUGH THAT SPACE AND OWN IDEAS (this is divergent thinking) 
and THEN shifting my brain "MODE" to CONVERGENT THINKING by MIXING DIFFERENT PARTS OF THOSE *NAVIGATED* PARTS (**CHANGING *WHICH* PARTS 
TO CONNECT AND *HOW* TO CONNECT THEM**) IT WAS EASIER TO NOTICE that the N could be bounded. So this follows the model discussed 
earlier. <br/>

## The main lesson of convergent thinking:

By following the brain model discussed earlier and the events experienced that were told, one can conclude the following: <br/>

*If I look for an answer "outside" the information that I already have, and I don't get anywhere, probably the answer is in 
some NOVEL COMBINATION of the PIECES I ALREADY HAVE... Most of the times the answer is nearer than one thinks*.

## The second main lesson of thinking:

Following all said before, I can conclude the following: <br/>

*I SHOULD NEVER-EVER do CYCLIC THINKING, this is a deadly end and a waste of time! Instead, try to **combine ideas/pieces that are 
ALREADY HERE in DIFFERENT WAYS** if cannot come up with an insight or divergent thinking idea*.

## Another lesson (more specific to the problem):

In the following attempts after the first submission, I was trying to "prove all possibilities of the DP" and actually I came up 
with some fixes, and even BEFORE the AC I thought "maybe if I make the small change of setting the base case dp[0] 
to 2 instead of infinity it works, but I don't want to get another WA..." I DID NOT SUBMIT THAT SOLUTION UNTIL I FOUND A CASE 
WHERE IT PROVES THAT SUCH A CASE EXISTS, and it gave AC... so: <br/>

*Sometimes when one does not know what is wrong AND CAN'T COME UP WITH A PROOF QUICKLY, it's OK to GUESS what is wrong by 
PUTTING PATCHES in the code!* <br/>

## Another lesson:

*Even if the patches seem to be weak or small (e.g. the small change of dp[0]=2 in this problem), sometimes those small changes en up working!*

And this could've been an earlier AC.
