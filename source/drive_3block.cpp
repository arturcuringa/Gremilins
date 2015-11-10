#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"

bool flag(){
char y;
std::cout<<" continuar?\n";
	while(y!='n'&&y!='y'){
		std::cin>>y;
		if(y!='n'&&y!='y'){
			std::cout<<"comando invalido\n";
		}
	}
	if(y=='y'){
		return true;
	}
	else{
		return false;
	}
}

int main (){
	//sf::RenderWindow janela(sf::VideoMode( 1280 , 720),"Memory pool test");
	SLLPool Tri(44);
	Tri.PoolPrint();
	if(flag()==false){
		return 0;
	}

	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	int *a = new(Tri) int;
	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	int *b = new(Tri) int;
	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	int *c = new(Tri) int;
	

	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Deletando um bloco\n";
	delete a;
	
	
	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	a = new(Tri) int;
	

	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Deletando um bloco\n";
	delete b;
	
	
	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	b = new(Tri) int;
	

	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();
	
	std::cout<<"Deletando um bloco\n";
	delete b;
	
	
	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();
	
	std::cout<<"Deletando um bloco\n";
	delete a;
	
	
	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Alocando 2 blocos\n";
	a = new(Tri) int[5];
	
	
	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();

	std::cout<<"Deletando 2 blocos\n";
	delete[] a;
	
	
	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Deletando um bloco\n";
	delete c;
	
	
	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Alocando 3 blocos\n";
	a = new(Tri) int[9];
	
	
	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Deletando 3 blocos\n";
	delete a;
	
	
	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	a = new(Tri) int;
	

	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();

	std::cout<<"Alocando 2 blocos\n";
	b = new(Tri) int[5];
	
	
	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Deletando um bloco\n";
	delete a;
	
	
	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();

	std::cout<<"Deletando 2 blocos\n";
	delete b;
	

	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	a = new(Tri) int;
	

	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();
	std::cout<<"Alocando um bloco\n";
	b = new(Tri) int;
	

	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Alocando um bloco\n";
	c = new(Tri) int;
	
	
	if(flag()==false){
		return 0;
	}	
	Tri.PoolPrint();

	std::cout<<"Deletando um bloco\n";
	delete a;
	

	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Deletando um bloco\n";
	delete c;
	

	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();

	std::cout<<"Deletando um bloco\n";
	delete b;
	

	if(flag()==false){
		return 0;
	}
	Tri.PoolPrint();
	std::cout<<"Encerrando testes\n";
	if(flag()==false){
		return 0;
	}
	return 0;
}