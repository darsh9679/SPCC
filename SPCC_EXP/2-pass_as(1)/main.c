// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *f1, *f2, *f3;
    int lc = 0, sa = 0, op1 = 0, o;
    char la[20], m1[20], op[20], otp[20];

    // Open files
    f1 = fopen("input.txt", "r");
    f3 = fopen("symtab.txt", "w");
    if (!f1 || !f3) {
        fprintf(stderr, "Error opening input or symtab file.\n");
        return 1;
    }

    // Read first line: label, mnemonic, operand
    if (fscanf(f1, "%s %s %d", la, m1, &op1) != 3) {
        fprintf(stderr, "Invalid START directive.\n");
        return 1;
    }
    if (strcmp(m1, "START") == 0) {
        sa = op1;
        lc = sa;
        printf("\t%s\t%s\t%d\n", la, m1, sa);
    } else {
        lc = 0;
        rewind(f1);
    }

    // Process each line: label, mnemonic, operand
    while (fscanf(f1, "%s %s %s", la, m1, op) == 3) {
        printf("\n%d\t%s\t%s\t%s\n", lc, la, m1, op);

        // Write label to symtab if present
        if (strcmp(la, "-") != 0) {
            fprintf(f3, "%d\t%s\n", lc, la);
        }

        // Check opcode table
        f2 = fopen("optab.txt", "r");
        if (!f2) {
            fprintf(stderr, "Error opening optab file.\n");
            return 1;
        }
        int found = 0;
        while (fscanf(f2, "%s %d", otp, &o) == 2) {
            if (strcmp(m1, otp) == 0) {
                lc += 3;
                found = 1;
                break;
            }
        }
        fclose(f2);

        // If not an instruction, handle directives
        if (!found) {
            if (strcmp(m1, "WORD") == 0) {
                lc += 3;
            } else if (strcmp(m1, "RESW") == 0) {
                op1 = atoi(op);
                lc += 3 * op1;
            } else if (strcmp(m1, "RESB") == 0) {
                op1 = atoi(op);
                lc += op1;
            } else if (strcmp(m1, "BYTE") == 0) {
                if (op[0] == 'X') {
                    // X'...'
                    lc += 1;
                } else if (op[0] == 'C') {
                    // C'...'
                    int len = strlen(op) - 3;  // subtract C' and '
                    lc += len;
                }
            } else if (strcmp(m1, "END") == 0) {
                break;
            }
        }
    }

    // Print program length
    printf("\nProgram Length = %d\n", lc - sa);

    fclose(f1);
    fclose(f3);
    return 0;
}
