#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int A[], int n)
{
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000000000000000;
    }
}

void ShakerSort(int A[], int n, int *swaps, int *comparisons) {
    *swaps = 0;
    *comparisons = 0;
    int l = 0, r = n - 1, k = n - 1;

    do {
        for (int j = r; j > l; j--) {
            (*comparisons) += 1;
            if (A[j] < A[j - 1]) {
                int cp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = cp;
                k = j;
                (*swaps) += 3;
            }
        }
        l = k;
        for (int j = l; j < r; j++) {
            (*comparisons) += 1;
            if (A[j] > A[j + 1]) {
                int cp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = cp;
                k = j;
                (*swaps) += 3;
            }
        }
        r = k;
    } while (l < r);
}

void BubbleSort(int A[], int n, int *swaps, int *comparisons)
{
    *comparisons = 0;
    *swaps = 0;

    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            (*comparisons)++;
            if (A[j] < A[j-1]) {
                int k = A[j];
                A[j] = A[j-1];
                A[j-1] = k;
                (*swaps) += 3;
            }
        }
    }
}

int TheorT(int n)
{
    int theor_comparisons = (n * (n - 1)) / 2;
    int theor_swaps = (3*theor_comparisons)/2;
    return theor_comparisons + theor_swaps;
}

int Bubble(void (*FillFunc)(int [], int), int n)
{
    int A[n], comparisons, swaps;
    int theor_comparisons = (n * (n - 1)) / 2;
    int theor_swaps = (3*theor_comparisons)/2;

    FillFunc(A, n);
    BubbleSort(A, n, &swaps, &comparisons);

    return comparisons + swaps;
}

int Shaker(void (*FillFunc)(int [], int), int n)
{
    int A[n], comparisons, swaps;
    int theor_comparisons = (n * (n - 1)) / 2;
    int theor_swaps = (3*theor_comparisons)/2;

    FillFunc(A, n);
    ShakerSort(A, n, &swaps, &comparisons);

    return comparisons + swaps;
}

int main()
{
    int N[5];
    srand(time(NULL));

    for (int i = 1; i < 6; i++) {
        N[i-1] = i*100;
    } 

    printf("  N |           M+C пузырьковой            |             M+C шейкерной        | \n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    |   Убыв.  |     Случ.   |  Возр.      |    Убыв.   |    Случ.   |  Возр. |\n");
    printf("-------------------------------------------------------------------------------\n"); //+21
    printf("%d  | %d   | %d       |  %d       |    %d   |  %d     |   %d   |\n", N[0], Bubble(FillDec, N[0]), Bubble(FillRand, N[0]), Bubble(FillInc, N[0]), 
            Shaker(FillDec, N[0]), Shaker(FillRand, N[0]), Shaker(FillInc, N[0]));
    printf("-------------------------------------------------------------------------------\n");
    printf("%d  | %d   | %d       |  %d      |    %d   |  %d     |  %d   |\n", N[1], Bubble(FillDec, N[1]), Bubble(FillRand, N[1]), Bubble(FillInc, N[1]), 
            Shaker(FillDec, N[1]), Shaker(FillRand, N[1]), Shaker(FillInc, N[1]));
    printf("-------------------------------------------------------------------------------\n");
    printf("%d  | %d  | %d      | %d       |    %d  |  %d     |   %d  |\n", N[2], Bubble(FillDec, N[2]), Bubble(FillRand, N[2]), Bubble(FillInc, N[2]), 
            Shaker(FillDec, N[2]), Shaker(FillRand, N[2]), Shaker(FillInc, N[2]));
    printf("-------------------------------------------------------------------------------\n");
    printf("%d  | %d  | %d      |  %d      |    %d  |  %d    |  %d   |\n", N[3], Bubble(FillDec, N[3]), Bubble(FillRand, N[3]), Bubble(FillInc, N[3]), 
            Shaker(FillDec, N[3]), Shaker(FillRand, N[3]), Shaker(FillInc, N[3]));
    printf("-------------------------------------------------------------------------------\n");
    printf("%d  | %d  | %d      |  %d     |    %d  |  %d    |   %d  |\n", N[4], Bubble(FillDec, N[4]), Bubble(FillRand, N[4]), Bubble(FillInc, N[4]), 
            Shaker(FillDec, N[4]), Shaker(FillRand, N[4]), Shaker(FillInc, N[4]));
    printf("-------------------------------------------------------------------------------\n");
    
        
    
}
