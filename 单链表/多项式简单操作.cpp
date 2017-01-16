/*
多项式的简单操作：多项式加法、多项式乘法
多项式加法只需要遍历两个非递增多项式链表，比较两个当前项的指数链接到结果链表即可
多项式乘法有三种算法，第一种遍历两个多项式相乘，将结果存储到一个多项式链表中，遍
厉该链表，寻找相同的多项式指数相加,复杂度O（M2N2）.第二种两个多项式相乘，将每个结
果MN取并集，复杂度为O（M2N）.第三种两个多项式相乘，排序合并同类项，复杂度O（MNlogMN）
*/
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>



typedef struct Node				//多项式结构
{
	int cofficient;				//系数
	int exponent;				//指数
	struct Node * next;
}Polynomial, *PtrPolynomial;


/*
创建多项式
*/
PtrPolynomial create_polynomial()
{
	int cofficient, exponent;
	PtrPolynomial pHead = (PtrPolynomial)malloc(sizeof(Polynomial));
	PtrPolynomial pCurrent = pHead;
	pHead->next = NULL;
	if (NULL == pHead)
	{
		printf("pHead malloc failed.\n");
		exit(-1);
	}

	while (1)
	{
		printf("Please input the cofficient(quit to input -1):\n");
		scanf("%d", &cofficient);
		if (cofficient == -1)
			break;

		printf("Please input the exponent(quit to input -1):\n");
		scanf("%d", &exponent);
		if (exponent == -1)
			break;

		PtrPolynomial pNew = (PtrPolynomial)malloc(sizeof(Polynomial));
		if (NULL == pNew)
		{
			printf("pNew malloc failed.\n");
			exit(-1);
		}
		pNew->cofficient = cofficient;
		pNew->exponent = exponent;
		pNew->next = pCurrent->next;
		pCurrent->next = pNew;
		pCurrent = pCurrent->next;
	}

	return pHead;
}

/*
将多项式的指数进行非递增排序
*/
void sort_cofficient(PtrPolynomial pHead)
{
	int temp;

	PtrPolynomial p, q;
	for (p = pHead->next; p != NULL; p = p->next)
		for (q = p->next; q != NULL; q = q->next)
		{
			if (p->exponent < q->exponent)
			{
				//交换两个多现式的指数
				temp = p->exponent;
				p->exponent = q->exponent;
				q->exponent = temp;

				//交换两个多现式的系数
				temp = p->cofficient;
				p->cofficient = q->cofficient;
				q->cofficient = temp;
			}
		}
		//if (!swap)	//如果未发生过交换则说明是非递增的
		//	break;
	return;
}

/*
多项式加法
*/
PtrPolynomial add_polynomial(PtrPolynomial p1, PtrPolynomial p2, PtrPolynomial p3)
{
	PtrPolynomial pCurrent1 = p1->next, pCurrent2 = p2->next, pCurrent = p3;
	
	while (NULL != pCurrent1 && NULL != pCurrent2)
	{
		PtrPolynomial temp;
		if (pCurrent1->exponent > pCurrent2->exponent)		//第一个多项式的项系数大于第二个
		{
			temp = pCurrent1->next;
			pCurrent1->next = pCurrent->next;
			pCurrent->next = pCurrent1;
			free(pCurrent1);

			//下一个要计算的多项式
			pCurrent1 = temp;
		}
		else if (pCurrent1->exponent < pCurrent2->exponent)	//第一个多项式的项系数小于第二个
		{
			temp = pCurrent2->next;
			pCurrent2->next = pCurrent->next;
			pCurrent->next = pCurrent2;
			free(pCurrent2);

			//下一个要计算的多项式
			pCurrent2 = temp;
		}
		else							//第一个多项式的项系数等于第二个
		{
			int sum = pCurrent1->cofficient + pCurrent2->cofficient;

			//两个多项式系数相加不为0,将结果存储在pCurrent中
			//否则两个计算多项式都向后移动
			if (sum != 0)
			{
				temp = pCurrent1->next;
				pCurrent1->cofficient = sum;
				pCurrent1->next = pCurrent->next;
				pCurrent->next = pCurrent1;

				pCurrent1 = temp;

				temp = pCurrent2->next;
				free(pCurrent2);
				pCurrent2 = temp;
			}
			else
			{
				temp = pCurrent1;
				pCurrent1 = pCurrent1->next;
				free(temp);
				temp = pCurrent2;
				pCurrent2 = pCurrent2->next;
				free(temp);
			}

		}
		pCurrent = pCurrent->next;
	}

	//如果第一个多项式不为空，则将其链接到pCurrent后
	while (NULL != pCurrent1)
	{
		PtrPolynomial temp;
		temp = pCurrent1->next;
		pCurrent1->next = pCurrent->next;
		pCurrent->next = pCurrent1;
		pCurrent1 = temp;
	}
	//如果第二个多项式不为空，则将其链接到pCurrent后
	while (NULL != pCurrent2)
	{
		PtrPolynomial temp;
		temp = pCurrent2->next;
		pCurrent2->next = pCurrent->next;
		pCurrent->next = pCurrent2;
		pCurrent2 = temp;
	}
	
	return p3;
}

