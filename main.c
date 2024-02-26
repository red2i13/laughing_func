#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define row 5
#define col 5

typedef struct node{
    struct node *next;
    struct node *parent;
    int x;
    int y;
}node;

void print_vis(int arr[row][col])
{
    for(int i = 0; row >i; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%i ", arr[i][j]);
        }
        printf("\n");
    }
}
void print_list(node *lst)
{
    node  *tmp;
    tmp = lst;
    int i = 1;
    
    if(!lst)
        printf("THE LIST IS EMPTY\n");
    while (tmp)
    {
        printf("Node N:%i tmp->x = %i , tmp->y = %i\n", i++, tmp->x, tmp->y);
        tmp = tmp->next;
    }
    printf("--------------------------------------------------\n");
    
}
int enqueue(node **queue, int x, int y)
{
    node *new_node = malloc(sizeof(node));
    if(!new_node)
        return(1);
    new_node->x = x;
    new_node->y = y;

    if ((*queue) == NULL)
    {
        printf("DEBUUUUUUUUG\n");
        (*queue) = new_node;
        (*queue)->parent = (*queue)->next = 0;

    }
    else if ((*queue)->parent == NULL)
    {
        new_node->next = 0;
        new_node->parent = (*queue);
        (*queue)->next = new_node;
    }
    else
    {
        new_node->next = (*queue)->next;
        new_node->parent = (*queue);
        (*queue)->next = new_node;
    }
    return(EXIT_SUCCESS);
}
//function to revisit
// int dequeue(node **queue, node *cur)
// {
//     node *tmp = (*queue);
//     if(!tmp)
//         return(1);
//     while (tmp)
//     {
//         if (tmp == (*queue))
//         {
//             tmp->next->parent = NULL;
//             (*queue) = (*queue)->next;
//             free(tmp);
//             return(0);
//         }
//         tmp = tmp->next;
//     }
//     return(1);
    
// }
//chat function to test
void dequeue(node **list, node *current) {
    if (!list || !*list || !current) {
        // Handle error cases: empty list, NULL list pointer, or NULL current node
        return;
    }

    // Handle removing the head node
    if (*list == current) {
        *list = (*list)->next; // Update head pointer
    } else {
        // Find the previous node of the current node
        node *previous = *list;
        while (previous->next != current && previous->next != NULL) {
            previous = previous->next;
        }

        // Check if current node was found in the list
        if (previous->next == current) {
            previous->next = current->next; // Link previous node to the next node
        } else {
            // Current node not found in the list (may be a dangling pointer)
            return;
        }
    }

    // Free the memory of the removed node
    free(current);
}
int neighbors(node **queue, node *cur,int grid[7][7], int vis[row][col])
{
    int x = cur->x;
    int y = cur->y;
    if(x + 1 < row && grid[x + 1][y] != 1 && vis[x + 1][y] == 0)
    {
        enqueue(queue, x + 1, y);
    }
    if(x - 1 >= 0 && grid[x - 1][y] != 1 && vis[x - 1][y] == 0)
    {
        enqueue(queue, x + 1, y);
    }
    if(y + 1 < col && grid[x][y + 1] && vis[x][y + 1] == 0)
    {
        enqueue(queue, x, y + 1);
    }
    if(y - 1 >= 0 && grid[x][y - 1] && vis[x][y - 1] == 0)
    {
        enqueue(queue, x, y - 1);
    }
    return(EXIT_SUCCESS);
    
}
int bfs(int grid[7][7] ,int st_x, int st_y)
{
    int arr[row][col]; 
    memset(arr, 0, sizeof(arr));
    print_vis(arr);
    node *queue;
    queue = NULL;
    enqueue(&queue, st_x, st_y);
    print_list(queue);
   //node *tmp = queue;
    while(queue)
    {
        arr[queue->x][queue->y] = 1;
        neighbors(&queue, queue, grid, arr);
        dequeue(&queue, queue);
        print_list(queue);
        
    }
    // print_list(queue);
    // printf("---------------------\n");
    // enqueue(&queue, 5, 6);
    // dequeue(&queue, queue);
    // print_list(queue);
    print_vis(arr);

    exit(5);
    return(EXIT_SUCCESS);
}

int main()
{
    int a[7][7] = {
        {0,1,1,0,0,0,0},
        {1,0,0,1,0,0,0},
        {1,0,0,1,1,0,0},
        {0,1,1,0,0,0,0},
        {0,0,1,0,0,1,1},
        {0,0,0,0,1,0,1}, 
        {0,0,0,0,1,1,0} 
    };
    bfs(a,3, 5);
}