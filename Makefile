#######################################################Compilação##################################################################

all: msg test

msg:
	@echo Gremlin_Alfa-estamos a compilar vosso codigo mestre
test:
	g++ -Wall -std=c++11 -I	include/ source/main.cpp source/memory.cpp source/DLPool.cpp -o bin/test -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

########################################################Execução###################################################################
roll:
	./bin/test

##########################################################FIM######################################################################

