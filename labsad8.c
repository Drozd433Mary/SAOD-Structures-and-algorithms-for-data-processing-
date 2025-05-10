#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Для malloc и free

// Структура для записи телефонного справочника
typedef struct {
    char name[50];
    char surname[50];
    char phone[20];
    char address[100];
} Contact;

// Функция сравнения для сортировки по фамилии
int compare_surname(const void *a, const void *b, void *contacts) {
    int index_a = *(int*)a;
    int index_b = *(int*)b;
    Contact* contact_arr = (Contact*) contacts;

    return strcmp(contact_arr[index_a].surname, contact_arr[index_b].surname);
}

// Функция сравнения для сортировки по номеру телефона
int compare_phone(const void *a, const void *b, void *contacts) {
    int index_a = *(int*)a;
    int index_b = *(int*)b;
    Contact* contact_arr = (Contact*) contacts;
    return strcmp(contact_arr[index_a].phone, contact_arr[index_b].phone);
}

// Сортировка вставками с использованием индексного массива
void insertion_sort(int *index_array, int size, int (*compare)(const void*, const void*, void*), void* contacts) {
    for (int i = 1; i < size; i++) {
        int key = index_array[i];
        int j = i - 1;

        while (j >= 0 && compare(&index_array[j], &key, contacts) > 0) {
            index_array[j + 1] = index_array[j];
            j--;
        }
        index_array[j + 1] = key;
    }
}

// Бинарный поиск по фамилии (вывод всех однофамильцев)
void binary_search_surname(Contact* data, int* index_array, int size, const char* target_surname) {
    int low = 0, high = size - 1;
    int found = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int contact_index = index_array[mid];
        int comparison = strcmp(data[contact_index].surname, target_surname);

        if (comparison == 0) {
            // Нашли первое совпадение. Теперь нужно найти все остальные.

            // Ищем влево от mid
            int i = mid;
            while (i >= 0 && strcmp(data[index_array[i]].surname, target_surname) == 0) {
                printf("\nКонтакт найден по фамилии '%s': %s %s, Phone: %s, Address: %s\n", target_surname,
                       data[index_array[i]].name, data[index_array[i]].surname, data[index_array[i]].phone, data[index_array[i]].address);
                found = 1;
                i--;
            }

            // Ищем вправо от mid
            i = mid + 1;
            while (i < size && strcmp(data[index_array[i]].surname, target_surname) == 0) {
                printf("\nКонтакт найден по фамилии '%s': %s %s, Phone: %s, Address: %s\n", target_surname,
                       data[index_array[i]].name, data[index_array[i]].surname, data[index_array[i]].phone, data[index_array[i]].address);
                found = 1;
                i++;
            }
            break; // Все однофамильцы найдены
        } else if (comparison < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        printf("\nКонтакт с фамилией '%s' не найден.\n", target_surname);
    }
}


// Бинарный поиск по номеру телефона
int binary_search_phone(Contact* data, int* index_array, int low, int high, const char* target) {
    if (high >= low) {
        int mid = low + (high - low) / 2; // Prevent overflow
        int contact_index = index_array[mid];
        int comparison = strcmp(data[contact_index].phone, target);

        if (comparison == 0) return contact_index; // Found

        if (comparison > 0) return binary_search_phone(data, index_array, low, mid - 1, target);

        return binary_search_phone(data, index_array, mid + 1, high, target);
    }
    return -1; // Not found
}

// Функция для вывода справочника
void print_contacts(Contact *contacts, int *index_array, int size) {
    for (int i = 0; i < size; i++) {
        int index = index_array[i];
        printf("%-15s %-10s %-15s %-30s\n",
               contacts[index].surname, contacts[index].name, contacts[index].phone, contacts[index].address);
    }
}


// Функция для вывода исходного справочника
void print_original_contacts(Contact *contacts, int size) {
    printf("Телефонный справочник (без сортировки):\n");
    printf("%-15s %-10s %-15s %-30s\n", "Фамилия", "Имя", "Телефон", "Адрес");
    for (int i = 0; i < size; i++) {
        printf("%-15s %-10s %-15s %-30s\n",
               contacts[i].surname, contacts[i].name, contacts[i].phone, contacts[i].address);
    }
}

