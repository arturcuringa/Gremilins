#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){
	DLPool z(400);

int *k = new(z) int;


	return 0;
}