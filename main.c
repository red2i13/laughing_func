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
    Node *tmp = queue;
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

    if(y + 1 < COL && grid[x][y + 1] != 1)
        insert(queue, x, y+1);
    else if(y - 1 > 0 && grid[x][y - 1] != 1)
        insert(queue, x, y+1);
    else if(x+1 < COL && grid[x+1][y] != 1)
        insert(queue, x + 1, y);
    else if(x - 1 > 0&& grid[x - 1][y] != 1)
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
        if (!search(current, *visited))
        {
            neighbors_search(queue, visited,grid, x, y);
        }
        printf("grid[%i][%i] = %i\n", current->x, current->y, grid[current->x][current->y]);
        grid[current->x][current->y] = 7;
        pop(queue, current->x, current->y);
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
    bfs(grid, 1, 3);
    print_grid(grid);

}