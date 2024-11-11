#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int applyOperator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Error: Division by zero.\n");
                exit(1);
            }
            return a / b;
    }
    return 0;
}

int evaluateExpression(char* expression) {
    int numStack[100], numTop = -1;  
    char opStack[100], opTop = -1;   

    int i = 0;
    while (expression[i] != '\0') {
        if(expression[i]==' '){
            i++;
            continue;
        }
        if (isdigit(expression[i])) {
            int num = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            numStack[++numTop] = num;
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (opTop >= 0 && precedence(opStack[opTop]) >= precedence(expression[i])) {
                int b = numStack[numTop--];
                int a = numStack[numTop--];
                char op = opStack[opTop--];
                numStack[++numTop] = applyOperator(a, b, op);
            }
            opStack[++opTop] = expression[i];
            i++;
        } else {
            printf("Error: Invalid expression.\n");
            return -1;
        }
    }

    while (opTop >= 0) {
        int b = numStack[numTop--];
        int a = numStack[numTop--];
        char op = opStack[opTop--];
        numStack[++numTop] = applyOperator(a, b, op);
    }

    return numStack[numTop];
}

int main() {
    char expression[100];
    printf("Enter a mathematical expression: ");
    fgets(expression, sizeof(expression), stdin);

    expression[strcspn(expression, "\n")] = '\0';

    int result = evaluateExpression(expression);
    if (result != -1) {
        printf("Result: %d\n", result);
    }

    return 0;
}
