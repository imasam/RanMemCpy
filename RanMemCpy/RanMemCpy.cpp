/*******胡哲 2014301550147 计科5班*******/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX 100
#define BUFFERLENGTH 9

void swap(int s[], int i, int j)
{
	int temp;
	temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}

void QuickSort(int s[], int low, int high)
{
	int i;
	int last;
	if (low<high)
	{
		last = low;

		for (i = low + 1; i <= high; i++)
		{
			if (s[i]<s[low])
				swap(s, ++last, i);
		}

		swap(s, last, low);
		QuickSort(s, low, last - 1);
		QuickSort(s, last + 1, high);
	}
}

void *RanMemCpy(void *dst, const void *src, int pos, size_t size)
/*dst：目标地址
src：源地址
pos：拷贝起始位置
size：需拷贝的字节数*/
{
	const char *psrc;
	char *pdst;
	int i, j;
	int num;
	int len = size;
	char tmp[MAX];
	char connect[MAX] = {};
	char moved[MAX];
	int rec2int[8] = { 0 };
	int orderedInt[8];

	//无效地址
	if (dst == NULL || src == NULL)
	{
		printf("WRONG ADDRESS!\n");
		exit(0);
	}

	//防止缓冲区溢出
	if ((pos + size) > BUFFERLENGTH - 1)
	{
		printf("BUFFER OVERFLOW!\n");
		exit(0);
	}

	psrc = (char *)src + pos;
	pdst = (char *)dst;

	int rand1 = rand() % 6 + 1;//[1,6] 用于异或的随机数
	printf("\n用于异或的随机数rand1=%d\n", rand1);
	while (size--)
	{
		num = (*psrc - '0') ^ rand1;//异或打乱顺序
		if (num == 0)
		{
			tmp[0] = 48; tmp[1] = 48; tmp[2] = 48; tmp[3] = '\0';//48为0的ASCII码
		}
		else if (num == 1)
		{
			tmp[0] = 48; tmp[1] = 48; tmp[2] = '1'; tmp[3] = '\0';
		}
		else if (num == 2)
		{
			tmp[0] = 48; tmp[1] = '1'; tmp[2] = 48; tmp[3] = '\0';
		}
		else if (num == 3)
		{
			tmp[0] = 48; tmp[1] = '1'; tmp[2] = '1'; tmp[3] = '\0';
		}
		else
			itoa(num, tmp, 2);
		
		//printf("%s\n", tmp);
		strcat(connect, tmp);
		
		psrc++;	
	}
	printf("操作后连接为长串：\n%s\n", connect);

	int rand2 = rand() % (len * 3);//平移随机数
	printf("\n用于右移的随机数rand2=%d\n", rand2);
	//右移rand2
	for (i = 0; i < rand2; i++)
		moved[i] = connect[len * 3 - rand2 + i];
	for (i = rand2; i < len * 3; i++)
		moved[i] = connect[i - rand2];
	moved[i] = '\0';
	printf("右移%d位后:\n%s\n", rand2, moved);

	//每3位分割并转换为十进制
	for (i = 0; i < len * 3; i += 3)
		for (j = i; j < i + 3; j++)
		{
			rec2int[i / 3] += (moved[j] - '0') * pow(2, 2 - (j % 3));
		}

	//测试转换结果
	printf("\n划分并转换为十进制后:\n");
	for (i = 0; i < len; i++)
		printf("rec2int[%d]=%d\n", i, rec2int[i]);
	printf("\n");


	for (i = 0; i < len; i++)
		orderedInt[i] = rec2int[i];

	QuickSort(orderedInt, 0, len - 1);
	//测试排序结果
	printf("排序结果:\n");
	for (i = 0; i < len; i++)
	{
		printf("orderedInt[%d]=%d\n", i, orderedInt[i]);
	}

	//有地址重叠则自后向前拷贝
	if ((src < dst) && ((char *)src + pos + size) > (char *)dst)
	{
		psrc = (char *)src + pos + size - 1;
		pdst = (char *)dst + size - 1;
		for (i = 0; i < len; i++)
		{
			for (j = 0; j < len; j++)
				if (rec2int[i] == orderedInt[j])
					*pdst-- = j + pos + '0';
		}
		*pdst = '\0';
	}
	else
	{
		psrc = (char *)src + pos;
		pdst = (char *)dst;
		for (i = 0; i < len; i++)
		{
			for (j = 0; j < len; j++)
				if (rec2int[i] == orderedInt[j])
					*pdst++ = j + pos + '0';
		}
		*pdst = '\0';
	}
}

int main()
{
	srand(int(time(0)));
	char src[MAX] = "01234567";
	char dst[BUFFERLENGTH];
	int pos, size;

	printf("拷贝起始位置pos:");//拷贝起始位置
	scanf("%d", &pos);
	printf("需拷贝的字节数size:");//需拷贝的字节数
	scanf("%d", &size);

	//乱序拷贝所选部分
	//无地址重叠
	RanMemCpy(dst, src, pos, size);
	printf("\n拷贝后目标地址内容为:%s\n", dst);
	
	//有地址重叠
	/*
	RanMemCpy(src+1, src, pos, size);
	printf("\n拷贝后目标地址内容为:%s\n", src);
	*/
}