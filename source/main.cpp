#include <iostream>
#include "memory.h"
#include "Operators.h"
#include "DLPool.h"


int main (){
	sf::RenderWindow janela(sf::VideoMode(  1280,720 ),"Memory Management");
	SLLPool p(1200);
	bool x = true;
	int *a,*b,*c,*d,*e,*f,*g,*h,*i,*j,*k,*l,*m;
	unsigned long long int *n;
	a = new(p) int;
	b = new(p) int;
	c = new(p) int;
	d = new(p) int;
	e = new(p) int;
	f = new(p) int;
	g = new(p) int;
	h = new(p) int;
	i = new(p) int;
	j = new(p) int;
	k = new(p) int;
	l = new(p) int;
	m = new(p) int;
	n = new(p) unsigned long long int;

	delete b;
	delete i;
	delete h;
	delete j;
	delete k;

	p.Barprint(janela);
	while(x==true){
		x=true;
	}


	return 0;
}