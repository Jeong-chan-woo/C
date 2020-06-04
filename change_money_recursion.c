#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//동네 구멍가게(현금거래가 주 거래수단)에서
//거스름돈을 최소한의 화폐로 주는(예를 들어 6000원을 거슬러 주어야하면 "1000원짜리 6개"가 아니라 "5000원짜리 1개, 1000원짜리 1개"로 거슬러줌)
//프로그램을 재귀로 만드려한다.

//규칙->지켜지지 않을 경우 프로그램 종료
//1. 손님이 총 금액의 이상의 금액을 지불해야한다.
//2. 2020년 대한민국의 현행 화폐로만 지불되어야한다.->(50000, 10000, 5000, 1000, 500, 100, 50, 10)원만 가능, (1, 5)원 불가능

int rec(change, money);

int main()
{
	int price, payment, change; //손님이 지불해야할 금액, 손님이 주인에게 준 금액, 주인이 손님에게 주어야할 거스름돈
	int money = 50000; //money는 현행 화폐->50000원부터 시작해서 10원까지 for문을 통해 점점 액수가 내려갈 것임.
	int i;

	printf("물건의 총 가격(손님이 지불해야할 금액)을 입력하시오: ");
	scanf("%d", &price);
	if (price % 10 != 0)
	{
		printf("현행 화폐로는 불가능한 금액입니다.\n");
		printf("프로그램을 종료합니다.");

		return 0;
	}

	printf("손님이 주인에게 지불한 금액을 입력하시오: ");
	scanf("%d", &payment);
	if (payment % 10 != 0)
	{
		printf("손님, 현행 화폐로는 불가능한 지불 금액입니다.\n");
		printf("프로그램을 종료합니다.");

		return 0;
	}

	if (price > payment)
	{
		printf("손님, 돈을 더 지불해야합니다\n");
		printf("프로그램을 종료합니다.");
	}

	else if (price == payment)
	{
		printf("손님, 딱 맞게 지불하셔서 거스름돈은 없습니다.");
	}

	else
	{
		change = payment - price; // (거슬러줄 금액) = (주인에게 지불한 금액) - (원래 지불 해야할 금액)

		for (i = 0; i < 8; i++)
		{//50000->10000->5000->1000->500->100->50->10 이렇게 "나누기 5"->"나누기 2"->"나누기 5"->"나누기 2"가 규칙적으로 반복된다.
			printf("%d원권: %d개\n", money, rec(change, money));

			change %= money;

			if (i % 2 == 0)
			{
				money /= 5;
			}

			else
			{
				money /= 2;
			}
		}
	}

	return 0;
}

int rec(change, money)
{
	if (change / money == 0) //base case
	{
		return 0;
	}

	else //recursion
	{
		return 1 + rec(change - money, money);
	}
}