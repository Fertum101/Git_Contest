#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int laws[n];
    
    int active_laws = 0;
    
    for (int i = 0; i < n; i++) {
        char operation[100];
        scanf("%s", operation);
        
        if (strcmp(operation, "declare") == 0) {
            laws[i] = -1;
        } else {
            int cancel_index;
            scanf("%d", &cancel_index);
            laws[i] = cancel_index;
        }
    }
    
    for (int i = n-1; i >= 0; i--) if (laws[i] != 0 && laws[i] != -1) laws[laws[i]-1] = 0;
    
    for (int i = 0; i < n; i++) if (laws[i] != 0) active_laws++;
    
    printf("%d\n", active_laws); 
    
    for (int i = 0; i < n; i++) if (laws[i] != 0) printf("%d ", i + 1); 
    
    return 0;
}
