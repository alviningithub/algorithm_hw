# Lab4: Dynamic Programming and Greedy
- In problem A, I need to solve longest common subsequence. Because the sequences are too long (1e7), I need to scroll the array.
- In problem B, we need to schedule different task. Each task require different time to finish. We can only do one task at a time. The cost is the time from start to the task is begin to handle. I use greedy to solve this problem. 
- Problem C is strongly connected component. It can be solve by dfs one time, record the finish time, and dfs again on the reverse graph.
- In problem D, there are two people and a sequence of number. They take turns to pick a number from the beginning or the end of the sequence and sum it up. They want the sum of their number is greater then each other, and maximum the difference. This question can be solve by dynamic programming.
- Problem E is a a knapsnak problem. Each item is limited. I have to group items into size of 2^n.
- Problem F is a dynamic programming problem. In this problem, I use segement tree to search a largest value in a specific range, and use that value to update the current value.
- Problem G want us to find the number of ways to place any numbers of kings such that no king is on an obstacle. The chestboard is n*n, where n can be up to 24. I have no idea how to solve it efficiently, so I only try two method and then give up.
  