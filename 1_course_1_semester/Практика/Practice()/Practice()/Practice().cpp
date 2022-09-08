#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

//глобальные переменные
FILE* binary = NULL; FILE* outputfile = NULL; FILE* outputparameters = NULL;
int count_parameters = 0, parameters[3] = { 0 }, count_notes = 0;
 
// глобальные функции
void readBinary();
void writeBinary();
void menu();
int exit();
void input();
void output_header();
void parameters_();
void output_parameters(int q);
void output_parameters2_0(int z);
void output();
void searching_();
void editing_();
void delete_();
void sorting_();
void inventory();

// структуры
struct library_book_information {
	char authors[50];
	char name[50];
	char edition[50];
	char year[50];
} *book = NULL;

struct personal_library {
	struct library_book_information book;
	char section[50];
	char book_origin[50];
	char availability_of_a_book[50];
	char book_evaluation[50];
} *library = NULL;


int main() {
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	binary = fopen("binary.bin", "ab"); fclose(binary);
	remove("output.txt");
	outputfile = fopen("output.txt", "a"); fclose(outputfile);
	library = (struct personal_library*)calloc(sizeof(struct personal_library), 15);
	book = (struct library_book_information*)calloc(sizeof(struct library_book_information), 15);
	menu();
}


void readBinary() {
	FILE* binary = fopen("binary.bin", "ab");
	if (binary == NULL) {
		printf("Error opening file");
		_getch();
		exit(-3);
	}
	fread(&count_notes, sizeof(int), 1, binary);
	fread(&library, sizeof(personal_library), 1, binary);
}

void writeBinary() {
	FILE* binary = fopen("binary.bin", "wb");
	if (binary == NULL) {
		printf("Error opening file");
		_getch();
		exit(-3);
	}
	fwrite(&count_notes, sizeof(int), 1, binary);
	fwrite(&library, sizeof(personal_library), count_notes, binary);
	fclose(binary);
}


void menu() {
	printf("\nПрактика. 24.01.22. Варіант 1: Персональна бібліотека.     Виконавець: Бабушко Андрій Сергійович. Група: ВТ-21-1(1).\n| Введення даних(1) | Виведення даних(2) | Пошук(3) | Рудагування(4) | Видалення(5) | Впорядкування(6) | Інвентаризація бібліотеки(7) | |Вихід з програми(інше). |");
	int i;
	while (!_kbhit) {}
	printf("\nВибір(0-7): "); i = _getche();
	switch (i) {
	case 49: 
		system("cls");
		input();
		break;
	case 50: 
		system("cls");
		output();
		break;
	case 51: 
		system("cls");
		searching_();
		break;
	case 52:
		system("cls");
		editing_();
		break;
	case 53:
		system("cls");
		delete_();
		break;
	case 54:
		system("cls");
		sorting_();
		break;
	case 55:
		system("cls");
		inventory();
		break;
	default:
		printf("\nВи впевнені?\n");
		exit();
		break;
	}
}

int exit() {
	char m;
	while (!_kbhit) {}
	printf("\nВибір:\n| 1 - повернення до меню | інше - вихід з програми | --> "); m = _getche();
	switch (m) {
	case 49: 
		system("cls");
		menu();
		break;
	default: 
		system("cls");
		return 1;
		break;
	}
}


void input()
{
	printf("\nВведіть кількість записів:"); scanf("%d", &count_notes); 

	for (int i = 0; i < count_notes; i++) {
		
		printf("\tЗапис %d:\n", i + 1);
		printf("Інформація про книгу =>");
		printf(" Автор книги:");																    scanf("%s", &library[i].book.authors);				 
		printf("\t\t\tIм'я книги:");															    scanf("%s", &library[i].book.name);					
		printf("\t\t\tВидавництво:");															    scanf("%s", &library[i].book.edition);				
		printf("\t\t\tРік:");																	    scanf("%s", &library[i].book.year);					
		printf("\t\t\tЖанр книги(детектив, фантастика, пригоди, роман, наука, гумор, фольклор):");  scanf("%s", &library[i].section);				    
		printf("\t\t\tПоходження:");															    scanf("%s", &library[i].book_origin);				 
		printf("\t\t\tНаявність: ");															    scanf("%s", &library[i].availability_of_a_book);		 
		printf("\t\t\tОсобиста оцінка книги(0-10): ");											    scanf("%s", &library[i].book_evaluation);			 
	}

	writeBinary();

	exit();
}

