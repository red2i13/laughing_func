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
int dequeue(node **queue, node *cur)
{
    node *tmp = (*queue);
    while (tmp)
    {
        if (tmp == (*queue))
        {
            tmp->next->parent = NULL;
            (*queue) = (*queue)->next;
            free(tmp);
            return(0);
        }
        tmp = tmp->next
    }
    return(1);
    
}
int bfs(int st_x, int st_y)
{
    int arr[row][col]; 
    memset(arr, 0, sizeof(arr));
    print_vis(arr);
    node *queue;
    queue = NULL;
    print_list(queue);
    enqueue(&queue, st_x, st_y);
    print_list(queue);
    printf("---------------------\n");
    enqueue(&queue, 5, 6);
    print_list(queue);

    exit(5);
    return(EXIT_SUCCESS);

}

int main()
{
    bfs(3, 5);
     int a [7][7] = {
        {0,1,1,0,0,0,0},
        {1,0,0,1,0,0,0},
        {1,0,0,1,1,0,0},
        {0,1,1,0,0,0,0},
        {0,0,1,0,0,1,1},
        {0,0,0,0,1,0,1}, 
        {0,0,0,0,1,1,0} 
    };
}