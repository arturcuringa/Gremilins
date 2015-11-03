#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){

	SLLPool Duo(28);
	Duo.PoolPrint();
	int *a = new(Duo) int;
	Duo.PoolPrint();
	int *b = new(Duo) int;
	Duo.PoolPrint();
	delete[] a;
Duo.PoolPrint();
	a = new(Duo) int;
Duo.PoolPrint();
	delete[] b;
Duo.PoolPrint();
	b = new(Duo) int;
Duo.PoolPrint();
	delete[] b;
Duo.PoolPrint();
	delete[] a;
Duo.PoolPrint();
	a = new(Duo) int[5];
Duo.PoolPrint();
	delete[] a;
Duo.PoolPrint();
	return 0;
}