#include <stdio.h>
#include <math.h>

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Error: Division by zero.\n");
        return 0;
    }
}

double power(double base, double exponent) {
    return pow(base, exponent);
}

double square_root(double number) {
    if (number >= 0) {
        return sqrt(number);
    } else {
        printf("Error: Square root of a negative number.\n");
        return 0;
    }
}

double factorial(int number) {
    if (number < 0) {
        printf("Error: Factorial of a negative number is not defined.\n");
        return 0;
    }
    double result = 1;
    for (int i = 1; i <= number; i++) {
        result *= i;
    }
    return result;
}

double sine_function(double angle) {
    return sin(angle);
}

double cosine_function(double angle) {
    return cos(angle);
}

double tangent_function(double angle) {
    return tan(angle);
}

int main() {
    double x = 5.0, y = 3.0;

    printf("Addition of %.2f and %.2f: %.2f\n", x, y, add(x, y));
    printf("Subtraction of %.2f and %.2f: %.2f\n", x, y, subtract(x, y));
    printf("Multiplication of %.2f and %.2f: %.2f\n", x, y, multiply(x, y));
    printf("Division of %.2f and %.2f: %.2f\n", x, y, divide(x, y));
    printf("Power of %.2f to %.2f: %.2f\n", x, y, power(x, y));
    printf("Square root of %.2f: %.2f\n", x, square_root(x));
    printf("Factorial of %d: %.2f\n", (int)y, factorial((int)y));
    printf("Sine of %.2f radians: %.2f\n", x, sine_function(x));
    printf("Cosine of %.2f radians: %.2f\n", x, cosine_function(x));
    printf("Tangent of %.2f radians: %.2f\n", x, tangent_function(x));

    return 0;
}
