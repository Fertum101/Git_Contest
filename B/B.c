#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 100

// Stack initialization
typedef struct {
    int data[MAXSIZE];
    int size;
} Stack; 

// Add function initialization elements on the stack
void Push(Stack *S, int x )
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
    // Initialization of variables and stack
    int N;
    Stack impasse;
    impasse.size = 0;

    // Entering the number of wagons and initializing strings with wagons and their number
    scanf("%d", &N);
    int first_way[N], second_way[N], first_len = N-1, second_len = 0;

    // Filling in the line for the first track with wagon numbers
    for (int i = 0; i < N; i++) scanf("%d", &first_way[i]);

    // Adding the first coach to the impasse
    Push(&impasse, first_way[0]);

    // Until the second path is filled, we execute the loop
    while(second_len != N)
    {
        // If the next coach number we need is in the first place in a impasse, we move it to a impasse
        if (second_len + 1 == impasse.data[impasse.size-1])
        {
            second_way[second_len] = Pop(&impasse);
            second_len++;
        } 
        else if (first_len == 0) break; // If we cannot rearrange the coach from the impasse and there are no more coaches on the first track, we interrupt the loop
        else // Otherwise, we bring a coach from the first path to a impasse
        {
            Push(&impasse, first_way[N - first_len]);
            first_len--;
        }
    }

    // If all the cars are at a dead end - we output yes, otherwise - no
    if (second_len == N) printf("Yes");
    else printf("No");
    
    return 0;
}