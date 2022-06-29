#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int dist = i < 3 ? i : 6 - i;
			if (j == 3 || j == 3 - dist || j == 3 + dist)
			{
				printf("*");
			}
			else
			{
				printf("#");
			}
		}
		printf("\n");
	}
}