a.out : main.o GenerateMaze.o dfs.o bfs.o Astar.o
	gcc main.o GenerateMaze.o dfs.o bfs.o Astar.o
main.o : main.c header.h
	gcc -c main.c
GenerateMaze.o : GenerateMaze.c header.h
	gcc -c GenerateMaze.c
dfs.o : dfs.c header.h
	gcc -c dfs.c
bfs.o : bfs.c header.h
	gcc -c bfs.c
Astar.o : Astar.c header.h 
	gcc -c Astar.c