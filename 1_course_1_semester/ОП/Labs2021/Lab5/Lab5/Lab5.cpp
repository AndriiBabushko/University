// Lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a, b, day;
	float x, y, result;
	printf("Choose what task do you want to solve?\nWrite here '1' or '2':");
	scanf_s("%d", &a);
	switch (a){
	case 1:
		printf("Day=");
		scanf_s("%d", &day);
			switch (day) {
			case 1: printf("Monday");
				break;
			case 2: printf("Tuesday");
				break;
			case 3: printf("Wednesday");
				break;
			case 4: printf("Thursday");
				break;
			case 5: printf("Friday");
				break;
			case 6: printf("Saturday");
				break;
			case 7: printf("Sunday");
				break;
			default: printf("Error");
			}
		break;
	case 2: 
		printf("Виберіть функцію f(x) для виконання: 1-'sinx', 2-'x^2', 3-e^x\nНапишіть тут 1, 2 або 3:");
		scanf_s("%d", &b);
		switch (b) {
		case 1: 
			printf("Введіть х:");
			scanf_s("%f", &x);
			printf("Введіть y:");
			scanf_s("%f", &y);
			if (x * y > 0) {
				result = pow(sin(x) + y, 2) - pow(abs(sin(x)), 1.0 / 3);
				printf("Результат=%.2f", result);
			}
			if (x * y < 0) {
				result = pow(sin(x) + y, 2) + sin(x);
				printf("Результат=%.2f", result);
			}
			if (x * y == 0) {
				result = pow(sin(x) + y, 2) + pow(y, 3);
				printf("Результат=%.2f", result);
			}
			break;
		case 2:
			printf("Введіть х:");
			scanf_s("%f", &x);
			printf("Введіть y:");
			scanf_s("%f", &y);
			if (x * y > 0) {
				result = pow(pow(x,2) + y, 2) - pow(abs(pow(x, 2)), 1.0 / 3);
				printf("Результат=%.2f", result);
			}
			if (x * y < 0) {
				result = pow(pow(x, 2) + y, 2) + sin(x);
				printf("Результат=%.2f", result);
			}
			if (x * y == 0) {
				result = pow(pow(x, 2) + y, 2) + pow(y, 3);
				printf("Результат=%.2f", result);
			}
			break;
		case 3:
			printf("Введіть х:");
			scanf_s("%f", &x);
			printf("Введіть y:");
			scanf_s("%f", &y);
			if (x * y > 0) {
				result = pow(exp(x) + y, 2) - pow(abs(exp(x)), 1.0 / 3);
				printf("Результат=%.2f", result);
			}
			if (x * y < 0) {
				result = pow(exp(x) + y, 2) + sin(x);
				printf("Результат=%.2f", result);
			}
			if (x * y == 0) {
				result = pow(exp(x) + y, 2) + pow(y, 3);
				printf("Результат=%.2f", result);
			}
			break;
		}
	}
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
