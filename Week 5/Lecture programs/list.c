#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    //int list[3];
    /*int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    };


    list[0] = 1;
    list[1] = 2;
    list[2] = 3;*/

    //int *tmp = malloc(4 * sizeof(int));
    /*int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    };*/

    /*for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    };*/

    /*list = tmp;

    list[3] = 4;

    //free(list);

    //list = tmp;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    };

    free(list);*/

    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // don't forget to free memory here
            return 1;
        };
        //*n.number = number;
        n->number = number;
        n->next = NULL;

        n->next = list;
        list = n;
    };

    node *ptr = list;
    while (ptr != NULL)
    //for (node *ptr = list; ptr!= NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    };

    ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    };
};