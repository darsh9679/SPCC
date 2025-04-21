#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX  10     // max number of statements
#define LEN  20     // max length of RHS

struct op {
    char l;          // left‑hand side (single variable)
    char r[LEN];     // right‑hand side (no spaces)
};

int main(void) {
    struct op op[MAX], pr[MAX];
    int n, i, j, m, z = 0, pos = -1;
    char *p;

    // 1) Read input
    printf("Enter the Number of Values: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        fprintf(stderr, "Invalid count (1–%d)\n", MAX);
        return 1;
    }
    for (i = 0; i < n; i++) {
        printf("left:  ");
        scanf(" %c", &op[i].l);
        printf("right: ");
        scanf("%19s", op[i].r);
    }

    // 2) Print Intermediate Code
    printf("\nIntermediate Code\n");
    for (i = 0; i < n; i++) {
        printf("  %c = %s\n", op[i].l, op[i].r);
    }

    // 3) Dead‑code elimination → pr[]
    //    Keep op[i] if its LHS is used later, plus always the last statement
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (strchr(op[j].r, op[i].l)) {
                pr[z++] = op[i];
                pos = z - 1;
                break;
            }
        }
    }
    // always include the very last original statement
    pr[z++] = op[n - 1];
    pos = z - 1;

    printf("\nAfter Dead Code Elimination\n");
    for (i = 0; i < z; i++) {
        printf("  %c = %s\n", pr[i].l, pr[i].r);
    }
    printf("Last live position: %d\n", pos);

    // 4) Common‑subexpression elimination in pr[]
    printf("\nEliminate Common Expression\n");
    for (m = 0; m < z; m++) {
        if (pr[m].l == '\0') continue;
        for (i = m + 1; i < z; i++) {
            if (pr[i].l != '\0' && strcmp(pr[m].r, pr[i].r) == 0) {
                printf("  Duplicate at pos %d: %c = %s\n", i, pr[i].l, pr[i].r);
                pr[i].l = '\0';  // mark as removed
            }
        }
    }

    // 5) Print Optimized Code
    printf("\nOptimized Code\n");
    for (i = 0; i < z; i++) {
        if (pr[i].l != '\0') {
            printf("  %c = %s\n", pr[i].l, pr[i].r);
        }
    }

    return 0;
}
