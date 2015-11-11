#######################################################Compilação##################################################################
CXX = g++
DELETAR = bin/rm
CVERSION = -std=c++11 #-std=c++0x
AVISA =-Wall -O3

OP = $(AVISA) $(CVERSION)
SFMLOP = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#######################################################DIR############################################################

DIRIN = include/

DIRSRC = source/

DRIVE =  drive_3block.cpp # drive_2block.cpp drive_oneblock.cpp  #main.cpp 

TIME =  TimeTest.cpp # drive_simulation.cpp #
#######################################################TEST########################################################


all: msg test

msg:
	@echo Gremlin_Alfa-estamos a compilar vosso codigo mestre
test:
	$(CXX) $(OP) -I	$(DIRIN) $(DIRSRC)$(DRIVE) $(DIRSRC)memory.cpp $(DIRSRC)DLPool.cpp -o bin/test $(SFMLOP)

########################################################Execução###################################################################
roll:
	./bin/test

########################################################TIMES TEST ############################
time:
	$(CXX) $(OP) -I $(DIRIN) $(DIRSRC)$(TIME) $(DIRSRC)memory.cpp $(DIRSRC)DLPool.cpp -o bin/test $(SFMLOP)

##########################################################FIM######################################################################

