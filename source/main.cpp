#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){
	
	DLPool z(20);

	int* k = new(z) int;

	z.PoolPrint();

	return 0;
}