#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//100�� ������ ������ ����. �ٸ� ���� ������ ���� ������ �� ���� ��Ȳ�̴�. 
//id�� score�� �߰� �Ҷ����� score�� �������� �ٷιٷ� sorting ���ִ� ���α׷� 

//�� �Ʒ��� �Է� ���� �ּ����� �־�����ϴ�.

//��Ģ
//1. �Է� ĭ�� 2�ڸ� �̻��� ���� or ���� ������ �� �˴ϴ�.
//2. score ĭ�� ���� ������ �� �˴ϴ�.
//3. �� �ܿ� �������� �����Է��ε� �����Է�, �����Է��ε� �����Է� �����մϴ�.

typedef struct Node
{
	int id;
	int score;
	struct Node *next;
} Node;

Node *getnode();
void initList(Node *header);
int check_id(Node *header, int id); //�̹� �Է��� id�� �Է��ϸ� ������ �����. ���� �����ϰ� �; �׷��ٸ� id�� �����ϰ� �ٽ� �Է��϶�� ������.
void add(Node *header, int id, int score);
void delete(Node *header, int id);
int get(Node *header, int id);
void print(Node *header);

int main()
{
	int id, score;
	int flag = 1;
	char ch;
	Node *header = getnode();

	initList(header);

	printf("�߰�:A, ����:D, ��ȸ:G, ���:P, ����:E\n");

	while (flag == 1)
	{
		printf("\n�Է�: ");
		scanf("%c", &ch);

		switch (ch)
		{
		case 'A':
			printf("id: ");
			scanf("%d", &id);
			if (check_id(header, id) == 0) { break; }
			printf("score: ");
			scanf("%d", &score);
			if (score < 0 || score > 100) { printf("score�� ������ 0 �̻�, 100 �����Դϴ�.\nó�� (���ĺ�)�Է����� ���ư��ϴ�.\n"); break; } //�̰� �³�?
			add(header, id, score);
			break;
		case 'D':
			printf("id: ");
			scanf("%d", &id);
			delete(header, id);
			break;
		case 'G':
			printf("id: ");
			scanf("%d", &id);
			if (get(header, id) != -1) { printf("%d �л��� ������ %d�� �Դϴ�.\n", id, get(header, id)); }
			break;
		case 'P':
			print(header);
			break;
		case 'E':
			flag = 0;
			break;
		default:
			printf("�߸��� �Է��Դϴ�.\n");
		}

		getchar();
	}

	return 0;
}

Node *getnode()
{
	Node *makeNode = (Node *)malloc(sizeof(Node));

	return makeNode;
}

void initList(Node *header)
{
	header->next = NULL;
}

int check_id(Node *header, int id)
{
	int flag = 1;
	Node *cur = header->next;

	while (cur != NULL)
	{
		if (id == cur->id)
		{
			flag = 0;

			printf("�̹� �Էµ� id�Դϴ�. id�� ���� score�� �����ϰ� �����ôٸ� id�� ���� �� �ٽ� �Է����ּ���. ó�� (���ĺ�)�Է����� ���ư��ϴ�.\n");
			printf("ó�� (���ĺ�)�Է����� ���ư��ϴ�.\n");

			break;
		}

		cur = cur->next;
	}

	return flag;
}

void add(Node *header, int id, int score)
{
	Node *before = header;
	Node *cur = header->next;
	Node *newNode = getnode();

	newNode->id = id;
	newNode->score = score;

	while (cur != NULL)
	{
		if (score > cur->score)
		{
			before->next = newNode;
			newNode->next = cur;

			break;
		}

		if (score == cur->score && id < cur->id)//�������̸� id�� ������ �켱����
		{
			before->next = newNode;
			newNode->next = cur;

			break;
		}

		before = before->next;
		cur = cur->next;
	}

	if (cur == NULL)
	{
		before->next = newNode;

		newNode->next = NULL;
	}
}

void delete(Node *header, int id)
{
	Node *before = header;
	Node *cur = header->next;

	while (cur != NULL)
	{
		if (id == cur->id)
		{
			before->next = cur->next;

			printf("%d���� %d �л��� �����Ͱ� �����Ǿ����ϴ�.\n", cur->score, cur->id);

			free(cur);

			break;
		}

		before = before->next;
		cur = cur->next;
	}

	if (cur == NULL)
	{
		printf("�Է��Ͻ� id�� �������� �ʽ��ϴ�.\n");
	}
}

int get(Node *header, int id)
{
	Node *cur = header->next;

	while (cur != NULL)
	{
		if (id == cur->id)
		{
			return cur->score;
		}

		cur = cur->next;
	}

	printf("�Է��Ͻ� id�� �������� �ʽ��ϴ�.\n");

	return -1;
}

void print(Node *header)
{
	Node *cur = header->next;

	printf("---������������ ���---\n");

	while (cur != NULL)
	{
		printf("%d %d��\n", cur->id, cur->score);

		cur = cur->next;
	}

	printf("-----------------------\n\n");
}

/*
A
19011712
100
A
19011712
A
19011711
80
A
19011710
80
D
19011718
A
19011812
30
P
D
19011812
G
19011719
A
19011538
45
P
E
*/