// Функция для вывода индексного массива
void print_index_array(int *index_array, int size, const char *message) {
    printf("%s", message);
    for (int i = 0; i < size; i++) {
        printf("%d ", index_array[i]);
    }
    printf("\n");
}

int main() {
    Contact contacts[] = {
        {"Мария", "Дроздова", "89831275645", "ул. Бориса Богаткова, 63"},
        {"Глеб", "Белов", "84001002328", "ул. Ленина, 13"},
        {"Григорий", "Патрушев", "89876540321", "ул. Жидкова, 18"},
        {"Александр", "Кожевников", "89999999990", "ул. Пастухова, 22"},
        {"Светлана", "Дроздова", "89133919519", "ул. Димитрова, 6"},
        {"Татьяна", "Иванова", "89925567235", "ул. Урицкого, 34"}
    };
    int size = sizeof(contacts) / sizeof(contacts[0]);

    // Создаем индексные массивы
    int *index_by_surname = (int*)malloc(size * sizeof(int));
    int *index_by_phone = (int*)malloc(size * sizeof(int));
    if (!index_by_surname || !index_by_phone) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Инициализируем индексные массивы
    for (int i = 0; i < size; i++) {
        index_by_surname[i] = i;
        index_by_phone[i] = i;
    }

    // Выводим исходный индексный массив
    print_index_array(index_by_surname, size, "Индексный массив (без сортировки): ");

    // Сортируем индексные массивы
    insertion_sort(index_by_surname, size, compare_surname, contacts);
    insertion_sort(index_by_phone, size, compare_phone, contacts);

    // Выводим исходный справочник
    print_original_contacts(contacts, size);

    // Выводим индексные массивы
    print_index_array(index_by_surname, size, "\nИндексный массив (отсортировано по фамилии): ");
    printf("\nТелефонный справочник (отсортировано по фамилии):\n");
    printf("%-15s %-10s %-15s %-30s\n", "Фамилия     ", "Имя     ", "Телефон     ", "Адрес     ");
    print_contacts(contacts, index_by_surname, size);

    print_index_array(index_by_phone, size, "\nИндексный массив (отсортировано по номеру телефона): ");
    printf("\nТелефонный справочник (отсортировано по номеру телефона):\n");
    printf("%-15s %-10s %-15s %-30s\n", "Фамилия     ", "Имя     ", "Телефон     ", "Адрес     ");
    print_contacts(contacts, index_by_phone, size);

    // int choice;
    // char search_surname[50], search_phone[20];

    // printf("\nВыберите поле для поиска:\n");
    // printf("1. Фамилия (поиск всех однофамильцев)\n");
    // printf("2. Номер телефона\n");
    // printf("Ваш выбор: ");
    // scanf("%d", &choice);
    // // Проверка на лишние символы в буфере ввода
    // while(getchar() != '\n'); // Clear input buffer

    // if (choice == 1) {
    //     printf("Введите фамилию для поиска: ");
    //     fgets(search_surname, sizeof(search_surname), stdin);
    //     search_surname[strcspn(search_surname, "\n")] = 0; // Удаляем символ новой строки

    //     binary_search_surname(contacts, index_by_surname, size, search_surname);

    // } else if (choice == 2) {
    //     printf("Введите номер телефона для поиска: ");
    //     fgets(search_phone, sizeof(search_phone), stdin);
    //     search_phone[strcspn(search_phone, "\n")] = 0; // Удаляем символ новой строки

    //      int found_index = binary_search_phone(contacts, index_by_phone, 0, size - 1, search_phone);

    //     if (found_index != -1) {
    //         printf("\nКонтакт найден по номеру телефона '%s': %s %s, Address: %s\n", search_phone,
    //                contacts[found_index].name, contacts[found_index].surname, contacts[found_index].address);
    //     } else {
    //         printf("\nКонтакт с номером телефона '%s' не найден.\n", search_phone);
    //     }
    // } else {
    //     printf("Неверный выбор.\n");
    // }


    // Освобождаем выделенную память
    free(index_by_surname);
    free(index_by_phone);

    return 0;
}
