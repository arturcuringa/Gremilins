#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){
	sf::RenderWindow janela(sf::VideoMode(  1280,720 ),"Memory Management");
	SLLPool p(100000);
	bool x = true;
	int *a,*b,*c,*d,*e,*f,*g,*h,*i,*j,*k,*l,*m;
	a = new(p) int;
	b = new(p) int;
	c = new(p) int;
	d = new(p) int;
	e = new(p) int;
	f = new(p) int;
	g = new(p) int[400];
	h = new(p) int;
	i = new(p) int;
	j = new(p) int;
	k = new(p) int;
	l = new(p) int;
	m = new(p) int;

	delete b;
	p.Barprint(janela);
	while(x==true){
		x=true;
	}


	return 0;
}