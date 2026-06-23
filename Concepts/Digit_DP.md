Given Senarios and exp for Digit DP

1. Range would be given directly or indirectly [l, r].

2. Perform operation -> linke, count the digit 3 across all the number from l to r.

3. High contraints, like, 10^15, 10^20, etc.

4. final Ans = (ans till r) - (ans till l-1).

5. suppose l = 12462 and r = 46257 , so there are 5 digits, so for the 0th digit, the possible digit would be from 0 to 4, exceding 4 woul result into a number > r. Similary for other digit positions as well.

6. This way at each digit position, we have two group of numbers, for eg: in given r at 0th position max can be 4, so, 0 to 3 would be in group 1 and 2 would in group 2. If at 0th position we put digit of grp 1, in the further digit positions we can put any digits from 0 to 9. But if we had put grp 2, then we need to check if the digit is posible for upcoming positions. Same applies to the position further.

7. define dp[idx][tight or bound or flag][count or sum or somthing we want to calculate][other variables as per question]  ||  idx -> number of digits, tight -> size of 2.

8. tight = true -> restrictons, and vice-versa; once tight becomes false it would remain false for further indices. Therefore, initally filled true.