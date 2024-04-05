// Sukesh

#include "header.h"

void enqueue(Queue *q, Point p)
{
    q->data[q->rear++] = p;
}

Point dequeue(Queue *q)
{
    return q->data[q->front++];
}

int isEmpty(Queue *q)
{
    return q->front == q->rear;
}

int isValid(int row, int col, int maxRow, int maxCol)
{
    return (row >= 0 && row < maxRow && col >= 0 && col < maxCol);
}

void markPath(char *maze, Point **path, int row, int col)
{
    int r = row - 1;
    int c = col - 2;

    while (!(r == 0 && c == 1))
    {
        maze[r * col + c] = 2;
        Point prev = path[r][c];
        r = prev.row;
        c = prev.col;
    }

    maze[1] = 2; // Mark starting point
}

void bfs(char *maze, int row, int col)
{
    Queue q;
    q.front = 0;
    q.rear = 0;

    Point **path;
    path = malloc(row * sizeof(Point *));
    for (int i = 0; i < row; i++)
    {
        path[i] = malloc(col * sizeof(Point));
    }
    // Point path[row][col];

    int visited[row][col];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            visited[i][j] = 0;
        }
    }

    Point start = {0, 1};
    enqueue(&q, start);
    visited[start.row][start.col] = 1;

    int dr[] = {-1, 1, 0, 0}; // Possible moves: up, down, left, right
    int dc[] = {0, 0, -1, 1};

    while (!isEmpty(&q))
    {
        Point current = dequeue(&q);
        if (current.row == row - 1 && current.col == col - 2)
        {
            break;
        }
        for (int i = 0; i < 4; ++i)
        {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (isValid(newRow, newCol, row, col) && maze[newRow * col + newCol] == 0 && !visited[newRow][newCol])
            {
                Point next = {newRow, newCol};
                enqueue(&q, next);
                visited[newRow][newCol] = 1;
                path[newRow][newCol] = current;
            }
        }
    }

    markPath(maze, path, row, col);
    for (int i = 0; i < row; i++)
    {
        free(path[i]);
    }
    free(path);
}