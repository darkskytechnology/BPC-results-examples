#include <stdio.h>

// Function to swap the values of two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print the values of two integers
void print_values(int a, int b) {
    printf("a = %d, b = %d\n", a, b);
}

int main() {
    int x = 5;
    int y = 10;

    printf("Before swapping:\n");
    print_values(x, y);

    // Call the swap function
    swap(&x, &y);

    printf("After swapping:\n");
    print_values(x, y);

    return 0;
}
