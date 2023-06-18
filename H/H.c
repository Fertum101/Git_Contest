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

// Функция для добавления новой ценной бумаги в базу данных
void addSecurities(char* code) {
    for (int i = 0; i < dbSize; i++) {
        // Проверяем, существует ли уже ценная бумага с данным кодом и не была ли она отозвана
        if (strcmp(database[i].code, code) == 0 && !database[i].active) {
            database[i].active = 1;
            printf("OK %s %d %d\n", code, database[i].id, database[i].reliability);
            return;
        }
    }

    // Ценная бумага с данным кодом не существует или была отозвана, добавляем новую
    strcpy(database[dbSize].code, code);
    database[dbSize].id = dbSize;
    database[dbSize].reliability = 0;
    database[dbSize].active = 1;
    printf("CREATED %d 0\n", dbSize);
    dbSize++;
}

// Функция для удаления ценной бумаги из базы данных
void deleteSecurities(char* code) {
    for (int i = 0; i < dbSize; i++) {
        // Проверяем, существует ли ценная бумага с данным кодом и активна ли она
        if (strcmp(database[i].code, code) == 0 && database[i].active) {
            database[i].active = 0;
            printf("OK %d %d\n", database[i].id, database[i].reliability);
            return;
        }
    }
    printf("BAD REQUEST\n");
}

// Функция для обновления надежности ценной бумаги
void updateReliability(char* code, long int reliability) {
    for (int i = 0; i < dbSize; i++) {
        // Проверяем, существует ли ценная бумага с данным кодом и активна ли она
        if (strcmp(database[i].code, code) == 0 && database[i].active) {
            // Обновляем надежность ценной бумаги
            database[i].reliability += reliability;
            printf("OK %d %d\n", database[i].id, database[i].reliability);
            return;
        }
    }
    printf("BAD REQUEST\n");
}

// Функция для поиска ценной бумаги по порядковому номеру
void findSecurities(int n) {
    if (dbSize == 0) {
        printf("EMPTY\n");
        return;
    }

    // Сортируем ценные бумаги по надежности (в убывающем порядке) и идентификатору (в возрастающем порядке)
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

    // Если бумага не активна, то ищем первую активную бумагу далее по списку
    while (database[n].active != 1) {
        n++;
        if (n >= dbSize) break;
    }
    
    // Запрошенный порядковый номер больше, чем количество ценных бумаг в базе данных
    if (n >= dbSize) {
        while (database[n].active != 1) {
            n--;
            // Если в базе не осталось не отозванных бумаг
            if (n < 0){
                printf("EMPTY\n");
                return;
            }
        }
        printf("OK %s %d %d\n", database[n].code, database[n].id, database[n].reliability);
    } else {
        // Находим ценную бумагу с заданным порядковым номером
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
