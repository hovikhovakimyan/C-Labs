#include <stdio.h>
#include <stdlib.h>
struct node {
    int id;
    int arrival;
    int total_cpu;
    int done;
    int start;
    int end;
    int turnaround;
    int sort_field;
}*table=NULL;

typedef struct node table_type;
int processes;

void printTable() {

	printf("ID      Arrival      Total      Start      End      Turnaround\n");
    printf("--------------------------------------------------------------\n");

    for(int i=0;i<processes;i++){
        printf("%2d      %7d      %5d      %5d      %3d      %10d\n", table[i].id, table[i].arrival, table[i].total_cpu,table[i].start,table[i].end,table[i].turnaround);
    }
	

	return;
}

void enterParameters() {

	printf("Enter maximum number of processes: ");
    scanf("%d",&processes);
    table=(table_type*)calloc(processes,sizeof(table_type));

    for(int i=0;i<processes;i++){
        printf("Enter process id: ");
        scanf("%d",&table[i].id);
        printf("Enter arrival time for P[%d]: ",table[i].id);
        scanf("%d",&table[i].arrival);
        printf("Enter total CPU time for P[%d]: ",table[i].id);
        scanf("%d",&table[i].total_cpu);
    }
    printf("ID      Arrival      Total      Start      End      Turnaround\n");
    printf("--------------------------------------------------------------\n");

    for(int i=0;i<processes;i++){
        printf("%2d      %7d      %5d\n", table[i].id, table[i].arrival, table[i].total_cpu);
    }
	
	return;	
}

table_type* sort(table_type* list) {
	int i,j;
    table_type temp;

    for(int i=0;i<processes-1;i++){
        for(int j=i+1;j<processes;j++){
            if(list[i].sort_field > list[j].sort_field){
                temp=list[i];
                list[i]=list[j];
                list[j]=temp;
            }
        }
    }

	return list;
}

void FIFO() {

    int i;
    table_type* sorted;
    sorted = (table_type*)calloc(processes,sizeof(table_type));
    for(int i=0;i<processes;i++){
        table[i].sort_field=table[i].arrival;
    }
    sorted = sort(table);
    sorted[0].start = sorted[0].arrival;
    sorted[0].end = sorted[0].start+sorted[0].total_cpu;
    sorted[0].turnaround=sorted[0].total_cpu;

    for(int i=1;i<processes;i++){
        sorted[i].start=sorted[i-1].end;
        sorted[i].end = sorted[i].start+sorted[i].total_cpu;
        sorted[i].turnaround=sorted[i].end-sorted[i].arrival;
    }
    printTable();

	return;
}
void SJF() {
	int i;
    table_type* sorted;
    sorted = (table_type*)calloc(processes,sizeof(table_type));
    for(int i=0;i<processes;i++){
        table[i].sort_field=table[i].total_cpu;
    }
    sorted = sort(table);
    int min=2000000;
    int fastestArrival;
    int previousEnd;
    for(int i=0;i<processes;i++){
        if(sorted[i].arrival<min){
            min=sorted[i].arrival;
            fastestArrival=i;
        }
    }
    sorted[fastestArrival].start=sorted[fastestArrival].arrival;
    sorted[fastestArrival].end=sorted[fastestArrival].start+sorted[fastestArrival].total_cpu;
    sorted[fastestArrival].turnaround=sorted[fastestArrival].end-sorted[fastestArrival].arrival;
    previousEnd=sorted[fastestArrival].end;

    for(int i=0;i<processes;i++){
        if(i!=fastestArrival && sorted[i].arrival<previousEnd){
            sorted[i].start = previousEnd;
            sorted[i].end = sorted[i].start + sorted[i].total_cpu;
            sorted[i].turnaround=sorted[i].end-sorted[i].arrival;
            previousEnd=sorted[i].end;
        }
    }
    printTable();

	return;
}
void garbageCollection() {
    if(table!=NULL){
        free(table);
    }

    return;
}

int main() {
    int choice;
    while(choice!=4){
        printf("\nBatch Scheduling\n--------------------------------\n1)Enter Parameters\n2)Schedule processes with FIFO\n3)Schedule processes with SJF\n4)Quit program and free memory\n");
        printf("\nPlease enter selection: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                enterParameters();
                break;
            case 2:
                FIFO();
                break;
            case 3:
                SJF();
                break;
        }
    }
    garbageCollection();

  return 1;
}
