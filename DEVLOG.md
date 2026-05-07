Jasper McIntyre
5/6/26

DFS MAZE DEVLOG

Entry 1: Out of bounds
Issue encountered: Program crashes with out range error after trying to search
Error symptom: memory error before maze finishes printing
Attempts: Realized that maze[r][c] was being checked before r and c bounds are checked\
Final Resolution: Reordered if statements in dfs so it checks that r and c are < 0 and >= N and M

Entry 2: missing return statement
Issue encountered: DFS finds exit but No path exists gets printed
Error symptom: Added a exit found test that worked but main still takes in false
Attempts: I was calling (rNew, cNew) inside the loop but not returning anything
Final Resolution: fixed loop logic to return true if exit is found

Entry 3: Visited Array Logic error
Issue encountered: The path was going through walls
Error symptom: Output path included points that were a 1
Attempts:I was marking cells visited too late
Final Resolution: added visited[r][c] and maze [r][c] to the base case

Entry 4: infinite recursion
Issue encountered: The program freezes and doesn't run
Error symptom: Using a 5x5 maze wors but a large one like 25x25 maze crashes
Attempts: I forgot to set visited[r][c] = true
Final Resolution: added the visited mark after the wall check to make sure the correct path is marked

Entry 5: Incorrect parent tracking
Issue encountered: printPath wouldn't output correctly
Error symptom: The path be completely random and not connected
Attempts: I was updating the current cel parent as the neighbor which is the opposite of whats required for input
Final Resolution: Switched the statement to set the neighbors parent to the current cell parent_r[rNew][cNew] = r and parent_c[rNew][cNew] = c before recursive call

Entry 6: redundant check in loop
Issue encountered: logic error in direction for loop stopped next neighbor from being checked
Error symptom: compiler flagged incomplete if statement and logic was skipping valid neighbor cells
Attempts: Tried to use base case at the top of dfs to catch out of bounds neighbors but i realized i needed a new check before parent assignment
Final Resolution: added a new check for rNew >=0 && rNew < N && cNew >=0 && cNew < M in the for loop to make sure parent_r and parent_c are updated if index is valid