void output_header() {
	printf("\n____________________________________________________________________________________________________________________________________________________________________________________\n");
	printf("|Персональна бібліотека.                                                                                                                                                            |\n");
	printf("|___________________________________________________________________________________________________________________________________________________________________________________|\n");
	printf("|Запис    |Автор(и) книги                    |Iм'я книги                    |Видавництво          |Рік     |Жанр          |Походження          |Наявність     |Особиста оцінка книги|\n");
	printf("|_________|__________________________________|______________________________|_____________________|________|______________|____________________|______________|_____________________|\n");
	// запис таблиці у файл 
	FILE* outputfile = fopen("output.txt", "w");
	fprintf(outputfile, "____________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf(outputfile, "|Персональна бібліотека.                                                                                                                                                            |\n");
	fprintf(outputfile, "|___________________________________________________________________________________________________________________________________________________________________________________|\n");
	fprintf(outputfile, "|Запис    |Автор(и) книги                    |Iм'я книги                    |Видавництво          |Рік     |Жанр          |Походження          |Наявність     |Особиста оцінка книги|\n");
	fprintf(outputfile, "|_________|__________________________________|______________________________|_____________________|________|______________|____________________|______________|_____________________|\n");
	fclose(outputfile);
	fclose(binary);
}

void parameters_() {
	
	printf("\nВиберіть кількість параметрів(1-3) чи (0) - повернутися до меню:"); scanf("%d", &count_parameters);
	if (count_parameters == 0) {
		system("cls");
		menu();
	}

	printf("За якими параметрами?\n| автор книги(1) | ім'я книги(2) | видання(3) | рік(4) | жанр(5) | походження(6) | наявність(7) | особиста оцінка(8) |\n");
	
	for (int i = 0; i < count_parameters; i++) {
		printf("Введіть параметр: "); scanf("%d", &parameters[i]);
	}
}

void output_parameters(int q) {

	if (parameters[q] == 1) {
		char author[50];
		printf("\nВведіть автора книги:"); scanf("%s", author);
		for (int z = 0; z < count_notes; z++) {
			if (strcmp(author, library[z].book.authors) == 0) {
				output_header();
				output_parameters2_0(z);
			}
		}
	}
	else {
		if (parameters[q] == 2) {
			char book_name[50];
			printf("\nВведіть ім'я книги:"); scanf("%s", book_name);
			for (int z = 0; z < count_notes; z++) {
				if (strcmp(book_name, library[z].book.name) == 0) {
					output_header();
					output_parameters2_0(z);
				}
			}
		}
		else {
			if (parameters[q] == 3) {
				char book_edition[50];
				printf("\nВведіть видання книги:"); scanf("%s", book_edition);
				for (int z = 0; z < count_notes; z++) {
					if (strcmp(book_edition, library[z].book.edition) == 0) {
						output_header();
						output_parameters2_0(z);
					}
				}
			}
			else {
				if (parameters[q] == 4) {
					char book_year[50];
					printf("\nВведіть рік:"); scanf("%s", book_year);
					for (int z = 0; z < count_notes; z++) {
						if (strcmp(book_year, library[z].book.year) == 0) {
							output_header();
							output_parameters2_0(z);
						}
					}
				}
				else {
					if (parameters[q] == 5) {
						char section[50];
						printf("\nВведіть жанр:"); scanf("%s", section);
						for (int z = 0; z < count_notes; z++) {
							if (strcmp(section, library[z].section) == 0) {
								output_header();
								output_parameters2_0(z);
							}
						}
					}
					else {
						if (parameters[q] == 6) {
							char book_origin[50];
							printf("\nВведіть походження:"); scanf("%s", book_origin);
							for (int z = 0; z < count_notes; z++) {
								if (strcmp(book_origin, library[z].book_origin) == 0) {
									output_header();
									output_parameters2_0(z);
								}
							}
						}
						else {
							if (parameters[q] == 7) {
								char availability_of_a_book[50];
								printf("\nВведіть наявність:"); scanf("%s", availability_of_a_book);
								for (int z = 0; z < count_notes; z++) {
									if (strcmp(availability_of_a_book, library[z].availability_of_a_book) == 0) {
										output_header();
										output_parameters2_0(z);
									}
								}
							}
							else {
								if (parameters[q] == 8) {
									char book_evaluation[50];
									printf("\nОцінку книги:"); scanf("%s", &book_evaluation);
									for (int z = 0; z < count_notes; z++) {
										if (strcmp(book_evaluation, library[z].book_evaluation) == 0) {
											output_header();
											output_parameters2_0(z);
										}

									}
								}
								else {
									printf("\nЗапис не знайдено.\n");
								}
							}
						}
					}
				}
			}
		}
	}
}

		
void output_parameters2_0(int z) {
	
	int temp;
	char spaces[9][50] = { "         ", "Автор книги                       ", "Iм'я книги                    ", "Видавництво          ", "Рік     ","Жанр          ","Походження          ","Наявність     ","Особиста оцінка книги" };
	for (int i = 0; i < 9; i++) {
		printf("|");
		fprintf(outputfile, "|");
		for (int j = 0; j <= strlen(spaces[i]); j++) {

			if (i == j) {
				printf("%d", z + 1);
				fprintf(outputfile, "%d", z + 1);
				int x = 1;
				if (z > 8) {
					x++;
				}
				temp = strlen(spaces[i]) - x;
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				temp = 0;
				break;
			}
			if (i == 1) {
				fread(library[z].book.authors, sizeof(char), 50, binary);
				printf("%s", library[z].book.authors);
				fprintf(outputfile, "%s", library[z].book.authors);
				temp = strlen(spaces[i]) - strlen(library[z].book.authors);
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				break;
			}

			if (i == 2) {
				printf("%s", library[z].book.name);
				fprintf(outputfile, "%s", library[z].book.name);
				temp = strlen(spaces[i]) - strlen(library[z].book.name);
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				break;
			}

			if (i == 3) {
				printf("%s", library[z].book.edition);
				fprintf(outputfile, "%s", library[z].book.edition);
				temp = strlen(spaces[i]) - strlen(library[z].book.edition);
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				break;
			}

			if (i == 4) {
				printf("%s", library[z].book.year);
				fprintf(outputfile, "%s", library[z].book.year);
				temp = strlen(spaces[i]) - strlen(library[z].book.year);
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				break;
			}

			if (i == 5) {
				printf("%s", library[z].section);
				fprintf(outputfile, "%s", library[z].section);
				temp = strlen(spaces[i]) - strlen(library[z].section);
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				break;
			}

			if (i == 6) {
				printf("%s", library[z].book_origin);
				fprintf(outputfile, "%s", library[z].book_origin);
				temp = strlen(spaces[i]) - strlen(library[z].book_origin);
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				break;
			}

			if (i == 7) {
				printf("%s", library[z].availability_of_a_book);
				fprintf(outputfile, "%s", library[z].availability_of_a_book);
				temp = strlen(spaces[i]) - strlen(library[z].availability_of_a_book);
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				break;
			}

			if (i == 8) {
				printf("%s", library[z].book_evaluation);
				fprintf(outputfile, "%s", library[z].book_evaluation);
				temp = strlen(spaces[i]) - strlen(library[z].book_evaluation);
				for (int k = 0; k < temp; k++) {
					printf(" ");
					fprintf(outputfile, " ");
				}
				break;
			}
		}
	}
	printf("|\n");
	fprintf(outputfile, "|\n");
	printf("|_________|__________________________________|______________________________|_____________________|________|______________|____________________|______________|_____________________|\n");
	fprintf(outputfile, "|_________|__________________________________|______________________________|_____________________|________|______________|____________________|______________|_____________________|\n");

}

void output()
{	
	char data_;
	while (!_kbhit) {}
	printf("\nВивести дані?(1 - з програми, 2 - ввести нові дані) ---> "); data_ = _getche();
	
	switch (data_) {
	case 49: {
		char i;
		while (!_kbhit) {}
		printf("\nБажаєте вивести всі дані? (1 - Так), (2 - за параметрами), (інше - вихід до меню): "); i = _getche();
		switch (i) {
		case 49: {
			readBinary();
			
			output_header();
			
			for (int z = 0; z < count_notes; z++) {
				output_parameters2_0(z);
			}

			fclose(binary);
			fclose(outputfile);
			exit();
			break;
		}
		case 50: {
			readBinary();

			parameters_();

			for (int q = 0; q < count_parameters; q++) {
				output_parameters(q);
			}

			fclose(binary);
			exit();
			break;
		}
		default: {
			exit();
			break;
		}
		}
		break;
	}
	case 50: {
		input();
		break;
	}
	}
}


void searching_() {	//функція сортування 
	readBinary();
	printf("\nЗапит на пошук.\n");
	if (count_notes == 0) {
		printf("В базі даних 0 записів.\n");
		exit();
	}
	parameters_();
	for (int b = 0; b < count_parameters; b++) {
		output_parameters(b);
	}
	fclose(binary);
	exit();
}

void editing_() {
	printf("\nЗапит на редагування.");
	if (count_notes == 0) {
		printf("В базі даних 0 записів.\n");
		exit();
	}
	int i;
	while(!_kbhit){}
	printf("\nЯкий запис редагувати? ---> "); scanf("%d", &i);	i = i - 1;
	printf("\tЗапис %d:\n", i + 1);
	printf("Інформація про книгу =>");
	printf(" Автор книги:");																    scanf("%s", library[i].book.authors);				 fwrite(library[i].book.authors, sizeof(char), 50, binary);
	printf("\t\t\tIм'я книги:");															    scanf("%s", library[i].book.name);					 fwrite(library[i].book.name, sizeof(char), 50, binary);
	printf("\t\t\tВидавництво:");															    scanf("%s", library[i].book.edition);				 fwrite(library[i].book.edition, sizeof(char), 50, binary);
	printf("\t\t\tРік:");																	    scanf("%s", library[i].book.year);					 fwrite(library[i].book.year, sizeof(char), 50, binary);
	printf("\t\t\tЖанр книги(детектив, фантастика, пригоди, роман, наука, гумор, фольклор):");  scanf("%s", library[i].section);				         fwrite(library[i].section, sizeof(char), 50, binary);
	printf("\t\t\tПоходження:");															    scanf("%s", library[i].book_origin);					 fwrite(library[i].book_origin, sizeof(char), 50, binary);
	printf("\t\t\tНаявність: ");															    scanf("%s", library[i].availability_of_a_book);		 fwrite(library[i].availability_of_a_book, sizeof(char), 50, binary);
	printf("\t\t\tОсобиста оцінка книги(0-10): ");											    scanf("%s", library[i].book_evaluation);				 fwrite(library[i].book_evaluation, sizeof(char), 50, binary);
	writeBinary();
	exit();
}

void delete_() {
	readBinary();
	printf("\nЗапит на видалення.\n");
	if (count_notes == 0) {
		printf("В базі даних 0 записів.\n");
		exit();
	}
	int i;
	while (!_kbhit) {}
	printf("\nЯкий запис видалити? ---> "); scanf("%d", &i); i = i - 1;
	for (int j = i; j < count_notes; j++) {
		library[j] = library[j + 1];	
		book[j] = book[j + 1];
	}
	count_notes--; writeBinary();
	fclose(binary); output();
}

void sorting_() {
	printf("\nЗапит на сортування.\n");
	if (count_notes == 0) {
		printf("В базі даних 0 записів.\n");
		exit();
	}
	int j;
	printf("\nЗ якого запису сортувати? ---> "); scanf("%d", &j);	j = j - 1;
	int sort;
	printf("\nЗа спаданням(1)\tЗа зростанням(2) ---> ");	scanf("%d", &sort);
	readBinary();
	parameters_();
	switch (sort) {
	case 1: {
		int fl;
		do {
			fl = 0;
			for (int z = 0; z < count_parameters; z++) {
				for (int i = j; i < count_notes; i++) {
					if (parameters[z] == 1) {
						if (strcmp(library[i].book.authors, library[i + 1].book.authors) < 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 2) {
						if (strcmp(library[i].book.name, library[i + 1].book.name) < 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 3) {
						if (strcmp(library[i].book.edition, library[i + 1].book.edition) < 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 4) {
						if (atoi(library[i].book.year) < atoi(library[i + 1].book.year)) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 5) {
						if (strcmp(library[i].section, library[i + 1].section) < 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 6) {
						if (strcmp(library[i].book_origin, library[i + 1].book_origin) < 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 7) {
						if (strcmp(library[i].availability_of_a_book, library[i + 1].availability_of_a_book) < 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 8) {
						if (atoi(library[i].book_evaluation) < atoi(library[i + 1].book_evaluation)) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
				}		
			}
		} while (fl);
		
		break;
	}
	case 2: {
		int fl;
		do {
			fl = 0;
			for (int z = 0; z < count_parameters; z++) {
				for (int i = j - 1; i < count_notes; i++) {
					if (parameters[z] == 1) {
						if (strcmp(library[i].book.authors, library[i + 1].book.authors) > 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 2) {
						if (strcmp(library[i].book.name, library[i + 1].book.name) > 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 3) {
						if (strcmp(library[i].book.edition, library[i + 1].book.edition) > 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 4) {
						if (atoi(library[i].book.year) > atoi(library[i + 1].book.year)) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 5) {
						if (strcmp(library[i].section, library[i + 1].section) > 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 6) {
						if (strcmp(library[i].book_origin, library[i + 1].book_origin) > 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 7) {
						if (strcmp(library[i].availability_of_a_book, library[i + 1].availability_of_a_book) > 0) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
					if (parameters[z] == 8) {
						if (atoi(library[i].book_evaluation) > atoi(library[i + 1].book_evaluation)) {
							library[count_notes] = library[i];
							library[i] = library[i + 1];
							library[i + 1] = library[count_notes];
							book[count_notes] = book[i];
							book[i] = book[i + 1];
							book[i + 1] = book[count_notes];
							fl = 1;
						}
					}
				}
			}
		} while (fl);
		break;
	}
	}
	writeBinary();
	output();
}

void inventory() {
	printf("\nЗапит на інвентаризацію.\n");
	if (count_notes == 0) {
		printf("В базі даних 0 записів.\n");
		exit();
	}
	readBinary();
	int inventory_book;
	printf("\nЯку інвентаризацію провести? (1 - в наявності; 2 - немає в наявності)---> "); scanf("%d", &inventory_book);
	switch (inventory_book) {
	case 1: 
		for (int i = 0; i < count_notes; i++) {
			if (strcmp("Есть", library[i].availability_of_a_book) == 0) {
				output_header();
				output_parameters2_0(i);
			}
		}
		break;
	case 2: 
		for (int i = 0; i < count_notes; i++) {
			if (strcmp("Нет", library[i].availability_of_a_book) == 0) {
				output_header();
				output_parameters2_0(i);
			}
		}
		break;
	}
	exit();
}