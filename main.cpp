//
// Created by Manju Muralidharan on 11/22/25.
//


//Jasper McIntyre
//5/5/26
//CS210

//DFS MAZE

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Directions for DFS (students must use these)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// ----------------------------------------------------------
// DO NOT MODIFY: Maze generation
// ----------------------------------------------------------
void generateMaze(vector<vector<int>>& maze, int N, int M) {
    srand(time(0));

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int roll = rand() % 100;
            maze[r][c] = (roll < 70) ? 0 : 1;   // 0 = open, 1 = wall
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Choose a random boundary cell that is open
// ----------------------------------------------------------
pair<int,int> chooseBoundaryCell(const vector<vector<int>>& maze) {
    int N = maze.size();
    int M = maze[0].size();

    while (true) {
        int side = rand() % 4;
        int r, c;

        if (side == 0) {          // top row
            r = 0;
            c = rand() % M;
        } else if (side == 1) {   // bottom row
            r = N - 1;
            c = rand() % M;
        } else if (side == 2) {   // left column
            r = rand() % N;
            c = 0;
        } else {                  // right column
            r = rand() % N;
            c = M - 1;
        }

        if (maze[r][c] == 0) {
            return {r, c};
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the maze with S and E markers
// ----------------------------------------------------------
void printMaze(const vector<vector<int>>& maze,
               int ent_r, int ent_c,
               int exit_r, int exit_c)
{
    int N = maze.size();
    int M = maze[0].size();


    cout << "\nMaze:\n";

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (r == ent_r && c == ent_c) {
                cout << "S ";
            } else if (r == exit_r && c == exit_c) {
                cout << "E ";
            } else {
                cout << maze[r][c] << " ";
            }
        }
        cout << "\n";
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the reconstructed path
// Students must fill parent[][] correctly during DFS
// ----------------------------------------------------------
void printPath(pair<int,int> exitcell,
               const vector<vector<int>>& parent_r,
               const vector<vector<int>>& parent_c,
               int ent_r, int ent_c)
{
    int r = exitcell.first;
    int c = exitcell.second;

    vector<pair<int,int>> path;

    // Walk backward from exit to entrance
    while (!(r == ent_r && c == ent_c)) {
        path.push_back({r, c});
        int pr = parent_r[r][c];
        int pc = parent_c[r][c];
        r = pr;
        c = pc;
    }
    path.push_back({ent_r, ent_c});

    cout << "\nPath from entrance to exit:\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << "(" << path[i].first << ", " << path[i].second << ")\n";
    }
}

// ----------------------------------------------------------
// STUDENTS IMPLEMENT DFS HERE
// Add arguments, return type, and logic
// ----------------------------------------------------------
// bool dfs(……) {
//     // Your code here
// }
bool dfs(int r, int c,
    const vector<vector<int>>& maze,
    vector<vector<bool>>& visited,
    vector<vector<int>>& parent_r,
    vector<vector<int>>& parent_c,
    int exit_r, int exit_c){
        int N = maze.size();
        int M = maze[0].size();
        //check if not a wall or out of bounds or visited
        if(r < 0 || r >= N || c < 0 || c >= M || maze[r][c] == 1 || visited[r][c]){
            return false;
        }
        //visited current
        visited[r][c] = true;

        //Recursive base case: check for exit
        if(r == exit_r && c == exit_c){
            return true;
        }
        //check every direction (0 = up, 1 = right, 2 = down, 3 = left
        for(int i = 0; i < 4; i++){
            //add direction offset from dr and dc to r and c
            int rNew = r + dr[i];
            int cNew = c + dc[i];

            //set parent neighbor to current if not a wall out of bounds or visited before recursing 
            if(rNew >=0 && cNew >= 0 && rNew < N && cNew < M && maze[rNew][cNew] == 0){
                parent_r[rNew][cNew] = r;
                parent_c[rNew][cNew] = c;
                //return true if recursive call returns true
                if(dfs(rNew, cNew, maze, visited, parent_r, parent_c, exit_r, exit_c)){
                    return true;
                }
            }
        }
        //return false if no path is found
        return false;


    }
    
// ----------------------------------------------------------
// MAIN PROGRAM (students add DFS calls and logic)
// ----------------------------------------------------------
int main() {
    int N, M;
    cout << "  ==Jasper M DFS Maze==\n";
    cout << "Enter maze dimensions N M: ";
    cin >> N >> M;


    vector<vector<int>> maze(N, vector<int>(M));
    generateMaze(maze, N, M);

    // Pick entrance and exit
    pair<int,int> entrance = chooseBoundaryCell(maze);
    pair<int,int> exitcell = chooseBoundaryCell(maze);

    while (exitcell == entrance) {
        exitcell = chooseBoundaryCell(maze);
    }

    int ent_r = entrance.first;
    int ent_c = entrance.second;
    int exit_r = exitcell.first;
    int exit_c = exitcell.second;

    // Display the maze
    printMaze(maze, ent_r, ent_c, exit_r, exit_c);

    // Students must use these
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> parent_r(N, vector<int>(M, -1));
    vector<vector<int>> parent_c(N, vector<int>(M, -1));

    // ------------------------------------------------------
    // STUDENT WORK:
    // Call your DFS, track visited, and fill parent_r and parent_c
    // ------------------------------------------------------
     bool found = dfs(ent_r, ent_c, maze, visited, parent_r, parent_c, exit_r, exit_c);

    // ------------------------------------------------------
    // STUDENT WORK:
    // If found, print the path
    // ------------------------------------------------------
    //
     if (found) {
         printPath(exitcell, parent_r, parent_c, ent_r, ent_c);
     } else {
         cout << "\nNo path exists.\n";
     }
//return 0 if run without errors
    return 0;
}
