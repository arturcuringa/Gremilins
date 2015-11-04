#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){

	SLLPool Tri(44);
	std::cout<<"Creating Pool: \n";
	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	int *a = new(Tri) int;
Tri.PoolPrint();
	std::cout<<"Alocando um bloco\n";
	int *b = new(Tri) int;
Tri.PoolPrint();
std::cout<<"Alocando um bloco\n";
	int *c = new(Tri) int;
	Tri.PoolPrint();
std::cout<<"Deletando um bloco\n";
	delete a;
Tri.PoolPrint();
std::cout<<"Alocando um bloco\n";
	a = new(Tri) int;
Tri.PoolPrint();
std::cout<<"Deletando um bloco\n";
	delete b;
Tri.PoolPrint();
std::cout<<"Alocando um bloco\n";
	b = new(Tri) int;
Tri.PoolPrint();
std::cout<<"Deletando um bloco\n";
	delete b;
Tri.PoolPrint();
std::cout<<"Deletando um bloco\n";
	delete a;
Tri.PoolPrint();
std::cout<<"Alocando 2 blocos\n";
	a = new(Tri) int[5];
Tri.PoolPrint();
std::cout<<"Deletando 2 blocos\n";
	delete[] a;
Tri.PoolPrint();
std::cout<<"Deletando um bloco\n";
	delete c;
Tri.PoolPrint();
std::cout<<"Alocando 3 blocos\n";
	a = new(Tri) int[9];
Tri.PoolPrint();
std::cout<<"Deletando 3 blocos\n";
	delete a;
Tri.PoolPrint();
std::cout<<"Alocando um bloco\n";
	a = new(Tri) int;
	Tri.PoolPrint();
std::cout<<"Alocando 2 blocos\n";
	b = new(Tri) int[5];
Tri.PoolPrint();
std::cout<<"Deletando um bloco\n";
	delete a;
Tri.PoolPrint();
std::cout<<"Deletando 2 blocos\n";
	delete b;
	Tri.PoolPrint();
std::cout<<"Alocando um bloco\n";
a = new(Tri) int;
Tri.PoolPrint();
std::cout<<"Alocando um bloco\n";
b = new(Tri) int;
Tri.PoolPrint();std::cout<<"Alocando um bloco\n";
c = new(Tri) int;
Tri.PoolPrint();
std::cout<<"Deletando um bloco\n";
	delete a;
Tri.PoolPrint();

std::cout<<"Deletando um bloco\n";
	delete c;
Tri.PoolPrint();

std::cout<<"Deletando um bloco\n";
	delete b;
Tri.PoolPrint();
}