#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){

	SLLPool Tri(44);
Tri.PoolPrint();
	int *a = new(Tri) int;
Tri.PoolPrint();
	int *b = new(Tri) int;
Tri.PoolPrint();
	int *c = new(Tri) int;
	Tri.PoolPrint();
	delete a;
Tri.PoolPrint();
	a = new(Tri) int;
Tri.PoolPrint();
	delete b;
Tri.PoolPrint();
	b = new(Tri) int;
Tri.PoolPrint();
	delete b;
Tri.PoolPrint();
	delete a;
Tri.PoolPrint();
	a = new(Tri) int[5];
Tri.PoolPrint();
	delete[] a;
Tri.PoolPrint();
	delete c;
Tri.PoolPrint();
	a = new(Tri) int[9];
Tri.PoolPrint();
	delete a;
Tri.PoolPrint();
	a = new(Tri) int;
	Tri.PoolPrint();
	b = new(Tri) int[5];
Tri.PoolPrint();
	delete a;
Tri.PoolPrint();
	delete b;
	Tri.PoolPrint();
	return 0;
}