#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    // Initialization of variables and bracket count in the buffer
    int N, count = 0; 
    scanf("%d", &N);
    fflush(stdin);

    // Creating string for brackets and buffer string
    char S[N], buff[N];    
    gets(S);

    // If the number of brackets is odd, then by definition the expression cannot be obtained
    if (N % 2 != 0) {printf("No"); return 0;}

    // Main Loop
    for (int i = 0; i < N; i++)
    {
        if ((S[i] == '(') || (S[i] == '{') || (S[i] == '[')) // Open parenthesis check
        {
            buff[count] = S[i]; // Adding to the buffer and incrementing the counter
            count++;
        }

        if (((S[i] == ')' && buff[count-1] == '(') || (S[i] == ']' && buff[count-1] == '[') || (S[i] == '}' && buff[count-1] == '{')) && count > 0) // Checking the closing parentheses against the opening ones from the buffer and decrementing the count
        {
            count--;
        }
        else if ((S[i] == ')' || S[i] == ']' || S[i] == '}') && count == 0) // Otherwise, we check the absence of opening brackets with the following closing
        {
            count--;
            break;
        }   
    }

    // If the counter = 0, then we output a positive result, otherwise - a negative one.
    if (count != 0) printf("No");
    else printf("Yes");
    
    return 0;
}
