#######################################################Compilação##################################################################
CXX = g++
DELETAR = bin/rm
CVERSION = -std=c++11 #-std=c++0x
AVISA =-Wall

OP = $(AVISA) $(CVERSION)
SFMLOP = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#######################################################DIR############################################################

DIRIN = include/

DIRSRC = source/

DRIVE = main.cpp
#######################################################TEST########################################################


all: msg test

msg:
	@echo Gremlin_Alfa-estamos a compilar vosso codigo mestre
test:
	$(CXX) $(OP) -I	$(DIRIN) $(DIRSRC)$(DRIVE) $(DIRSRC)memory.cpp $(DIRSRC)DLPool.cpp -o bin/test $(SFMLOP)

########################################################Execução###################################################################
roll:
	./bin/test

##########################################################FIM######################################################################

