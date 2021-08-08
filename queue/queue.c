#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    /* data */
    int value;
    struct node *next;
} node_t;

typedef struct queue
{
    node_t *head;
    node_t *tail;
} queue_t;

void add_node(queue_t *q, int val)
{
    node_t *n = malloc(sizeof(struct node));
    n->value = val;

    if (q->head == NULL)
    {
        q->head = n;
    }
    if (q->tail != NULL)
    {
        q->tail->next = n;
    }
    q->tail = n;
}

void print_queue(queue_t *q)
{
    node_t *n = q->head;
    while (n)
    {
        printf("%d -> ", n->value);
        n = n->next;
    }
    printf("END \n");
}

int dequeue(queue_t *q)
{
    if (!q->head)
    {
        return -1;
    }
    node_t *tmp;
    tmp = q->head;
    q->head = q->head->next;
    int val = tmp->value;
    // free(tmp);
    return val;
}

void main()
{
    queue_t q;
    memset(&q, 0, sizeof(q));

    printf("Dequeue: %d\n", dequeue(&q));

    for (int i = 0; i < 10; i++)
    {
        add_node(&q, i);
    }

    printf("q->head->val: %d\n", (&q)->head->value);
    printf("q->tail->val: %d\n", (&q)->tail->value);

    print_queue(&q);
    for (int j = 0; j < 15; j++)
    {
        printf("Dequeue: %d\n", dequeue(&q));
        // add_node(&q, j);
    }

    print_queue(&q);

    for (int j = 0; j < 15; j++)
    {
        // printf("Dequeue: %d\n", dequeue(&q));
        add_node(&q, j);
        if (j % 2 == 0)
        {
            printf("Dequeue: %d\n", dequeue(&q));
        }
    }

    print_queue(&q);

    exit(EXIT_SUCCESS);
}