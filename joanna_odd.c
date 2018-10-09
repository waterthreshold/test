#include <stdlib.h>
#include <stdio.h>
int main ()
{
	
	unsigned long long int n;
	while (scanf ("%d",&n) && n)
	{
		unsigned long long int num;
		int i;
		unsigned long long int sum=0;
		num=((1+n)*((n-1)/2+1))/2; 
		for (i =0;i<3;i++)
			sum += (1+2*(num-1-i));
			printf ("%llu\n",sum);
	}
	//git hub test
	return 0;
}
