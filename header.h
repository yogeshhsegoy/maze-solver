#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>
#ifdef __unix__
   #include<stdio_ext.h>
#endif

#define MAX_ROW 30
#define MAX_COL 30

//for storing row,column
typedef struct {
    int row;
    int col;
} Point;

//for bfs(queue) and A*(priority queue)
typedef struct {
    Point data[MAX_ROW * MAX_COL];
    int front, rear;
} Queue;
//for A* to store the cash for each cell and store the parent to retrace or mark the path
typedef struct {
    Point parent;
    Point current;
    int f, g, h;
} Node;




//Dhruva
void ShowMaze(const char *maze, int width, int height);
void CarveMaze(char *maze, int width, int height, int x, int y);
void GenerateMaze(char *maze, int width, int height);
void printMaze(const char *maze, int width, int height);


//Akash
int dfs(char *Maze ,int row,int col,int end_row,int end_col);


//Sukesh
void enqueue(Queue *q, Point p);
Point dequeue(Queue *q);
int isEmpty(Queue *q);
int isValid(int row, int col, int maxRow, int maxCol) ;
void markPath(char * maze, Point **path, int row, int col);
void bfs(char *maze, int row, int col);


//Yogesh
bool isValid_Astar(int row, int col, char *maze, Point p);
bool isDestination(Point p, Point dest);
int calculateHValue(Point p, Point dest);
void tracePath(Node** nodeDetails, int row, int col, Point dest, char* maze);
void aStar(int row, int col, char *maze, Point src, Point dest);

