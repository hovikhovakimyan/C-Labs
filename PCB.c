#include <stdio.h>
#include <stdlib.h>

/* Define structures and global variables*/
typedef struct{
    int parent;
    int first_child;
    int older_sibling;
    int younger_sibling;
}node;
node* PCB;
int max;
int totalprocesses;




void enterParameters() {

    printf("Please enter maximum number of processes: ");
    scanf("%d",&max);
    PCB=malloc(max*sizeof(*PCB));
    PCB[0].parent = 0;
    PCB[0].first_child = -1;
    PCB[0].younger_sibling=-1;
    PCB[0].older_sibling=-1;
    totalprocesses++;
    for(int i=1;i<max;i++){
        PCB[i].parent=-1;
        PCB[i].first_child=-1;
        PCB[i].younger_sibling=-1;
        PCB[i].older_sibling=-1;
    }
    return;
}


void printTable() {

    int i=0;
    puts("i  Parent  First  Older  Younger");
    puts("---------------------------------");
    for(int i=0;i<max;i++){
        if(PCB[i].parent!=-1){
            printf("%d  ",i);
            if(PCB[i].parent!=-1){
                printf("%d ",PCB[i].parent);
            }
            else{
                printf("  ");
            }
            printf("      ");
            if(PCB[i].first_child!=-1){
                printf("%d ",PCB[i].first_child);
            }
            else{
                printf("  ");
            }
            printf("     ");
            if(PCB[i].older_sibling!=-1){
                printf("%d ",PCB[i].older_sibling);
            }
            else{
                printf("  ");
            }
            printf("     ");
            if(PCB[i].younger_sibling!=-1){
                printf("%d ",PCB[i].younger_sibling);
            }
            else{
                printf("  ");
            }
            printf("\n");
        }

    }
    return;
}

void createProcess() {
    if(totalprocesses==max){
        printf("\nMaximum number of processes has been reached\n");
        return;
    }
    int p;
    int q=1;
    int children;
    printf("Enter the parent process index: ");
    scanf("%d",&p);
    if(p>max-1){
         printf("\nInvalid input: Parent Process Number chosen is higher than maximum allowed\n");
         return;
    }
    if(PCB[p].parent==-1){
        printf("\nInvalid input: Parent process %d doesnt exist\n",p);
        return;
    }
    while(PCB[q].parent!=-1){
        q++;
    }
    PCB[q].parent=p;
    if(PCB[p].first_child==-1){
        PCB[p].first_child=q;
        children=1;
    }else{
        children=2;
        int next_child = PCB[p].first_child;
        while(PCB[next_child].younger_sibling!=-1){
            next_child = PCB[next_child].younger_sibling;
        }
        PCB[q].older_sibling=next_child;
        PCB[next_child].younger_sibling=q;
    }
    printf("cr[%d] :\tcreates %dth child oof process %d at %d\n",p,children,p,q);
    totalprocesses++;
    printTable();
    return;
}
void recursiveDestroy(int q) {
    if(q==-1){
        return;
    }
    else{
        recursiveDestroy(PCB[q].younger_sibling);
        recursiveDestroy(PCB[q].first_child);
        PCB[q].parent=-1;
        PCB[q].first_child=-1;
        PCB[q].younger_sibling=-1;
        PCB[q].older_sibling=-1;
        totalprocesses--;
        printf("PCB[%d]\t",q);
    }
  return;
}

void destroyProcesses(int p) {
    printf("de[%d]:\tdestroys all the descendants of PCB[%d] which includes: \n",p,p);
    recursiveDestroy(PCB[p].first_child);
    printf("\n");
    PCB[p].first_child=-1;
    printTable();
  return;
}


void garbageCollection() {
    if(PCB!=NULL){
        free(PCB);
    }

    return;
}
int main() {
    int choice=0;
    int destructionchoice;
    while(choice!=4){
        printf("\nProcess creation and destruction\n--------------------------------\n1)Enter Parameters\n2)Create a new child process\n3)Destroy all descendants of a process\n4)Quit program and free memory\n");
        printf("\nPlease enter selection: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                enterParameters();
                break;
            case 2:
                createProcess();
                break;
            case 3:
                printf("Enter the process whose descendants are to be destroyed: ");
                scanf("%d",&destructionchoice);
                if(destructionchoice>max-1){
                    printf("\nInvalid input: Process Number chosen is higher than maximum allowed\n");
                    break;
                }
                if(PCB[destructionchoice].parent==-1){
                    printf("\nInvalid input: Process %d doesnt exist\n",destructionchoice);
                    break;
                    }
                destroyProcesses(destructionchoice);
                break; 
        }
    }
    garbageCollection();
    return 1;
}
