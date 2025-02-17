//#include <iostream>
#include <cstdlib>//malloc
#include <cstdio>//printf
//#include <typeid>//typeid(a).name()
#include <assert.h>
//using namespace std;
int main(){
//int *ptr;ptr = (int *)malloc(5 * sizeof(int));
int a = 0xA; 
int *b=&a; assert(b==&a);  printf("b:%p &a:%p deref b:%x\u000a",b,&a,*b);
int **c=&b;assert(c==&b);  printf("c:%p &b:%p deref c:%p derefDeref c:%x \u000a",c,&b,*c,**c);
//printf("%lx \u000a",(ssize_t)**c);
//printf("%d \u000a",/*(void**)*/**c);
//printf("%p \u000a",**c);
}//main
