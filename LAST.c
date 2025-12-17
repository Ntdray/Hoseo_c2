#include <stdio.h>
#include <string.h>
#include <math.h>

#define WORD 16


void getBinary(char bin[], char str[], int n) {
    int len = strlen(str);
    int i;

    //초기화
    for (i = 0; i < n; i++) {
        bin[i] = '0';
    }
    bin[n] = '\0';

    int start = n - len;
    if (start < 0) start = 0;

    for (i = 0; i < len && (start + i) < n; i++) {
        bin[start + i] = str[i];
    }
}

//2의 보수를 구하는 함수
void complement2(char bin[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        bin[i] = (bin[i] == '0') ? '1' : '0';
    }

    for (i = n - 1; i >= 0; i--) {
        if (bin[i] == '0') {
            bin[i] = '1';
            break;
        } else {
            bin[i] = '0';
        }
    }
}

//2진수 문자열을 10진수 정수로 변환하는 함수
int bin2dec(char bin[], int n) {
    int num = 0;
    int i;
    char temp[WORD + 1];

    strcpy(temp, bin);

    if (temp[0] == '1') {
        complement2(temp, n);
        
        // 2진수 -> 10진수 변환
        int power = 1;
        for (i = n - 1; i >= 0; i--) {
            if (temp[i] == '1') {
                num += power;
            }
            power *= 2;
        }
        
        return -num;
    } 
    else {
        // 양수일 경우 단순 변환
        int power = 1;
        for (i = n - 1; i >= 0; i--) {
            if (temp[i] == '1') {
                num += power;
            }
            power *= 2;
        }
        return num;
    }
}

int main() {
    char input1[100];
    char input2[100];
    char op[10];

    char binary1[WORD + 1] = { 0 };
    char binary2[WORD + 1] = { 0 };

    int result;
    int num1, num2;

    printf("<<<<input>>>>>>\n");
    gets(input1);
    gets(op);
    gets(input2);

    getBinary(binary1, input1, WORD);
    getBinary(binary2, input2, WORD);

    num1 = bin2dec(binary1, WORD);
    num2 = bin2dec(binary2, WORD);

    switch (op[0]) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': 
            if(num2 != 0) result = num1 / num2; 
            else { printf("Error: Divide by zero\n"); return 1; }
            break;
        case '%': 
            if(num2 != 0) result = num1 % num2;
            else { printf("Error: Divide by zero\n"); return 1; }
            break;
        default: printf("bad operator...\n"); break;
    }

    printf("%s(%d) %c %s(%d) = %d\n", binary1, num1, op[0], binary2, num2, result);

    return 0;
}
