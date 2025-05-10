#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Структура для стека
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

// Структура для очереди
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* first;
    QueueNode* end;
} Queue;

// Структура для связного списка
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// Добавление элемента в стек
void push(StackNode** top, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// Удаление элемента из стека
int pop(StackNode** top) {
    if (*top == NULL) return -1;
    StackNode* temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

// Заполнение стека возрастающими числами
void fillStackIncreasing(StackNode** top, int n) {
    for (int i = n; i >= 1; i--) {
        push(top, i);
    }
}

// Заполнение стека убывающими числами
void fillStackDecreasing(StackNode** top, int n) {
    for (int i = 1; i <= n; i++) {
        push(top, i);
    }
}

// Заполнение стека случайными числами
void fillStackRandom(StackNode** top, int n, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = minVal + rand() % (maxVal - minVal + 1);
        push(top, num);
    }
}

// Добавление элемента в очередь
void enqueue(Queue* q, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (q->end == NULL) {
        q->first = q->end = newNode;
    } else {
        q->end->next = newNode;
        q->end = newNode;
    }
}

// Удаление элемента из очереди
int dequeue(Queue* q) {
    if (q->first == NULL) return -1;
    QueueNode* temp = q->first;
    int data = temp->data;
    q->first = q->first->next;
    if (q->first == NULL) q->end = NULL;
    free(temp);
    return data;
}

// Заполнение очереди возрастающими числами
void fillQueueIncreasing(Queue* q, int n) {
    for (int i = 1; i <= n; i++) {
        enqueue(q, i);
    }
}

// Заполнение очереди убывающими числами
void fillQueueDecreasing(Queue* q, int n) {
    for (int i = n; i >= 1; i--) {
        enqueue(q, i);
    }
}

// Заполнение очереди случайными числами
void fillQueueRandom(Queue* q, int n, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = minVal + rand() % (maxVal - minVal + 1);
        enqueue(q, num);
    }
}

// Вставка элемента в начало списка
void insertToList(ListNode** head, int data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

// Печать списка
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Подсчёт контрольной суммы списка
int calculateChecksum(ListNode* head) {
    int sum = 0;
    ListNode* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

int countSeries(ListNode* head) {
    if (head == NULL) return 0;
    int count = 1; // Минимум одна серия
    ListNode* current = head;
    
    while (current->next != NULL) {
        // Если следующее число меньше текущего, серия прерывается
        if (current->data > current->next->data) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// Преобразование стека в список
ListNode* stackToList(StackNode* top) {
    ListNode* list = NULL;
    StackNode* current = top;
    while (current != NULL) {
        insertToList(&list, current->data);
        current = current->next;
    }
    return list;
}


// Преобразование очереди в список
ListNode* queueToList(Queue* q) {
    ListNode* list = NULL;
    QueueNode* current = q->first;
    while (current != NULL) {
        insertToList(&list, current->data);
        current = current->next;
    }
    return list;
}

// Освобождение памяти стека
void freeStack(StackNode** top) {
    while (*top != NULL) {
        pop(top);
    }
}

// Освобождение памяти очереди
void freeQueue(Queue* q) {
    while (q->first != NULL) {
        dequeue(q);
    }
}

// Освобождение памяти списка
void freeList(ListNode** head) {
    ListNode* current = *head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Печать стека
void printStack(StackNode* top) {
    StackNode* current = top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Печать очереди
void printQueue(Queue* q) {
    QueueNode* current = q->first;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int a = 10; // Размер структур
    int b = 10; // Максимальное случайное число

    printf("---Тестирование стека ---\n");
    
    // 1. Возрастающие числа
    StackNode* stack = NULL;
    fillStackIncreasing(&stack, a);
    printf("Стек (возрастающие числа): ");
    printStack(stack);
    
    ListNode* stackList = stackToList(stack);
    printf("Контрольная сумма: %d\n", calculateChecksum(stackList));
    printf("Количество  серий: %d\n", countSeries(stackList)); // ! Теперь считает возрастающие серии
    freeList(&stackList);
    freeStack(&stack);

    // 2. Убывающие числа
    fillStackDecreasing(&stack, a);
    printf("\nСтек (убывающие числа): ");
    printStack(stack);
    
    stackList = stackToList(stack);
    printf("Контрольная сумма: %d\n", calculateChecksum(stackList));
    printf("Количество серий: %d\n", countSeries(stackList)); // Для убывающих чисел будет много серий
    freeList(&stackList);
    freeStack(&stack);

    // 3. Случайные числа
    fillStackRandom(&stack, a, 1, b);
    printf("\nСтек (случайные числа): ");
    printStack(stack);
    
    stackList = stackToList(stack);
    printf("Контрольная сумма: %d\n", calculateChecksum(stackList));
    printf("Количество серий: %d\n", countSeries(stackList));
    freeList(&stackList);
    freeStack(&stack);

    printf("\n--- Тестирование очереди ---\n");
    
    Queue queue = {NULL, NULL};
    
    // 1. Возрастающие числа
    fillQueueIncreasing(&queue, a);
    printf("Очередь (возрастающие числа): ");
    printQueue(&queue);
    
    ListNode* queueList = queueToList(&queue);
    printf("Контрольная сумма: %d\n", calculateChecksum(queueList));
    printf("Количество серий: %d\n", countSeries(queueList)); // Должно быть 1 (вся очередь - одна возрастающая серия)
    freeList(&queueList);
    freeQueue(&queue);

    // 2. Убывающие числа
    fillQueueDecreasing(&queue, a);
    printf("\nОчередь (убывающие числа): ");
    printQueue(&queue);
    
    queueList = queueToList(&queue);
    printf("Контрольная сумма: %d\n", calculateChecksum(queueList));
    printf("Количество серий: %d\n", countSeries(queueList)); // Для убывающей очереди будет a серий (10)
    freeList(&queueList);
    freeQueue(&queue);

    // 3. Случайные числа
    fillQueueRandom(&queue, a, 1, b);
    printf("\nОчередь (случайные числа): ");
    printQueue(&queue);
    
    queueList = queueToList(&queue);
    printf("Контрольная сумма: %d\n", calculateChecksum(queueList));
    printf("Количество серий: %d\n", countSeries(queueList));
    freeList(&queueList);
    freeQueue(&queue);

printf("\n--- Тестирование списка ---\n");
    
    // Пример списка: [3, 3, 5, 2, 4, 4, 1] (вставляется в начало, поэтому порядок обратный)
    ListNode* list = NULL;
    insertToList(&list, 1);
    insertToList(&list, 4);
    insertToList(&list, 4);
    insertToList(&list, 2);
    insertToList(&list, 5);
    insertToList(&list, 3);
    insertToList(&list, 3);
    
    printf("Список: ");
    printList(list); // Напечатает: 3 3 5 2 4 4 1
    
    printf("Контрольная сумма: %d\n", calculateChecksum(list));
    printf("Количество серий: %d\n", countSeries(list)); // Ожидается 4 серии
    
    freeList(&list);
    
    return 0;
}