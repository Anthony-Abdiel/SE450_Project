#include "AVL_Tree_Utility.h"


void process_input(FILE *input, AvlTreeNodeType **root);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening file");
        return 1;
    }

    AvlTreeNodeType *root = NULL;
    process_input(input, &root);

    fclose(input);
    return 0;
}

// Updated process_input function
void process_input(FILE *input, AvlTreeNodeType **root) {
    char operation[10];
    char name[100];
    char city[100];
    int rank;

    while (fscanf(input, "%s", operation) != EOF) {
        if (strcmp(operation, "insert") == 0) {
            // Read the university name, city, and rank
            if (fscanf(input, "%99s %99s %d", name, city, &rank) == 3) {
                *root = insertRawData(*root, name, city, rank);
            } else {
                fprintf(stderr, "Invalid input format for insert operation.\n");
            }
        } else if (strcmp(operation, "search") == 0) {
            // Read the university name to search
            if (fscanf(input, "%99s", name) == 1) {
                AvlTreeNodeType *result = search(*root, name);
                if (result) {
                    char buffer[200];
                    universityDataToString(buffer, *result);
                    printf("Found: %s\n", buffer);
                } else {
                    printf("Not found: %s\n", name);
                }
            } else {
                fprintf(stderr, "Invalid input format for search operation.\n");
            }
        } else if (strcmp(operation, "DIO") == 0) {
            int count = 1;
            displayInOrder(*root, &count);
        } else if (strcmp(operation, "DPOST") == 0) {
            int count = 1;
            displayPostOrder(*root, &count);
        } else if (strcmp(operation, "DPRE") == 0) {
            int count = 1;
            displayPreOrder(*root, &count);
        } else if (strcmp(operation, "CLR") == 0) {
            *root = clearTree(*root);
            printf("Tree cleared.\n");
        } else if (strcmp(operation, "DSIO") == 0) {
            char segment[100];
            if (fscanf(input, "%99s", segment) == 1) {
                int count = 1;
                displaySelectionInOrder(*root, segment, &count);
            } else {
                fprintf(stderr, "Invalid input format for DSIO operation.\n");
            }
        } else if (strcmp(operation, "VALH") == 0) {
            int nodeCount = countNodes(*root);
            if (isHeightValid(*root, nodeCount)) {
                printf("Tree height is valid.\n");
            } else {
                printf("Tree height is NOT valid.\n");
            }
        } else if (strcmp(operation, "CNT") == 0) {
            int nodeCount = countNodes(*root);
            printf("Node count: %d\n", nodeCount);
        } else {
            fprintf(stderr, "Unknown operation: %s\n", operation);
        }
    }
}