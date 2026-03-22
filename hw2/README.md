# LAB2: Divide and conquer
- In question B, there is a recursive relation with the form `Xn = a * Xn-1 + b * Xn-2 + c`. We need to calculate Xn and the accumulation of X1 to Xn with given n. However, n is greater than 1e9, so I have to use matrix multiplication with fast pow to speed up the process.
- In question C, they give us an array with intergers. After that, they will do two operation sequentially. One of them is change a number in that array, the other is ask 'how many primes is in that range'. I solved it with segment tree. 
- In question D, this is a variant of closest pair problem. In this question, there are points with indexs and a values. The two pairs that I need to find need not to be adjacent. I solve it with 2 methods: D-.cpp is brute force, which is not fast enought for this problem. And D.cpp is divide and conquer. D+.cpp and D++.cpp are also divide and conquer with some optimization.   
- In question E, we are just counting the inversion pairs. E-.cpp is brute force, while E.cpp is counting along the merge sort process.
- The rest of the file are just tools for me to debug.
