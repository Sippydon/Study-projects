/*------------------------------------
	Здравствуй, человек!
	Чтобы получить ключ 
	поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define NMAX 10

void input(int *buffer, int *length, int *flag);
void output(int *buffer, int sum, int flag, int numbers_length);
int sum_numbers(int *buffer, int length, int *flag);
int find_numbers(int* buffer, int length, int number, int *numbers, int *numbers_length);

/*------------------------------------
	Функция получает массив данных 
	через stdin.
	Выдает в stdout особую сумму
	и сформированный массив 
	специальных элементов
	(выбранных с помощью найденной суммы):
	это и будет частью ключа
-------------------------------------*/
int main() {
    int length, buffer[NMAX], flag, numbers[NMAX], sum, numbers_length;
    int f = 0;

    input(buffer, &length, &flag);
    if (flag == 0) {
        sum = sum_numbers(buffer, length, &f);
        find_numbers(buffer, length, sum, numbers, &numbers_length);
        output(numbers, sum, f, numbers_length);
    } else {
        printf("n/a");
    }

    return 0;
}

/*------------------------------------
	Функция должна находить
	сумму четных элементов 
	с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length, int *flag) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum += buffer[i];
            *flag = 1;
        }
    }

    return sum;
}

/*------------------------------------
	Функция должна находить
	все элементы, на которые нацело
	делится переданное число и
	записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int* buffer, int length, int number, int* numbers, int *numbers_length) {
    int j = 0;

    for (int i = 0; i < length; i++) {
        if (*(buffer + i) != 0 && (number % *(buffer + i)) == 0) {
            *(numbers + j) = *(buffer + i);
            j++;
        }
    }
    *(numbers + j) = 0;
    *numbers_length = j;

    return number;
}

void input(int *buffer, int *length, int *flag) {
    char c;

    scanf("%d", length);
    scanf("%c", &c);

    if (c == '\n' && *length > 0 && *length < 11) {
        for (int i = 0; i < *length; i++) {
            scanf("%d", (buffer + i));
        }

        scanf("%c", &c);

        if (c != '\n') {
            *flag = 1;
        }
    } else {
        *flag = 1;
    }
}

void output(int *buffer, int sum, int flag, int numbers_length) {
    if (flag == 1) {
        printf("%d\n", sum);
        int i = 0;

        if (numbers_length == 0) {
            printf("n/a");
        }

        while (buffer[i] != 0) {
            printf("%d", buffer[i]);

            if (i < (numbers_length - 2)) {
                printf(" ");
            }
            i++;
        }
    } else {
        printf("n/a");
    }
}
