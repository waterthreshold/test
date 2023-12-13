#include<stdlib.h>
#include<stdio.h>
//#void initial (T_ARRAYLIST t ){
//	t.length =0 ;
//	memset (t.arr , 0 , sizeof (t.arr));
//}
//#pragma pack(1)
void add (){
	return;
}
struct Node {
    int data;
    struct Node *next;
};

    
typedef struct node {
	int data;
} T_NODE;
struct { 
    short s[5];
    union { 
         float y; 
         long z; 
    }u; 
} t;
typedef struct array_list {
	int length ;
	T_NODE arr[10000];
//	void (*initial) (T_ARRAYLIST);
} T_ARRAYLIST;
char *my_strcat (char *dst, const char *src) {
	int i=0,index;
	while ( *(dst+i) != '\0' ){
		i++;
	}	
	index=i, i=0;
	while (*(src+i) != '\0'){
		*(dst+index+i)= *(src+i);
		i++;
	}
	return dst;
}

char *my_strcpy (char *dest,const char *src) {
	int i=0;
	while ( *(src+i) != '\0') {
		*(dest+i) = *(src+i);
		i++;
	}
	return dest;
}
//hunt 
void hunt (int n){
	if ( n % 6 == 0 ){
		printf ("number %d can divide by 3 and 2\n",n);
	}	
	else if ( n % 3 == 0 ) {
		printf ("number %d can divide by 3\n",n);	
	}
   	else if ( n % 2 == 0){
		printf ("number %d can divide by 2\n",n);
	}
   	else {
		printf ("number %d cannot divide by 3 and 2\n",n);
	}
}
void swap (int *m , int *n) {
		*m = *m+ *n;
		*n = *m - *n;
		*m = *m-*n;
}	

int gcd (int m , int n) {
 	int r = m % n;
	if ( r == 0 ) {
		return n ;
	} else {
		return gcd (n,r);
	}

}
int fib (int index ) {
	if ( index == 1  || index == 2 ) 
		return 1;
	else 
		return fib(index - 2) + fib (index - 1 );
}
int fib_loop (int index ){
	int m,n,tmp;
	 m=n=1 ;
	if ( index ==1 || index  == 2 ) {
		return m;
	}
	int i = 2 ;
	while ( i++ < index ) {
		tmp = m + n , m=n ,n=tmp  ;
	}
	return n ;
}

int main (int argc ,char *argv[]){
	char dst [64] ={0};
	char src[64] = "Hello world";
	int a = 12 , b = 18 ;	
	my_strcpy(dst,src);
	my_strcat(src,dst);
	printf ("%s\n",src);
	printf("%s\n",dst);
	hunt (64);	
	printf ("before swap %d and %d \n", a ,b );
	
	swap ( &a , &b );
	printf ("after swap %d and %d \n", a ,b );
	int n =gcd (a,b );
	printf ("gcd (%d,%d)=%d\n" , a ,b ,n );
	n =	fib (10);
	printf ("fib =  %d\n" ,n );
	n =	fib_loop (10);
	printf ("fib =  %d\n" ,n );
	printf ("%d\n",sizeof(t));	
	return 0;
}
