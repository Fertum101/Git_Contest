#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char code[31];
    int id;
    int reliability;
    int active;
} Securities;

Securities database[100000];
int dbSize = 0;

void addSecurities(char* code) {
    for (int i = 0; i < dbSize; i++) {
        if (strcmp(database[i].code, code) == 0 && !database[i].active) {
            database[i].active = 1;
            printf("OK %s %d %d\n", code, database[i].id, database[i].reliability);
            return;
        }
    }

    strcpy(database[dbSize].code, code);
    database[dbSize].id = dbSize;
    database[dbSize].reliability = 0;
    database[dbSize].active = 1;
    printf("CREATED %d 0\n", dbSize);
    dbSize++;
}

void deleteSecurities(char* code) {
    for (int i = 0; i < dbSize; i++) {
        if (strcmp(database[i].code, code) == 0 && database[i].active) {
            database[i].active = 0;
            printf("OK %d %d\n", database[i].id, database[i].reliability);
            return;
        }
    }
    printf("BAD REQUEST\n");
}

void updateReliability(char* code, long int reliability) {
    for (int i = 0; i < dbSize; i++) {
        if (strcmp(database[i].code, code) == 0 && database[i].active) {
            database[i].reliability += reliability;
            printf("OK %d %d\n", database[i].id, database[i].reliability);
            return;
        }
    }
    printf("BAD REQUEST\n");
}

void findSecurities(int n) {
    if (dbSize == 0) {
        printf("EMPTY\n");
        return;
    }

    for (int i = 0; i < dbSize - 1; i++) {
        for (int j = 0; j < dbSize - i - 1; j++) {
            if (database[j].reliability < database[j + 1].reliability || (database[j].reliability == database[j + 1].reliability && database[j].id > database[j + 1].id)) 
            {
                Securities temp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = temp;
            }
        }
    }

    while (database[n].active != 1) {
        n++;
        if (n >= dbSize) break;
    }
    
    if (n >= dbSize) {
        while (database[n].active != 1) {
            n--;
            if (n < 0){
                printf("EMPTY\n");
                return;
            }
        }
        printf("OK %s %d %d\n", database[n].code, database[n].id, database[n].reliability);
    } else {
        printf("OK %s %d %d\n", database[n].code, database[n].id, database[n].reliability);
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        char query[12];
        char code[31];
        long int reliability, n;
        scanf("%s", query);

        if (strcmp(query, "ISSUE") == 0) {
            scanf("%s", code);
            addSecurities(code);
        } else if (strcmp(query, "DELETE") == 0) {
            scanf("%s", code);
            deleteSecurities(code);
        } else if (strcmp(query, "RELIABILITY") == 0) {
            scanf("%s %d", code, &reliability);
            updateReliability(code, reliability);
        } else if (strcmp(query, "FIND") == 0) {
            scanf("%d", &n);
            findSecurities(n);
        }
    }

    return 0;
}
