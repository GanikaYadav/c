#include <stdio.h>

#define MAX 100

void display(int allocation[], int remaining[], int n) {
    printf("\nProcess\tAllocated Block\n");

    for (int i = 0; i < n; i++) {
        if (allocation[i] == -1)
            printf("P%d\tNot Allocated\n", i + 1);
        else
            printf("P%d\tBlock %d\n", i + 1, allocation[i] + 1);
    }

    printf("\nRemaining Memory:\n");

    for (int i = 0; i < MAX; i++) {
        if (remaining[i] > 0)
            printf("Block %d = %d KB\n", i + 1, remaining[i]);
    }
}

void firstFit(int block[], int process[], int m, int n) {
    int rem[MAX], alloc[MAX];

    for (int i = 0; i < m; i++)
        rem[i] = block[i];

    for (int i = 0; i < n; i++) {
        alloc[i] = -1;

        for (int j = 0; j < m; j++) {
            if (rem[j] >= process[i]) {
                alloc[i] = j;
                rem[j] -= process[i];
                break;
            }
        }
    }

    display(alloc, rem, n);
}

void bestFit(int block[], int process[], int m, int n) {
    int rem[MAX], alloc[MAX];

    for (int i = 0; i < m; i++)
        rem[i] = block[i];

    for (int i = 0; i < n; i++) {
        alloc[i] = -1;
        int best = -1;

        for (int j = 0; j < m; j++) {
            if (rem[j] >= process[i]) {
                if (best == -1 || rem[j] < rem[best])
                    best = j;
            }
        }

        if (best != -1) {
            alloc[i] = best;
            rem[best] -= process[i];
        }
    }

    display(alloc, rem, n);
}

void worstFit(int block[], int process[], int m, int n) {
    int rem[MAX], alloc[MAX];

    for (int i = 0; i < m; i++)
        rem[i] = block[i];

    for (int i = 0; i < n; i++) {
        alloc[i] = -1;
        int worst = -1;

        for (int j = 0; j < m; j++) {
            if (rem[j] >= process[i]) {
                if (worst == -1 || rem[j] > rem[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            alloc[i] = worst;
            rem[worst] -= process[i];
        }
    }

    display(alloc, rem, n);
}

void nextFit(int block[], int process[], int m, int n) {
    int rem[MAX], alloc[MAX];
    int last = 0;

    for (int i = 0; i < m; i++)
        rem[i] = block[i];

    for (int i = 0; i < n; i++) {
        alloc[i] = -1;

        for (int k = 0; k < m; k++) {
            int j = (last + k) % m;

            if (rem[j] >= process[i]) {
                alloc[i] = j;
                rem[j] -= process[i];
                last = (j + 1) % m;
                break;
            }
        }
    }

    display(alloc, rem, n);
}

int main() {
    int block[MAX], process[MAX];
    int m, n, choice;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter memory block sizes:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter process sizes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &process[i]);

    printf("\n1. First Fit");
    printf("\n2. Best Fit");
    printf("\n3. Worst Fit");
    printf("\n4. Next Fit");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nFIRST FIT ALGORITHM\n");
            firstFit(block, process, m, n);
            break;

        case 2:
            printf("\nBEST FIT ALGORITHM\n");
            bestFit(block, process, m, n);
            break;

        case 3:
            printf("\nWORST FIT ALGORITHM\n");
            worstFit(block, process, m, n);
            break;

        case 4:
            printf("\nNEXT FIT ALGORITHM\n");
            nextFit(block, process, m, n);
            break;

        default:
            printf("Invalid choice!");
    }

    return 0;
}