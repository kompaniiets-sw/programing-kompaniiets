/**
 * @file main.c
 * @brief Лабораторна робота №3. Розробка лінійних програм.
 * @details Індивідуальне завдання №18: Дано 4-розрядне число у системі
 *          числення p (від 2 до 10). Визначити його еквівалент у десятковій
 *          системі числення.
 *
 * ХІД РОБОТИ:
 * 1. Оголошення змінних для основи системи числення (p) та 4-х розрядів
 *    числа (d3, d2, d1, d0).
 * 2. Уведення та перевірка коректності основи p в діапазоні [2..10].
 * 3. Уведення та перевірка розрядів числа (кожен розряд у діапазоні [0..p-1]).
 * 4. Обчислення десяткового еквівалента за позиційною формулою:
 *    decimal = d3 * p^3 + d2 * p^2 + d1 * p^1 + d0 * p^0.
 * 5. Виведення результату на екран.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Безпечно читає ціле число зі стандартного вводу.
 * @param prompt Підказка для користувача.
 * @param out Вказівник на змінну, куди буде записано результат.
 * @return 1 у разі успіху, 0 у разі помилки введення.
 */
static int read_int(const char *prompt, int *out)
{
	char buf[64];
	char *end = NULL;
	long val = 0;

	printf("%s", prompt);
	if (fgets(buf, sizeof buf, stdin) == NULL) {
		return 0;
	}

	errno = 0;
	val = strtol(buf, &end, 10);
	if (end == buf || errno != 0 || val < INT_MIN || val > INT_MAX) {
		return 0;
	}

	while (*end == ' ' || *end == '\t') {
		end++;
	}
	if (*end != '\n' && *end != '\0') {
		return 0;
	}

	*out = (int)val;
	return 1;
}

int main(void)
{
	// 1: оголошення змінних
	int base_val = 0;
	int digit_three = 0;
	int digit_two = 0;
	int digit_one = 0;
	int digit_zero = 0;
	int decimal_result = 0;

	printf("=== Конвертер 4-розрядного числа з бази p у десяткову систему ===\n");

	// 2: уведення основи системи числення p
	if (!read_int("Введіть основу системи числення p (від 2 до 10): ", &base_val) || base_val < 2 || base_val > 10) {
		printf("Помилка: основа повинна бути цілим числом у діапазоні [2..10]!\n");
		return 1;
	}

	// 3: уведення 4 розрядів числа (від старшого до молодшого)
	if (!read_int("Введіть розряд d3 (старший): ", &digit_three) || !read_int("Введіть розряд d2: ", &digit_two) ||
	    !read_int("Введіть розряд d1: ", &digit_one) || !read_int("Введіть розряд d0 (молодший): ", &digit_zero)) {
		printf("Помилка введення розрядів!\n");
		return 1;
	}

	// перевіряємо, чи відповідають розряди системі числення [0..p-1]
	if (digit_three < 0 || digit_three >= base_val || digit_two < 0 || digit_two >= base_val || digit_one < 0 || digit_one >= base_val ||
	    digit_zero < 0 || digit_zero >= base_val) {
		printf("Помилка: кожен розряд має бути в діапазоні [0..%d]!\n", base_val - 1);
		return 1;
	}

	// 4: обчислення еквівалента у десятковій системі числення
	decimal_result = digit_three * base_val * base_val * base_val + digit_two * base_val * base_val + digit_one * base_val + digit_zero;

	// 5: виведення результату
	printf("Число у системі %d: %d%d%d%d\n", base_val, digit_three, digit_two, digit_one, digit_zero);
	printf("Його еквівалент у десятковій системі: %d\n", decimal_result);

	return 0;
}
