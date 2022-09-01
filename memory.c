#include <stdio.h>
#include <stdlib.h>

int pm_size;
int memleft;
int algorithm;
struct node
{
    int id;
    int size;
    int start;
    int end;
    struct node *next;
} *head = NULL;
typedef struct node block;

void EnterParameters()
{

    printf("Enter size of physical memory: ");
    scanf("%d", &pm_size);
    printf("Enter hole-fitting algorithm(0=first fit, 1=best fit): ");
    scanf("%d", &algorithm);
    memleft = pm_size;
    head = (block *)malloc(sizeof(block));
    head->size = 0;
    head->start = 0;
    head->end = 0;
    head->next = NULL;
    return;
}
void PrintBlocks()
{
    block *n = head->next;

    printf("ID    Start    End \n------------------\n");
    while (n != NULL)
    {
        printf("%3d   ", n->id);
        printf("%5d    ", n->start);
        printf("%3d    \n", n->end);
        n = n->next;
    }
    printf("\n");
}

void Allocate()
{
    int best_hole = pm_size;
    int best_start;
    int best_end = pm_size;
    int holefound = 0;
    block *best_block = (block *)malloc(sizeof(block));

    int blockid;
    int blocksize;
    printf("Enter block id: ");
    scanf("%d", &blockid);
    printf("Enter block size: ");
    scanf("%d", &blocksize);
    if (blocksize > memleft)
    {
        printf("Could not fit block\n\n");
        return;
    }
    block *new = (block *)malloc(sizeof(block));
    new->id = blockid;
    if (head->next == NULL)
    {
        head->next = (block *)malloc(sizeof(block));
        head->next->id = blockid;
        head->next->start = 0;
        head->next->size = blocksize;
        head->next->end = blocksize;
        memleft -= blocksize;
        PrintBlocks();
        return;
    }
    block *n = (block *)malloc(sizeof(block));
    n = head;
    while (n != NULL)
    {
        if (n->id == blockid)
        {
            printf("ID already exists\n\n");
            return;
        }
        n = n->next;
    }
    n = head;
    int holestart;
    int holeend;
    while (n != NULL)
    {
        holestart = n->end;
        if (n->next == NULL)
            holeend = pm_size;
        else
            holeend = n->next->start;
        if ((holeend - holestart) >= blocksize)
        {
            if (algorithm == 0)
            {
                new->start = holestart;
                new->end = holestart + blocksize;
                new->next = n->next;
                new->size = blocksize;
                n->next = new;
                memleft -= blocksize;
                holefound = 1;
                PrintBlocks();
                return;
            }
            else if ((holeend - holestart) < best_hole)
            {
                best_start = holestart;
                best_end = holestart + blocksize;
                best_hole = holeend - holestart;
                best_block = n;
                holefound = 1;
            }
        }
        n = n->next;
    }
    if (algorithm == 1 && holefound == 1)
    {
        new->start = best_start;
        new->end = best_end;
        new->next = best_block->next;
        new->size = blocksize;
        best_block->next = new;
        memleft -= blocksize;
    }
    else if (holefound == 0)
    {
        printf("Could not fit block\n\n");
    }
    PrintBlocks();
    return;
}

void Deallocate()
{
    int id;
    block *n = head->next;
    block *previous = head;
    printf("Enter Block ID:");
    scanf("%d", &id);

    while (n != NULL && n->id != id)
    {
        previous = n;
        n = n->next;
    }
    if (n == NULL)
    {
        printf("Block ID Not Found\n\n");
        return;
    }
    else
    {
        previous->next = n->next;
        memleft += (n->size);
        free(n);
        PrintBlocks();
        return;
    }
}
void Defragment()
{
    block *n = head->next;
    int prev_end = 0;
    while (n != NULL)
    {
        n->start = prev_end;
        n->end = n->start + n->size;
        prev_end = n->end;
        n = n->next;
    }
    PrintBlocks();
    return;
}

int main()
{
    int choice = 8;
    while (choice != 5)
    {
        printf("Memory allocation\n-----------------\n1)Enter parameters\n2)Allocate memory for block\n3)Deallocate memory for block\n4)Defragment memory\n5)Quit program\n\nEnter Selection: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            EnterParameters();
            break;
        case 2:
            Allocate();
            break;
        case 3:
            Deallocate();
            break;
        case 4:
            Defragment();
            break;
        }
    }
    free(head);
    return 0;
}