/*
多项式乘法（第一种）
*/
PtrPolynomial multi_polynomial(PtrPolynomial p1, PtrPolynomial p2, PtrPolynomial p3)
{
	PtrPolynomial pCurrent1, pCurrent2;
	for(pCurrent1=p1->next;NULL != pCurrent1;pCurrent1=pCurrent1->next)
		for (pCurrent2 = p2->next; NULL != pCurrent2; pCurrent2 = pCurrent2->next)
		{
			//申请结果存储空间
			PtrPolynomial pResult = (PtrPolynomial)malloc(sizeof(Polynomial));
			pResult->next = NULL;
			if (NULL == pResult)
			{
				printf("pResult malloc failed.");
				exit(-1);
			}

			//进行多项式结果运算
			PtrPolynomial pCurrent=p3;
			pResult->cofficient = pCurrent1->cofficient * pCurrent2->cofficient;
			pResult->exponent = pCurrent1->exponent + pCurrent2->exponent;
			pResult->next = pCurrent->next;
			pCurrent->next = pResult;
			pCurrent = pCurrent->next;
		}

	//遍历多项式乘积结果链表
	//将exponent指数相同多项式合并
	PtrPolynomial pTraverse, pSearch, pOneResult;
	for (pTraverse = p3->next; NULL != pTraverse; pTraverse = pTraverse->next)
	{
		pOneResult = pTraverse;
		for (pSearch = pTraverse; NULL != pSearch; pSearch = pSearch->next)
		{
			if (NULL != pSearch->next && pSearch->next->exponent == pOneResult->exponent)
			{
				PtrPolynomial temp;
				pOneResult->cofficient = pOneResult->cofficient + pSearch->next->cofficient;
				temp = pSearch->next;
				pSearch->next = temp->next;
				free(temp);
			}
		}
		printf("cofficient=%d, exponent=%d\n", pOneResult->cofficient, pOneResult->exponent);
	}
	
	return p3;
}




void main()
{
	PtrPolynomial p1, p2, p3;
	p3 = (PtrPolynomial)malloc(sizeof(Polynomial));
	p3->next = NULL;

	//创建多项式
	printf("创建第一个多项式\n");
	p1 =create_polynomial();
	printf("创建第二个多项式\n");
	p2 = create_polynomial();

	//多项式排序
	printf("第一个多项式排序\n");
	sort_cofficient(p1);
	printf("第二个多项式排序\n");
	sort_cofficient(p2);

	//多项式的运算，注意这两个运算不能同时运行，需要注释掉另一个
	printf("多项式加法\n");
	PtrPolynomial result= add_polynomial(p1, p2, p3), show=result->next;
	while (NULL != show)
	{
		printf("%dX%d+", show->cofficient, show->exponent);
		show = show->next;
	}
	printf("\n");

	printf("多项式乘法\n");
	PtrPolynomial result2 = multi_polynomial(p1, p2, p3), show2=result2->next;
	while (NULL != show2)
	{
		printf("%dX%d+", show2->cofficient, show2->exponent);
		show2 = show2->next;
	}
	printf("\n");
}
