#include <stdio.h>
#include <stdlib.h>
int* sequence=NULL;
int num_tracks;
int sequence_size;


void EnterParameters() {
    printf("Enter number of concentric tracks: ");
    scanf("%d", &num_tracks);
    printf("Enter size of sequence: ");
    scanf("%d", &sequence_size);
    sequence = (int*)malloc(sequence_size * sizeof(int));
	return;
}

void FIFO() {
    int num_traversed;

    for(int i=0;i<sequence_size;i++){
        printf("Enter sequence #%d: ",i);
        scanf("%d", &sequence[i]);
        if(sequence[i]<0||sequence[i]>num_tracks){
            printf("invalid track number\n");
            return;
        }
    } 


    printf("Traversed sequence: %d ", sequence[0]);
    num_traversed = sequence[0];

	for(int i=1;i<sequence_size;i++){	
        num_traversed += abs(sequence[i] - sequence[i-1]);
        printf("%d ", sequence[i]);
    }
    printf("\n");
	printf("The number of tracks transversed is: %d\n",num_traversed);
    return;
} 
	
void SSTF() {
    int *sorted = NULL;
    int total_delay = 0;
    int longest_delay = 0;
    int longest_track = 0;
    int num_tracks_moved = 0;
    int num_traversed;
    float average_delay;

    for(int i=0;i<sequence_size;i++){
        printf("Enter sequence #%d: ",i);
        scanf("%d", &sequence[i]);
        if(sequence[i]<0||sequence[i]>num_tracks){
            printf("invalid track number\n");
            return;
        }
    } 
	sorted = (int*)malloc(sequence_size * sizeof(int));
    for(int i=0;i<sequence_size;i++){	
        sorted[i]=sequence[i];
    }
    int temp;
    for(int i=0;i<sequence_size-1;i++){
        for(int j=i+1;j<sequence_size;j++){
            if(sorted[i]> sorted[j]){
                temp=sorted[i];
                sorted[i]=sorted[j];
                sorted[j]=temp;
            }
        }
    }
    for(int i=0;i<sequence_size-1;i++){
        int num_moves=0;
        int j = i+1;

        while ( (sequence[i] != sorted[j]) && (j < sequence_size) ){
            j++;
        } 

		if (j < sequence_size) {
            num_moves = j-i;
            total_delay += num_moves;
            num_tracks_moved += 1;		
            if (num_moves > longest_delay){
                longest_delay = num_moves;
                longest_track = sequence[i];
            }
        }
    }

    num_traversed = sorted[0];
    printf("Traversed sequence: ");
    for(int i=1;i<sequence_size;i++){
            num_traversed += (sorted[i] - sorted[i-1]);
            printf("%d ", sorted[i-1]);
    }
    printf("%d\n",sorted[sequence_size-1]);
    printf("The number of tracks transversed is: %d\n",num_traversed);	
    average_delay = total_delay / num_tracks_moved;
    printf("The average delay of all tracks processed later is: %.2f\n",average_delay);
    printf("The longest delay experienced by a track is: %d for track: %d", longest_delay, longest_track);
    free(sorted);
	return;
}

void GarbageCollection() {
	if(sequence!=NULL){
        free(sequence);
    }
	return;
} 


int main() {
	int choice;
    while(choice!=4){
        printf("\nDisk Scheduling\n--------------------------------\n1)Enter Parameters\n2)Schedule disk tracks with FIFO\n3)Schedule disk tracks with SSTF\n4)Quit program and free memory\n");
        printf("\nPlease enter selection: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                EnterParameters();
                break;
            case 2:
                FIFO();
                break;
            case 3:
                SSTF();
                break;
        }
    }
    GarbageCollection();
	return 1;
}