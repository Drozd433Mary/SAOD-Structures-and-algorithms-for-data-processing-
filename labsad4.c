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

int CheckSum(int A[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }

    return sum;
}

int RunNumber(int A[], int n)
{
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i - 1]) {
            count += 1;
        }
    }
    return count;
}

void PrintMas(int A[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void InsertSort(int A[], int n, int *swaps, int *comparisons) {
    *swaps = 0;
    *comparisons = 0;
    for (int i = 1; i < n; i++) {
        int t = A[i], j = i - 1;
        while(j >= 0 && t < A[j]) {
            (*comparisons) += 1;
            A[j+1] = A[j];
            j--;
            (*swaps) += 1;
        }
        if (j >= 0) {
            (*comparisons)++;
        }
        A[j+1] = t;
        (*swaps) += 2;
    }
}

int TheorT(int n)
{
    int theor_comparisons = (n*n - n)/4;
    int theor_swaps = (((n*n-n)/2)+(2*n-2))/2;

    return theor_comparisons + theor_swaps;
}

int Sort(void (*FillFunc)(int [], int), int n)
{
    int A[n], comparisons, swaps;
    int theor_comparisons = (n * (n - 1)) / 2;
    int theor_swaps = (3*theor_comparisons)/2;

    FillFunc(A, n);
    InsertSort(A, n, &comparisons, &swaps);

    return comparisons + swaps;
}

int main()
{
    int N[5];
    srand(time(NULL));

    for (int i = 1; i < 6; i++) {
        N[i-1] = i*100;
    }



    printf("N   |    C+M   |       Исходный M+C(факт.)   |\n");
    printf("    | теоретич.|     Убыв. |  Случ. |   Возр.|\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        if (i < 3) {
            printf("%d |   %d    |    %d  |  %d  |   %d |\n", N[i], TheorT(N[i]), Sort(FillDec, N[i]), Sort(FillRand, N[i]), Sort(FillInc, N[i]));
            printf("----------------------------------------------\n");
        } else {
            printf("%d |   %d   |   %d  |  %d  |  %d |\n", N[i], TheorT(N[i]), Sort(FillDec, N[i]), Sort(FillRand, N[i]), Sort(FillInc, N[i]));
            printf("----------------------------------------------\n");
        }
        
    }
    

}
