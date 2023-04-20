#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 10000

// Stack initialization
typedef struct {
    double data[MAXSIZE];
    int size;
} Stack; 

// Add function initialization elements on the stack
void Push(Stack *S, double x )
{
    S->data[S->size] = x;
    S->size ++;
} 

// Initializing the function to remove an element from the stack
int Pop(Stack *S )
{
    S->size --;
    return S->data[S->size];
} 

int main()
{
    // Initialize and enter the number of lines
    int N = 0;
    scanf("%d", &N);
    
    // Create an array whith arrays that contains the boxes on the conveyor and ther count
    double **conveyor = (double**)malloc(N*sizeof(double*));
    for (int i = 0; i < N; i++) conveyor[i] = (double*)malloc(MAXSIZE*sizeof(double));

    // Populate the array with conveyor boxes
    for (int i = 0; i < N; i++)
    {
        int K; 
        scanf("%d", &K);
        conveyor[i][0] = (double)K; //The first element of each array stores the number of boxes
        
        // Filling the boxes of the current conveyor with priority numbers from the end
        for (int j = K; j > 0; j--)
        {
            scanf("%lf", &conveyor[i][j]);
            printf("conveyor[%d][%d] =  %lf\n", i, j, conveyor[i][j]);
        }   
    }


    for (int i = 0; i < N; i++)
    {
        // initialization of the stack for storing information about the boxes in the storage and getting the number of boxes on the current conveyor
        Stack storage;
        storage.size =  0;
        int conveyor_len = (int)conveyor[i][0];
        
        while (1)
        {
            double min = conveyor[i][1];

            // If there are no boxes in the storage and the conveyor is not empty, we look for the minimum element on the conveyor, and if it is the first on the way, we send it to the workshop, otherwise, to the storage
            if (!storage.size && conveyor_len != 0)
            {
                for (int j = 1; j <= conveyor_len; j++) if (min > conveyor[i][j]) min = conveyor[i][j];

                if (min == conveyor[i][conveyor_len]) conveyor_len--;
                else {Push(&storage, conveyor[i][conveyor_len]); conveyor_len--;}
                
            }
            else if (storage.size && conveyor_len != 0) // If the storage and pipeline are not empty - look for the minimum elements in both arrays and compare them and their positions
            {
                for (int j = 1; j <= conveyor_len; j++) if (min > conveyor[i][j]) min = conveyor[i][j];

                double min_store = storage.data[0];
                for (int j = 0; j < storage.size; j++) if (min_store > storage.data[j]) min_store = storage.data[j]; 

                if (min > min_store)
                {
                    if (min_store == storage.data[storage.size-1]) Pop(&storage); // If the minimum element is the first in the storage, we send it to the workshop. If it is impossible to send the minimum element to the workshop, we break the loop
                    else break;
                }
                else if (min == conveyor[i][conveyor_len]) conveyor_len--; // If the minimum element is in the first place on the conveyor, we send it to the workshop, otherwise - to the storage
                else {Push(&storage, conveyor[i][conveyor_len]); conveyor_len--;}
            }
            else if (storage.size && !conveyor_len) // If the elements are left only in the storage - check its first element for compliance with the minimum 
            {
                double min_store = storage.data[0];

                for (int j = 0; j < storage.size; j++) if (min_store > storage.data[j]) min_store = storage.data[j];

                if (min_store == storage.data[storage.size-1]) Pop(&storage); // // If the element is minimal, we send it to the workshop, otherwise we break the loop
                else break;
            } else break;

        }

        // If there are no elements anywhere else - print 1, otherwise - print 0
        if (!storage.size && !conveyor_len) printf("1\n");
        else printf("0\n");
    }

    return 0;
}