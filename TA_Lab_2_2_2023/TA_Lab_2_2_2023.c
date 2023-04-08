//TA_Lab_2_2_2023.c Масиви структур. Створення структури банківських вкладів.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct Deposit//вклади
{
	float many;//сума вкладу
	char date[11];//дата вкладу
};

struct Client//Клієнти
{
	int marks;//рахунок
	char surname[25];//Фамілія
	struct Deposit *deal;
	int quant;//лічильник к-ті вкладів
};

int main(void)
{
	//Встановив кодування, підключення Укр. мови
	system("chcp 1251");
	setlocale(LC_CTYPE, "ukr");
	system("cls");

	static int i, j;
	
	struct Client *Bank;
	Bank = (struct Client*)malloc(sizeof(struct Client));
	if (Bank == NULL)
	{
		printf("Збій виділення динамічної пам'яті");
		exit(1);
	}
	//Введення даних з консолі
	char C, D;
	i = 0;
	printf(" Введіть особисті дані клієнтів банку. \n");
	do
	{
		printf(" Введіть особистий рахунок %d вкладника: ", (1 + i));
		scanf("%d", &(Bank + i)->marks);
		printf(" Введіть прізвище та ініціали %d вкладника: ", (1 + i));
		getchar();
		gets_s((Bank + i)->surname, 25 * sizeof(char));
		printf(" Введіть операції %d вкладника:\n", (1 + i));
		
		(Bank+i)->deal = (struct Deposit*)malloc(sizeof(struct Deposit));
		if ((Bank + i)->deal == NULL)
		{
			printf("Збій виділення динамічної пам'яті");
			exit(1);
		}

		j = 0;
		do
		{
			printf("\t Операція %d вкладника %d: сума вкладу => ", (1 + j), (1 + i));
			scanf("%f", &((Bank + i)->deal + j)->many);
			printf("\t Операція %d вкладника %d: дата => ", (1 + j), (1 + i));
			getchar();
			gets_s(((Bank + i)->deal + j)->date, 11 * sizeof(char));
			printf("Додати ще один вклад y/n: ");
			D = getchar();
			j++; 
			(Bank + i)->deal = (struct Deposit*)realloc((Bank + i)->deal, (1+j)*sizeof(struct Deposit));
		}
	while (D == 'y');
	(Bank + i)->quant = j;
	getchar();
	printf("Додати ще одного вкладника y/n: ");
	C = getchar();
	i++;
	Bank = (struct Client*)realloc(Bank, (1 + i) * sizeof(struct Client));
	} 
	while (C == 'y');
	int N = i;

	system("cls");

	printf(" Введені вами відомості про клієнтів:\n");
	printf("  ________________________________________________________________________________________ \n");
	printf(" | № рахунку   | Пірзвище та Ініціали        | К-ть вкладів  | Сума вкладу   | Дата вкладу|\n");
	printf(" |_____________|_____________________________|_______________|_______________|____________| \n");
	char t[] = { " " };
	for (i = 0; i < N; i++)
	{
		printf(" | %-11d | %-27s | %-13d | %-13s | %-10s |\n", (Bank + i)->marks, (Bank + i)->surname, (Bank + i)->quant, t, t);

		for (j = 0; j < ((Bank + i)->quant); j++)
		{
			printf(" | %-11s | %-27s | %-13s | %-12.2f  | %-10s |\n", t, t, t, ((Bank + i)->deal + j)->many, ((Bank + i)->deal + j)->date);
			if (j != ((Bank + i)->quant) - 1) printf(" | %-11s | %-27s | %-13s |_______________|____________| \n", t, t, t);
			else printf(" |_____________|_____________________________|_______________|_______________|____________| \n");
		}
	}
	//Сорування структури по максимальному числу вкладів
	for (i = N - 1; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			struct Client tmp;
			if ((Bank + j)->quant < (Bank+ 1 +j)->quant)
			{
				tmp = *(Bank + j);
				*(Bank + j) = *(Bank + 1 + j);
				*(Bank + 1 + j) = tmp;
			}
		}
	}

	printf("\n Клієнти банку в послідовності зменшення кількості операцій:\n");
	printf("  ________________________________________________________________________________________ \n");
	printf(" | № рахунку   | Пірзвище та Ініціали        | К-ть вкладів  | Сума вкладу   | Дата вкладу|\n");
	printf(" |_____________|_____________________________|_______________|_______________|____________| \n");
	
	for (i = 0; i < N; i++)
	{
	printf(" | %-11d | %-27s | %-13d | %-13s | %-10s |\n", (Bank + i)->marks, (Bank + i)->surname, (Bank + i)->quant, t, t);
		
		for (j = 0; j < ((Bank + i)->quant); j++)
		{
			printf(" | %-11s | %-27s | %-13s | %-12.2f  | %-10s |\n", t, t, t, ((Bank + i)->deal + j)->many, ((Bank + i)->deal + j)->date);
			if (j!= ((Bank + i)->quant)-1) printf(" | %-11s | %-27s | %-13s |_______________|____________| \n", t, t, t);
			else printf(" |_____________|_____________________________|_______________|_______________|____________| \n");
		}
	}

	for (i = 0; i < N; i++)
	free((Bank + i)->deal);
	free(Bank);
	
	int getch(); getch();
	return 0;
}
