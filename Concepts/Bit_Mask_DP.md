Concept of BIT MASKING

Suppose we want to generate/ store all the elements of a subset, using as less space as possible. What would the most optimal approach.

Suppose is there are N elements in a Set. { Each element represented by its index(say)}.

Then we need N bits to represent the whole set as well as any subet.

A set-bit -> the element is presetn in the subset
else the element is not present.

so those combination of bits would translate into an integer that wouls represent the set;

say subset = {1, 2, 3, 4} and N = 10 {1, 2, ---- , 10}

Which integer would represent this set ? 
so basically we would set the 0th, 1st, 2nd, and the 3rd bits, that would result into interger 15.

If we want to add something into the set, -> set that corresonding bit -> ( 1 << i)^(val) (same for removing an element as well). [first check if the element is preset or not].
If we want to check if a number (i) is present in the set of not -> (1<< (i-1) & val).
