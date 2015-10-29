#include <iostream>
#include "memory.h"
#include "Operators.h"



int main (){
	
	SLLPool p(200);

	int *k;

	k = new(p) int;

	*k = 5;

	std::cout<<*k<<"\n";

	return 0;
}