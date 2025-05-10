#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char surname[20];
    char name[20];
    char patronymic[20];
    long long number;
};

typedef struct Person person;

void PrintPeople(person People[], int n) {
    printf("Фамилия        Имя        Отчество        Номер\n");
    for (int i = 0; i < n; i++) {
        printf("%-14s %-10s %-15s %lld \n", People[i].surname, People[i].name, People[i].patronymic, People[i].number);
    }
    printf("\n");
}

// int less(person first, person second, int key, int order) {
//     int result = 0;

//     if (key == 1) {
//         int surname_cmp = strcmp(first.surname, second.surname);
//         int name_cmp = strcmp(first.name, second.name);
//         if (surname_cmp < 0) result = -1;
//         else if (surname_cmp > 0) result = 1;
//         else if (name_cmp < 0) result = -1;
//         else result = 1;
//     } else if (key == 2) {
//         int patronymic_cmp = strcmp(first.patronymic, second.patronymic);
//         int name_cmp = strcmp(first.name, second.name);
//         if (name_cmp < 0) result = -1;
//         else if (name_cmp > 0) result = 1;
//         else if (patronymic_cmp < 0) result = -1;
//         else result = 1;
//     } else {
//         int surname_cmp = strcmp(first.surname, second.surname);
//         int patronymic_cmp = strcmp(first.patronymic, second.patronymic);
//         if (patronymic_cmp < 0) result = -1;
//         else if (patronymic_cmp > 0) result = 1;
//         else if (surname_cmp < 0) result = -1;
//         else result = 1;
//     }

//     return (order == 1) ? (result < 0) : (result > 0);
// }


// Сравнение по фамилии и имени 
int less_by_surname_name(person first, person second, int order) {
    int surname_cmp = strcmp(first.surname, second.surname);
    int name_cmp = strcmp(first.name, second.name);
    
    if (surname_cmp < 0) return (order == 1) ? 1 : 0;
    if (surname_cmp > 0) return (order == 1) ? 0 : 1;
    if (name_cmp < 0) return (order == 1) ? 1 : 0;
    return (order == 1) ? 0 : 1;
}

// Сравнение по имени и отчеству
int less_by_name_patronymic(person first, person second, int order) {
    int name_cmp = strcmp(first.name, second.name);
    int patronymic_cmp = strcmp(first.patronymic, second.patronymic);
    
    if (name_cmp < 0) return (order == 1) ? 1 : 0;
    if (name_cmp > 0) return (order == 1) ? 0 : 1;
    if (patronymic_cmp < 0) return (order == 1) ? 1 : 0;
    return (order == 1) ? 0 : 1;
}

// Сравнение по отчеству и фамилии 
int less_by_patronymic_surname(person first, person second, int order) {
    int patronymic_cmp = strcmp(first.patronymic, second.patronymic);
    int surname_cmp = strcmp(first.surname, second.surname);
    
    if (patronymic_cmp < 0) return (order == 1) ? 1 : 0;
    if (patronymic_cmp > 0) return (order == 1) ? 0 : 1;
    if (surname_cmp < 0) return (order == 1) ? 1 : 0;
    return (order == 1) ? 0 : 1;
}

int less(person first, person second, int key, int order) {
    switch (key) {
        case 1:
            return less_by_surname_name(first, second, order);
        case 2:
            return less_by_name_patronymic(first, second, order);
        case 3:
            return less_by_patronymic_surname(first, second, order);
        default:
            return 0; // на случай неверного ключа, можно вернуть значение по умолчанию
    }
}



void SelectSort(person People[], int n, int key, int order) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        
        for (int j = i + 1; j < n; j++) {
            if (less(People[j], People[k], key, order)) {
                k = j;
            }
        }
        
        if (k != i) {
            person temp = People[i];
            People[i] = People[k];
            People[k] = temp;
        }
    }
}

int main()
{
    int n = 5, key = 0, order = 0;
    
    person people[] = {
        {"Drozdova", "Maria", "Gennadievna", 89831275645LL},
        {"Belov", "Gleb", "Yuryevich", 89135647415LL},
        {"Pashko", "Victoria", "Evgenievna", 89765432111LL},
        {"Drozdova", "Svetlana", "Vladimirovna", 89993421717LL},
        {"Kuzmina", "Yesenia", "Sergeevna", 89115745408LL}
    };
    
    printf("Исходный массив:\n");
    PrintPeople(people, n);

    printf("Выберите ключ сортировки(1 - по фамилии и имени, 2 - по имени и отчеству, 3 - по отчеству и фамилии)\nКлюч: ");
    scanf("%d", &key);
    printf("Выберите направление сортировки(1 - прямое, 2 - обратное)\nНаправление: ");
    scanf("%d", &order);
    printf("\n");

    printf("Отсортированный массив:\n");
    SelectSort(people, n, key, order);
    PrintPeople(people, n);

}
