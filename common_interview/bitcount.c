#include <stdio.h>
int bitcount (int n ) {
	if ( n <= 0 ){
		return 0;
	} else {
		return  (n & 1) + bitcount(n >> 1 ); 
	}
}
void main2() {
	int a[3]= {1,2,3};
	int n1,n2 ;
	int *p;
	int **pp;
	p=a;
	pp=&p;
	*p+=1;
	printf ("%d %d %d \n",a[0],a[1],a[2]);
	p+=1;
	**pp-=1;
	printf ("%d %d %d \n",a[0],a[1],a[2]);
	*pp-=1;
	*p+=1;
	printf ("%d %d %d \n",a[0],a[1],a[2]);
	**pp+=1;
	printf ("%d %d %d \n",a[0],a[1],a[2]);
	n1=*p;
	n2 =**pp;
	printf ("n1=%d n2=%d\n",n1,n2);	
}
int func (int x ) {
	static int s = 0;
	while (x)
			s += x--;
	return s;
}
void func2 ()
{
	int n1,n2,n3;
	n1 =1;
	n2 = func(++n1);
	n3 =func(n2++);
	printf ("n1=%d n2=%d n3=%d\n",n1,n2,n3);	
}
int main (){
	short arr [] = {0x1,0x3,0x5,0x7,0x9,0xB,0xD};
	int n1 = sizeof (arr);
	int n2 = *(arr+2);
	int n3 = (arr+4)[1];
	int n4 = (int)&arr[3];
	int n5= *(short *)(((int *)arr)+2); 
	int n6= *(int *)(arr+1);
	printf ("%x %x %x %x %x %x\n",n1 , n2 ,n3,n4,n5,n6);

	int n = 0xF0FC;
	int count = bitcount (n);
	printf("%d\n",count);
	main2();
	func2();
	return 0;
}
