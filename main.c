//Akash

#include "header.h"

//used for dfs
int **visited;

int main(int argc, char *argv[])
{

    int width, height;
    char *maze;
    int x, y;
    int choice_M_Type, choice_S_Type;
    char *temp;
    int Valid_Maze = 1;

    printf("\t\t\t\t\t\t----MAZE__SOLVER----\n\n");
    printf("\nDone by-\n");
    printf("\nPES1UG22CS244 J Yogesh");
    printf("\nPES1UG22CS227 Gunda Sukesh");
    printf("\nPES1UG22CS226 Gunda Akash");
    printf("\nPES1UG22CS186 Dhruva R Prasad\n\n\n");

    printf("Maze Type :\n1.Generate Random\n2.Maze Input\n");
    printf("Enter your choice : ");
    scanf("%d", &choice_M_Type);

    if (choice_M_Type == 1)
    {

        printf("Enter the height and width :");
        scanf("%d %d", &x, &y);

        /* Get and validate the size. */
        width = y * 2 + 3;
        height = x * 2 + 3;
        if (width < 7 || height < 7)
        {
            printf("error: illegal maze size\n");
            exit(EXIT_FAILURE);
        }

        /* Allocate the maze array. */
        maze = (char *)malloc(width * height * sizeof(char));
        if (maze == NULL)
        {
            printf("error: not enough memory\n");
            exit(EXIT_FAILURE);
        }
        /* Generate and display the maze. */
        GenerateMaze(maze, width, height);
        printf("Maze Generated is : \n");
        ShowMaze(maze, width, height);
        printf("\n\n");
        // printMaze(maze,width,height);
        // printf("\n");
    }

    else if (choice_M_Type == 2)
    {
        printf("Enter the height and width :");
        scanf("%d %d", &x, &y);
        printf("%d %d\n", x, y);
        width = y;
        height = x;
        maze = (char *)malloc(x * y * sizeof(char));
        temp = (char *)malloc((2 * y + 1) * sizeof(char));
        printf("\nWarning : Enter the Maze in such a way that [] represent walls and '  ' represent space\n");
        printf("\nEnter your Maze :\n");
#ifdef __MINGW32__
        for (int i = 0; i < height; i++)
        {
            fflush(stdin);
            scanf("%[^\n]s", temp);
            for (int j = 0, k = 0; j < 2 * y - 1; j = j + 2)
            {
                if (temp[j] == 91 && temp[j + 1] == 93)
                {
                    maze[i * y + k] = 1;
                    k++;
                }
                else if (temp[j] == 32 && temp[j + 1] == 32)
                {
                    maze[i * y + k] = 0;
                    k++;
                }
                else
                {
                    maze[i * y + k] = -1;
                    k++;
                    Valid_Maze = 0;
                }
            }
        }
#elif __unix__
        for (int i = 0; i < height; i++)
        {
            __fpurge(stdin);
            scanf("%[^\n]s", temp);
            for (int j = 0, k = 0; j < 2 * y - 1; j = j + 2)
            {
                if (temp[j] == 91 && temp[j + 1] == 93)
                {
                    maze[i * y + k] = 1;
                    k++;
                }
                else if (temp[j] == 32 && temp[j + 1] == 32)
                {
                    maze[i * y + k] = 0;
                    k++;
                }
                else
                {
                    maze[i * y + k] = -1;
                    k++;
                    Valid_Maze = 0;
                }
            }
        }
#endif

        if (Valid_Maze == 0)
        {
            printf("Invalid Maze\n");
            printf("Exiting Maze Solver\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("the maze given is\n");
            ShowMaze(maze, width, height);
            printf("\n\n");
        }
    }

    else
    {
        printf("Invalid input\n");
        printf("Exiting Maze Solver\n");
        exit(EXIT_FAILURE);
    }

    printf("Maze solver options : \n");
    printf("1.DFS 2.BFS 3.A* 4.all 5.exit\n");
    printf("Enter the choice : ");
    scanf("%d", &choice_S_Type);

    switch (choice_S_Type)
    {
    case 1:
    {
        printf("Solving the Maze using DFS\n");
        visited = malloc(height * sizeof(int *));
        for (int i = 0; i < height; i++)
        {
            visited[i] = malloc(width * sizeof(int));
        }
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                visited[i][j] = 0;
            }
        }
        dfs(maze, 0, 1, height, width);
        ShowMaze(maze, width, height);
        for (int i = 0; i < height; i++)
        {
            free(visited[i]);
        }
        free(visited);
        break;
    }
    case 2:
    {
        printf("Solving the Maze using BFS\n");
        bfs(maze, width, height);
        ShowMaze(maze, width, height);
        break;
    }
    case 3:
    {
        printf("Solving the Maze using A*\n");
        //(int row, int col, char *maze, Point src, Point dest)
        Point src = {0, 1};
        Point dest = {height - 1, width - 2};
        aStar(height, width, maze, src, dest);
        ShowMaze(maze, width, height);
        break;
    }
    case 4:
    {
        char *maze_bfs = (char *)malloc(width * height * sizeof(char));
        char *maze_astar = (char *)malloc(width * height * sizeof(char));
        for (int i = 0; i < (width * height); i++)
        {
            maze_astar[i] = maze[i];
            maze_bfs[i] = maze[i];
        }

        // for dfs

        printf("Solving the Maze using DFS\n");
        visited = malloc(height * sizeof(int *));
        for (int i = 0; i < height; i++)
        {
            visited[i] = malloc(width * sizeof(int));
        }
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                visited[i][j] = 0;
            }
        }
        dfs(maze, 0, 1, height, width);
        ShowMaze(maze, width, height);
        printf("\n\n\n");
        for (int i = 0; i < height; i++)
        {
            free(visited[i]);
        }
        free(visited);

        // for bfs
        printf("Solving the Maze using BFS\n");
        bfs(maze_bfs, width, height);
        ShowMaze(maze, width, height);
        printf("\n\n\n");

        // for A*
        printf("Solving the Maze using A*\n");
        //(int row, int col, char *maze, Point src, Point dest)
        Point src = {0, 1};
        Point dest = {height - 1, width - 2};
        aStar(height, width, maze_astar, src, dest);
        ShowMaze(maze_astar, width, height);
        printf("\n\n\n");

        break;
    }
    default:
    {
        printf("exiting Maze Solver\n");
    }
    }

    // for seeing the maze content
    // printMaze(maze,width,height);

    /* Clean up. */
    free(maze);
    printf("EXITING MAZE SOLVER\n");
    exit(EXIT_SUCCESS);
}