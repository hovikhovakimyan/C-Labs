#include <stdio.h>
#include <stdlib.h>

int m;
int n;
int* resources;
int* available;
int** allocated;
int** max;
int** need;

void PrintResources() {

    printf("Resources: \n\t");
    for(int i=0;i<n;i++){
        printf("%4d",resources[i]);
    }
    printf("\n");
	return;
}


void PrintAvailable() {

    printf("Available: \n\t");
    for(int i=0;i<n;i++){
    printf("%3s%d","r",i);
    }
    printf("\n  \t");
    for(int i=0;i<n;i++){
        printf("%4d",available[i]);
    }
    printf("\n");
	return;
}

void PrintMax() { 

    printf("Max claim:\n  \t");
    for(int i=0;i<n;i++){
    printf("%3s%d","r",i);
    }
    printf("\n");

    for(int i=0;i<m;i++){
    printf("p%d\t",i);
        for(int j=0;j<n;j++){
        printf("%4d",max[i][j]);
        }
    printf("\n");
    }
	return;
}


void PrintAllocated() {

    printf("Allocated:\n  \t");
    for(int i=0;i<n;i++){
    printf("%3s%d","r",i);
    }
    printf("\n");

    for(int i=0;i<m;i++){
    printf("p%d\t",i);
        for(int j=0;j<n;j++){
        printf("%4d",allocated[i][j]);
        }
    printf("\n");
    }
	return;
}

void PrintNeed() {
    printf("Need:\n  \t");
    for(int i=0;i<n;i++){
    printf("%3s%d","r",i);
    }
    printf("\n");

    for(int i=0;i<m;i++){
    printf("p%d\t",i);
        for(int j=0;j<n;j++){
        printf("%4d",need[i][j]);
        }
    printf("\n");
    }
	return;
}
void EnterParameters() {
    printf("Enter number of processes(max 5): ");
    scanf("%d",&m);
    printf("Enter number of resources(max 5): ");
    scanf("%d",&n);
    resources=malloc(n*sizeof(int));
    available=malloc(n*sizeof(int));
    max=malloc(m*sizeof(int*));
    need=malloc(m*sizeof(int*));
    allocated=malloc(m*sizeof(int*));
    for(int i=0;i<m;i++){
        max[i]=malloc(n*sizeof(int));
        need[i]=malloc(n*sizeof(int));
        allocated[i]=malloc(n*sizeof(int));
    }
    switch(n){
        case 1:
            printf("Enter resource value for r0: ");
            scanf("%d",&resources[0]);
            break;
        case 2:
            printf("Enter resource value for r0 and r1: ");
            scanf("%d %d",&resources[0],&resources[1]);
            break;
        case 3:
            printf("Enter resource value for r0-r2: ");
            scanf("%d %d %d",&resources[0],&resources[1],&resources[2]);
            break;
        case 4:
            printf("Enter resource value for r0-r3: ");
            scanf("%d %d %d %d",&resources[0],&resources[1],&resources[2],&resources[3]);
            break;
        case 5:
            printf("Enter resource value for r0-r4: ");
            scanf("%d %d %d %d %d",&resources[0],&resources[1],&resources[2],&resources[3],&resources[4]);
            break;
    }
    for(int i=0;i<m;i++){
        printf("Enter maximum number of units process p%d will request from each resource(r%d to r%d): ",i,0,n-1);
        switch(n){
        case 1:
            scanf("%d",&max[i][0]);
            break;
        case 2:
            scanf("%d %d",&max[i][0],&max[i][1]);
            break;
        case 3:
            scanf("%d %d %d",&max[i][0],&max[i][1],&max[i][2]);
            break;
        case 4:
            scanf("%d %d %d %d",&max[i][0],&max[i][1],&max[i][2],&max[i][3]);
            break;
        case 5:
            scanf("%d %d %d %d %d",&max[i][0],&max[i][1],&max[i][2],&max[i][3],&max[i][4]);
            break;
    }
    }
    for(int i=0;i<m;i++){
        printf("Enter number of units of each resource(r%d to r%d) allocated to process p%d : ",0,n-1,i);
        switch(n){
        case 1:
            scanf("%d",&allocated[i][0]);
            break;
        case 2:
            scanf("%d %d",&allocated[i][0],&allocated[i][1]);
            break;
        case 3:
            scanf("%d %d %d",&allocated[i][0],&allocated[i][1],&allocated[i][2]);
            break;
        case 4:
            scanf("%d %d %d %d",&allocated[i][0],&allocated[i][1],&allocated[i][2],&allocated[i][3]);
            break;
        case 5:
            scanf("%d %d %d %d %d",&allocated[i][0],&allocated[i][1],&allocated[i][2],&allocated[i][3],&allocated[i][4]);
            break;
    }
    for(int i=0;i<n;i++){
        available[i]=resources[i];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++){
            need[i][j] = max[i][j] - allocated[i][j];
            available[j]-=allocated[i][j];
        }
    } 
    }


	return;
}
void SafeSequence(){
    int flag[m];
    for(int i=0;i<m;i++){
        flag[i]=0;
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(flag[j]==0){
                int f = 0;
                printf("Checking p%d\n",j);
                for(int k=0;k<n;k++){
                    if(need[j][k]>available[k]){
                        f=1;
                        break;
                    }
                }
                if(f==0){
                    flag[j]=1;
                    for(int l=0;l<n;l++){
                        available[l]+=allocated[j][l];
                    }
                    printf("p%d safely sequenced\n",j);
                }
            }
        }
    }
}
void GarbageCollection(){
    free(resources);
    free(available);
    free(allocated);
    free(max);
    free(need);
}

int main() {
    int choice;
    while(choice!=3){
        printf("\nBanker's Algorithm\n------------------\n1)Enter Parameters\n2)Determine Safe Sequence\n3)Quit Program\n");
        printf("\nPlease enter selection: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                EnterParameters();
                PrintResources();
                PrintAvailable();
                PrintMax();
                PrintAllocated();
                PrintNeed();
                break;
            case 2:
                SafeSequence();
                break;
        }
    }
    GarbageCollection();
    return 1;
}