#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tel
{
	char *name;
	char *tel_no;
	char *birth;
};

typedef struct tel TEL;

void insert(TEL **tel_list, int count);
void print_all(TEL **tel_list, int count);
void delete_tel(TEL **tel_list, int count);
void find_by_birth(TEL **tel_list, int count);

int main()
{
	int max_num, count = 0, n, i;
	TEL **tel_list = NULL;

	printf("Max_num:");
	scanf("%d", &max_num);

	tel_list = (TEL **)malloc(max_num * sizeof(TEL *));

	while (1)
	{
		printf("*****Menu*****\n");
		printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.Exit>\n");
		printf("Enter_the_menu_number:");
		scanf("%d", &n);

		switch (n)
		{
		case 1:

			if (count < max_num)
			{
				insert(tel_list, count);

				count++;
			}

			else
			{
				printf("OVERFLOW\n");
			}

			break;

		case 2:

			if (count != 0)
			{
				print_all(tel_list, count);
			}

			break;

		case 3:

			if (count != 0)
			{
				delete_tel(tel_list, count);

				count--;
			}

			else
			{
				printf("NO MEMBER\n");
			}

			break;

		case 4:
			find_by_birth(tel_list, count);
			break;

		case 5:

			for (i = 0; i < count; i++)
			{
				free(tel_list[i][0].name);
				free(tel_list[i][0].tel_no);
				free(tel_list[i][0].birth);
			}

			for (i = 0; i < count; i++)
			{
				free(tel_list[i]);
			}

			free(tel_list);

			return 0;
		}

	}

	return 0;
}

void insert(TEL **tel_list, int count)
{
	int i, loc = count, len;
	char str[100];

	tel_list[loc] = (TEL *)malloc(sizeof(TEL));

	printf("Name:");
	scanf("%s", str);

	for (i = 0; i < count; i++)
	{
		if (strcmp(tel_list[i][0].name, str) > 0)
		{
			loc = i;

			break;
		}
	}

	for (i = count; i > loc; i--)
	{
		tel_list[i][0].name = (char *)malloc((strlen(tel_list[i - 1][0].name) + 1) * sizeof(char));
		strcpy(tel_list[i][0].name, tel_list[i - 1][0].name);

		tel_list[i][0].tel_no = (char *)malloc((strlen(tel_list[i - 1][0].tel_no) + 1) * sizeof(char));
		strcpy(tel_list[i][0].tel_no, tel_list[i - 1][0].tel_no);

		tel_list[i][0].birth = (char *)malloc((strlen(tel_list[i - 1][0].birth) + 1) * sizeof(char));
		strcpy(tel_list[i][0].birth, tel_list[i - 1][0].birth);
	}

	len = strlen(str);
	tel_list[loc][0].name = (char *)malloc((len + 1) * sizeof(char));
	strcpy(tel_list[loc][0].name, str);

	printf("Phone_number:");
	scanf("%s", str);
	len = strlen(str);
	tel_list[loc][0].tel_no = (char *)malloc((len + 1) * sizeof(char));
	strcpy(tel_list[loc][0].tel_no, str);

	printf("Birth:");
	scanf("%s", str);
	len = strlen(str);
	tel_list[loc][0].birth = (char *)malloc((len + 1) * sizeof(char));
	strcpy(tel_list[loc][0].birth, str);

	printf("<<%d>> \n", count + 1);
}

void print_all(TEL **tel_list, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		printf("%s %s %s\n", tel_list[i][0].name, tel_list[i][0].tel_no, tel_list[i][0].birth);
	}
}

void delete_tel(TEL **tel_list, int count)
{
	int i, loc = -1;
	char str[100];

	printf("Name:");
	scanf("%s", str);

	for (i = 0; i < count; i++)
	{
		if (strcmp(tel_list[i][0].name, str) == 0)
		{
			loc = i;

			break;
		}
	}

	if (loc != -1)
	{
		for (i = loc; i < count - 1; i++)
		{
			tel_list[i][0].name = (char *)malloc((strlen(tel_list[i + 1][0].name) + 1) * sizeof(char));
			strcpy(tel_list[i][0].name, tel_list[i + 1][0].name);

			tel_list[i][0].tel_no = (char *)malloc((strlen(tel_list[i + 1][0].tel_no) + 1) * sizeof(char));
			strcpy(tel_list[i][0].tel_no, tel_list[i + 1][0].tel_no);

			tel_list[i][0].birth = (char *)malloc((strlen(tel_list[i + 1][0].birth) + 1) * sizeof(char));
			strcpy(tel_list[i][0].birth, tel_list[i + 1][0].birth);
		}

		free(tel_list[count - 1][0].name);
		free(tel_list[count - 1][0].birth);
		free(tel_list[count - 1][0].tel_no);

		free(tel_list[count - 1]);
	}
}

void find_by_birth(TEL **tel_list, int count)
{
	int i, month;

	printf("Birth:");
	scanf("%d", &month);

	for (i = 0; i < count; i++)
	{
		if (month == (tel_list[i][0].birth[4] - '0') * 10 + (int)(tel_list[i][0].birth[5]) - '0')
		{
			printf("%s %s %s\n", tel_list[i][0].name, tel_list[i][0].tel_no, tel_list[i][0].birth);
		}
	}
}