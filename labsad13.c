#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура для хранения статистики операций
typedef struct {
    int C;          // Количество сравнений
    int M;          // Количество перемещений
    int series_count; // Количество серий
    int checksum;   // Контрольная сумма
} Stats;

// Функция разделения списка на два подсписка
void splitting(Node* S, Node** c0, Node** c1, int* n) {
    Node* a = S;        // Первый элемент исходного списка
    Node* b = S->next;  // Второй элемент исходного списка
    *n = 1;             // Счетчик элементов

    Node* k = a;        // Текущий элемент первого подсписка
    Node* p = b;        // Текущий элемент второго подсписка

    *c0 = a;            // Голова первого подсписка
    *c1 = b;            // Голова второго подсписка

    while(p != NULL) {
        (*n)++;
        if (k != NULL) {
            k->next = p->next;
            k = p;
        }
        p = p->next;
    }
    // Завершаем оба подсписка NULL
    if (k != NULL) k->next = NULL;
}

Node* merge(Node* a, int q, Node* b, int r, Node** c, Node** tail, Stats* stats) {
    Node* current = *c;
    
    while (q > 0 && r > 0 && a != NULL && b != NULL) {
        stats->C++;
        if (a->data <= b->data) {
            stats->M++;
            if (*c == NULL) {
                *c = a;
                current = a;
            } else {
                current->next = a;
                current = current->next;
            }
            a = a->next;
            q--;
        } else {
            stats->M++;
            if (*c == NULL) {
                *c = b;
                current = b;
            } else {
                current->next = b;
                current = current->next;
            }
            b = b->next;
            r--;
        }
    }
    
    // Добавляем оставшиеся элементы из a
    while (q > 0 && a != NULL) {
        stats->M++;
        if (*c == NULL) {
            *c = a;
            current = a;
        } else {
            current->next = a;
            current = current->next;
        }
        a = a->next;
        q--;
    }
    
    // Добавляем оставшиеся элементы из b
    while (r > 0 && b != NULL) {
        stats->M++;
        if (*c == NULL) {
            *c = b;
            current = b;
        } else {
            current->next = b;
            current = current->next;
        }
        b = b->next;
        r--;
    }
    
    *tail = current;
    return (q > 0) ? a : b;
}

// Основная функция сортировки слиянием
Node* mergeSort(Node* s, int n, Stats* stats) {
    if (s == NULL || n <= 1) {
        return s;
    }


    int p = 1; // Начальный размер серии
    
    while (p < n) {
        Node* c[2] = {NULL, NULL};
        Node* tails[2] = {NULL, NULL};
        int i = 0;
        Node* current = s;
        int m = n;
        
        while (m > 0) {
            // Размер первой серии
            int q = (m > p) ? p : m;
            Node* a = current;
            for (int j = 1; j < q && current != NULL; j++) {
                current = current->next;
            }
            Node* next = (current != NULL) ? current->next : NULL;
            if (current != NULL) {
                current->next = NULL;
            }
            m -= q;
            
            // Размер второй серии
            int r = (m > p) ? p : m;
            Node* b = next;
            for (int j = 1; j < r && next != NULL; j++) {
                next = next->next;
            }
            Node* next_next = (next != NULL) ? next->next : NULL;
            if (next != NULL) {
                next->next = NULL;
            }
            m -= r;
            
            // Слияние серий a и b
            Node* merged_tail = NULL;
            Node* merged_head = NULL;
            merge(a, q, b, r, &merged_head, &merged_tail, stats);
            
            if (c[i] == NULL) {
                c[i] = merged_head;
            } else {
                tails[i]->next = merged_head;
            }
            tails[i] = merged_tail;
            
            i = 1 - i;
            current = next_next;
        }
        
        // Объединяем две очереди в одну
        if (tails[0] != NULL) {
            tails[0]->next = c[1];
        }
        s = (c[0] != NULL) ? c[0] : c[1];
        p *= 2;
    }
    
    return s;
}

// Функция создания списка
Node* create_list(int size) {
    Node* head = NULL;
    Node* tail = NULL;
    
    for (int i = 1; i <= size; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    return head;
}

// Функция создания случайного списка
Node* create_random_list(int size) {
    Node* head = NULL;
    Node* tail = NULL;
    srand(time(NULL));
    
    for (int i = 1; i <= size; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = rand() % 100;
        new_node->next = NULL;
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    return head;
}

// Функция создания убывающего списка
Node* create_descending_list(int size) {
    Node* head = NULL;
    Node* tail = NULL;
    
    for (int i = size; i >= 1; i--) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    return head;
}

// Функция печати списка
void print_list(Node* head, const char* name) {
    printf("Список %s: ", name);
    Node* current = head;
    int count = 0;
    
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
        count++;
    }
    
    printf("\nКоличество элементов: %d\n", count);
}

// Функция освобождения памяти
void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// Функция для вычисления контрольной суммы
int compute_checksum(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}


// Функция для подсчета количества серий
int count_series(Node* head) {
    if (head == NULL) return 0;
    
    int count = 1;
    Node* current = head;
    int prev_data = current->data;
    current = current->next;
    
    while (current != NULL) {
        if (current->data < prev_data) {
            count++;
        }
        prev_data = current->data;
        current = current->next;
    }
    
    return count;
}

int main() {
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("         Трудоемкость сортировки прямого слияния\n");
    printf("--------------------------------------------------------\n");
    printf("| N    |   М+С теоретич.    |     М+С фактич           |\n");
    printf("|______________________________________________________|\n");
    printf("|      |                    |  Убыв.  | Случ.  |Возр.  |\n");
    printf("|------------------------------------------------------|\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        
        // Теоретическая оценка: O(n log n)
        int theoretical = 2 * n * (int)ceil(log2(n)) + n;
        
        // Для убывающего списка
        Node* desc_list = create_descending_list(n);
        Stats desc_stats = {0, 0, 0, 0};
        desc_stats.checksum = compute_checksum(desc_list);
        desc_stats.series_count = count_series(desc_list);
        desc_list = mergeSort(desc_list, n, &desc_stats);
        free_list(desc_list);
        
        // Для случайного списка
        Node* rand_list = create_random_list(n);
        Stats rand_stats = {0, 0, 0, 0};
        rand_stats.checksum = compute_checksum(rand_list);
        rand_stats.series_count = count_series(rand_list);
        rand_list = mergeSort(rand_list, n, &rand_stats);
        free_list(rand_list);
        
        // Для возрастающего списка (уже отсортирован)
        Node* asc_list = create_list(n);
        Stats asc_stats = {0, 0, 0, 0};
        asc_stats.checksum = compute_checksum(asc_list);
        asc_stats.series_count = count_series(asc_list);
        asc_list = mergeSort(asc_list, n, &asc_stats);
        free_list(asc_list);
        
        printf("| %-4d | %-18d | %-7d | %-7d| %-6d|\n", 
               n, theoretical, 
               desc_stats.C + desc_stats.M, 
               rand_stats.C + rand_stats.M, 
               asc_stats.C + asc_stats.M);
    }
    
    printf("--------------------------------------------------------\n");
    return 0;
}
