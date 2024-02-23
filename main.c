#include <stdlib.h>
#include <stdio.h>

#define ROW 9
#define COL 10
typedef struct Node {
    int x, y; 

    struct Node* parent;
    struct Node* next;
    int content;
    int visited;
 
} Node;
Node* createNode(int x, int y, Node* parent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    //printf("create NOde %i %i\n", x, y);
    newNode->x = x;
    newNode->y = y;
    newNode->parent = parent;
    return newNode;
}
void print_grid(int grid[ROW][COL])
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            printf("%i ", grid[i][j]);
        }
        printf("\n");
    }
}
int insert(Node **list, int x, int y)
{
    Node *newnode = createNode(x, y, NULL);

    newnode->parent = *list;
    *list = newnode;
    return(EXIT_SUCCESS);
}
int search(Node *queue, Node *visited)
{
    //Node *tmp = queue;
    Node *tmp1 = visited;

    while (tmp1)
    {
        if(tmp1->x == queue->x && tmp1->y == queue->y)
            return(1);
        tmp1 = tmp1->parent; 
    }
    return(0);
}
int neighbors_search(Node **queue, Node **visited, int grid[ROW][COL],int x, int y)
{
    int i;
    Node *current = (*queue);
    printf("neihbors x = %i y = %i\n", x, y);
    if(y + 1 < COL && grid[y+1][x] != 1)
    {
        insert(queue, x, y+1);
        //printf("inserted %i %i\n", x, y+1);
    }
    else if(y - 1 > 0 && grid[y-1][x] != 1)
        insert(queue, x, y-1);
    else if(x+1 < COL && grid[y][x+1] != 1)
        insert(queue, x + 1, y);
    else if(x - 1 > 0&& grid[y][x-1] != 1)
        insert(queue, x - 1, y);
    return(EXIT_SUCCESS);
}
int pop(Node **queue, int x, int y)
{
    Node *current = *queue;
    while (current)
    {
        if(current->x == x && current->y == y)
        {
            current->parent = NULL;
            free(current);
            return(1);
        }
        current = current->parent;
    }
    return(0);
    
}
int bfs(int grid[ROW][COL], int x, int y)
{
    Node **queue  = malloc(sizeof(Node *));
    Node **visited = malloc(sizeof(Node *));

    (*queue) = createNode(x, y, NULL);
    Node *current = (*queue);
    while (current)
    {
        //printf("SEG FAULTT  TTTTTT\n");
        if (!search(current, *visited))
        {
            printf("grid[%i][%i] = \n", current->y, current->x);
            printf("%i\n", grid[current->y][current->x]);
            grid[current->y][current->x] = 7;
            neighbors_search(queue, visited,grid, current->x, current->y);
            insert(visited, current->x, current->y);
            pop(queue, current->x, current->y);
        }
        //printf("after grid[%i][%i] = %i\n", current->x, current->y, grid[current->y][current->x]);
        current = *queue;
    }
    return(EXIT_SUCCESS);
}

int main()
{
    int grid[ROW][COL]
        = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 1, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 1 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
    print_grid(grid);
    bfs(grid, 3, 1);
    print_grid(grid);
    return(EXIT_SUCCESS);
}