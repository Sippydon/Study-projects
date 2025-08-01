#include <stdio.h>

#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void output(int *buffer, int length, int *buffer2, int length2);
void input(int *buffer, int *length, int *flag);

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод: 
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод: 
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main() {
    int length, buffer[LEN], flag, buffer2[LEN], length2;
    length = 0;
    length2 = 0;
    flag = 0;

    input(buffer, &length, &flag);
    input(buffer2, &length2, &flag);
    if (flag == 0) {
        output(buffer, length, buffer2, length2);
    } else {
        printf("n/a");
    }

    return 0;
}

void output(int *buffer, int length, int *buffer2, int length2) {
  for (int i = 0; i < length; i++) {
    printf("%d", buffer[i]);
        if (i < (length - 1)) {
          printf(" ");
        }
  }

  printf("\n");

  for (int i = 0; i < length2; i++) {
    printf("%d", buffer2[i]);
    if (i < (length2 - 1)) {
      printf(" ");
    }
  }
}

void input(int *buffer, int *length, int *flag) {
  int first, second;

  for (int i = 0; i < LEN; i++) {
    first = getchar();
    second = getchar();

    if (first > 47 && first < 58 && (second == ' ' || second == '\n' || second == '\0' || second == EOF)) {
      buffer[i] = first - 48;
      *length += 1;

      if (second == '\n' || second == '\0' || second == EOF) break;
    } else {
      *flag = 1;
    }
  }
}

// void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
//   int j = len2 - 1;

//   for(int i = len1 - 1; i != 0; i--) {
//     if (buff1[i] == 0 && (i - 1) > 0) {
//       result[i] = (buff1[i] - buff2[j]) * -1;
//       j++;

//     }

//   }
// }
