// Yogesh

#include "header.h"

// Function to check if a given point is valid (within the maze and not a wall)
bool isValid_Astar(int row, int col, char *maze, Point p)
{
    return (p.row >= 0) && (p.row < row) && (p.col >= 0) && (p.col < col) && (maze[p.row * col + p.col] == 0);
}

// Function to check if a given point is the destination
bool isDestination(Point p, Point dest)
{
    return p.row == dest.row && p.col == dest.col;
}

// Function to calculate the heuristic (H) value using the Manhattan distance
int calculateHValue(Point p, Point dest)
{
    return abs(p.row - dest.row) + abs(p.col - dest.col);
}

// Function to trace the path from the destination to the source and mark the path in the maze
void tracePath(Node **nodeDetails, int row, int col, Point dest, char *maze)
{
    printf("Path found!\n");
    int x = dest.row, y = dest.col;
    while (!(x == 0 && y == 1))
    {
        maze[x * col + y] = 2; // Marking the path as 2

        // printf("(%d, %d) <- ", x, y);

        int newX = nodeDetails[x][y].parent.row;
        int newY = nodeDetails[x][y].parent.col;
        x = newX;
        y = newY;
    }
    maze[1] = 2;
    printf("\n");
}

// A* algorithm to find the path in the maze
void aStar(int row, int col, char *maze, Point src, Point dest)
{
    // Arrays to store details of each cell/node
    Node **nodeDetails = (Node **)malloc(row * sizeof(Node *));
    for (int i = 0; i < row; ++i)
    {
        nodeDetails[i] = (Node *)malloc(col * sizeof(Node));
    }

    // Initialization
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            nodeDetails[i][j].f = nodeDetails[i][j].g = nodeDetails[i][j].h = INT_MAX;
            nodeDetails[i][j].parent.row = nodeDetails[i][j].parent.col = -1;
        }
    }

    // Initial node details for source
    int i = src.row, j = src.col;
    nodeDetails[i][j].f = nodeDetails[i][j].g = nodeDetails[i][j].h = 0;
    nodeDetails[i][j].parent.row = i;
    nodeDetails[i][j].parent.col = j;

    // Open list to keep track of nodes to be evaluated
    bool openList[row][col];
    memset(openList, false, sizeof(openList));
    openList[i][j] = true;

    // Perform A* algorithm
    while (true)
    {
        int minF = INT_MAX;
        Point current;

        // Find the node with the lowest f value in the open list
        for (int x = 0; x < row; ++x)
        {
            for (int y = 0; y < col; ++y)
            {
                if (openList[x][y] && nodeDetails[x][y].f < minF)
                {
                    minF = nodeDetails[x][y].f;
                    current.row = x;
                    current.col = y;
                }
            }
        }

        // No path found
        if (minF == INT_MAX)
        {
            printf("No path found\n");
            return;
        }

        // Remove the current node from the open list
        openList[current.row][current.col] = false;

        // Generate the successors of the current node
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int dir = 0; dir < 4; ++dir)
        {
            Point neighbor = {current.row + dx[dir], current.col + dy[dir]};

            // Check if the neighbor is valid
            if (isValid_Astar(row, col, maze, neighbor))
            {
                int newG = nodeDetails[current.row][current.col].g + 1;

                // Check if a better path is found
                if (newG < nodeDetails[neighbor.row][neighbor.col].g)
                {
                    // Update the details of the neighbor
                    nodeDetails[neighbor.row][neighbor.col].g = newG;
                    nodeDetails[neighbor.row][neighbor.col].h = calculateHValue(neighbor, dest);
                    nodeDetails[neighbor.row][neighbor.col].f = newG + nodeDetails[neighbor.row][neighbor.col].h;
                    nodeDetails[neighbor.row][neighbor.col].parent = current;

                    // Add the neighbor to the open list if not already present
                    if (!openList[neighbor.row][neighbor.col])
                    {
                        openList[neighbor.row][neighbor.col] = true;
                    }
                }
            }
        }

        // Check if the destination is reached
        if (isDestination(current, dest))
        {
            tracePath(nodeDetails, row, col, dest, maze);
            break;
        }
    }

    // Free allocated memory
    for (int i = 0; i < row; ++i)
    {
        free(nodeDetails[i]);
    }
    free(nodeDetails);
}