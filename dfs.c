//Akash

#include "header.h"

extern int **visited;

int dfs(char *Maze, int row, int col, int end_row, int end_col)
{
    if (row == end_row - 1 && col == end_col - 2)
    {
        Maze[1] = 2;
        Maze[row * col + col - 2] = 2;
        return 1;
    }
    else if (row < 0 || row >= end_row || col < 0 || col >= end_col || visited[row][col] == 1 || Maze[row * end_col + col] == 1)
    {
        return 0;
    }
    else
    {
        visited[row][col] = 1;
        if (dfs(Maze, row + 1, col, end_row, end_col))
        {
            Maze[(row + 1) * end_col + col] = 2;
            return 1;
        }
        else if (dfs(Maze, row, col + 1, end_row, end_col))
        {
            Maze[(row)*end_col + col + 1] = 2;
            return 1;
        }
        else if (dfs(Maze, row - 1, col, end_row, end_col))
        {
            Maze[(row - 1) * end_col + col] = 2;
            return 1;
        }
        else if (dfs(Maze, row, col - 1, end_row, end_col))
        {
            Maze[(row)*end_col + col - 1] = 2;
            return 1;
        }
    }
    return 0;
}