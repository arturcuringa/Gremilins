#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){
	
	SLLPool p(400);
	SLLPool q(800);
	int* a, *b, *c ,*d, *e, *f , *g;

	a = new(p) int;
	b = new(p) int;
	c = new(p) int;
	d = new(p) int;
	e = new(p) int;
	f = new(p) int;
	g = new(p) int;


	*a = 5;
	*b = 6;
	*c = 7;
	*d = 8; 
	*e = 9;
	*f = 10;
	*g = 11;


	std::cout<<*a<<"\n";
	std::cout<<*b<<"\n";
	std::cout<<*c<<"\n";
	std::cout<<*d<<"\n";
	std::cout<<*e<<"\n";
	std::cout<<*f<<"\n";
	std::cout<<*g<<"\n";


	int* vec = new(q) int[10];

	for (int i = 0; i < 10; ++i)
	{
		vec[i] = i;
	}

	for (int i = 0; i < 10; ++i)
	{
		std::cout<<"vec["<<i<<"]: "<<i<<"\n";
	}
	int * k = new int;
	delete k;
	delete a;
	delete b;

	int *j = new(p) int[5];

	delete[] j;

	DLPool z(400);
	z.PoolPrint();
	int* zaf = new(z) int[10];
	z.PoolPrint();
	int* zaf2 = new(z) int;
	z.PoolPrint();
	int* zaf3 = new(z) int;
	z.PoolPrint();
	int* zaf4 = new(z) int[10];
	z.PoolPrint();
	delete[] zaf;
	z.PoolPrint();
	delete zaf3;
	z.PoolPrint();
	std::cout<<"\n\n\n\n";
	SLLPool n(20);


	int* zap = new(n) int[5];
	n.PoolPrint();
	delete[] zap;
	n.PoolPrint();
	std::cout<<"\n\n\n\n";
	
	int* zaf3ret = new(z) int;
	z.PoolPrint();
	std::cout<<"\n\n\n\n";
	DLPool u(400);
	u.PoolPrint();
	int* Hydeoshi = new(u) int[10];
	u.PoolPrint();
	int* Yuki = new(u) int;
	u.PoolPrint();
	int* Yuji = new(u) int[11];
	u.PoolPrint();
	int* Himeji = new(u) int;
	u.PoolPrint();

	delete Yuki;
	u.PoolPrint();
	delete[] Yuji;

	u.PoolPrint();



	return 0;
}