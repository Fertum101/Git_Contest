#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n); // Вводим количество законов
    
    int laws[n]; // Список для хранения информации о законах
    
    int active_laws = 0; // Переменная для хранения количества действующих законов
    
    for (int i = 0; i < n; i++) {
        char operation[100];
        scanf("%s", operation); // Вводим операцию (declare или cancel)
        
        if (strcmp(operation, "declare") == 0) {
            laws[i] = -1; // Если операция declare, устанавливаем значение закона в -1 (Активный закон)
        } else {
            int cancel_index;
            scanf("%d", &cancel_index); // Вводим номер закона, который нужно аннулировать
            laws[i] = cancel_index; // Сохраняем индекс аннулированного закона
        }
    }
    
    // С конца списка ищем поправки, аннулирующие законы, и аннулируем соответствующие законы
    for (int i = n-1; i >= 0; i--) if (laws[i] != 0 && laws[i] != -1) laws[laws[i]-1] = 0;
    
    // Считаем количество активных законов
    for (int i = 0; i < n; i++) if (laws[i] != 0) active_laws++;
    
    printf("%d\n", active_laws); // Выводим количество действующих законов
    
    // Выводим номера действующих законов
    for (int i = 0; i < n; i++) if (laws[i] != 0) printf("%d ", i + 1); 
    
    return 0;
}