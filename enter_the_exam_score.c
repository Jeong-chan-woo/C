#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//100점 만점인 시험을 본다. 다만 시험 응시자 수를 예측할 수 없는 상황이다. 
//id와 score를 추가 할때마다 score를 기준으로 바로바로 sorting 해주는 프로그램 

//맨 아래에 입력 예시 주석으로 넣어놨습니다.

//규칙
//1. 입력 칸에 2자리 이상의 문자 or 숫자 넣으면 안 됩니다.
//2. score 칸에 문자 넣으면 안 됩니다.
//3. 그 외에 문제에서 정수입력인데 문자입력, 문자입력인데 정수입력 금지합니다.

typedef struct Node
{
	int id;
	int score;
	struct Node *next;
} Node;

Node *getnode();
void initList(Node *header);
int check_id(Node *header, int id); //이미 입력한 id를 입력하면 오류를 띄워줌. 만약 수정하고 싶어서 그랬다면 id를 삭제하고 다시 입력하라고 말해줌.
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

	printf("추가:A, 삭제:D, 조회:G, 출력:P, 종료:E\n");

	while (flag == 1)
	{
		printf("\n입력: ");
		scanf("%c", &ch);

		switch (ch)
		{
		case 'A':
			printf("id: ");
			scanf("%d", &id);
			if (check_id(header, id) == 0) { break; }
			printf("score: ");
			scanf("%d", &score);
			if (score < 0 || score > 100) { printf("score의 범위는 0 이상, 100 이하입니다.\n처음 (알파벳)입력으로 돌아갑니다.\n"); break; } //이거 맞나?
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
			if (get(header, id) != -1) { printf("%d 학생의 점수는 %d점 입니다.\n", id, get(header, id)); }
			break;
		case 'P':
			print(header);
			break;
		case 'E':
			flag = 0;
			break;
		default:
			printf("잘못된 입력입니다.\n");
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

			printf("이미 입력된 id입니다. id에 대한 score을 수정하고 싶으시다면 id를 삭제 후 다시 입력해주세요. 처음 (알파벳)입력으로 돌아갑니다.\n");
			printf("처음 (알파벳)입력으로 돌아갑니다.\n");

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

		if (score == cur->score && id < cur->id)//동점자이면 id가 작은게 우선순위
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

			printf("%d점인 %d 학생의 데이터가 삭제되었습니다.\n", cur->score, cur->id);

			free(cur);

			break;
		}

		before = before->next;
		cur = cur->next;
	}

	if (cur == NULL)
	{
		printf("입력하신 id는 존재하지 않습니다.\n");
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

	printf("입력하신 id는 존재하지 않습니다.\n");

	return -1;
}

void print(Node *header)
{
	Node *cur = header->next;

	printf("---내림차순으로 출력---\n");

	while (cur != NULL)
	{
		printf("%d %d점\n", cur->id, cur->score);

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