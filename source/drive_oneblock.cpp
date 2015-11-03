#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){

	SLLPool One(12);
	One.PoolPrint();
	int *a = new(One) int;
	One.PoolPrint();
	delete[] a;
	One.PoolPrint();
	return 0;
}