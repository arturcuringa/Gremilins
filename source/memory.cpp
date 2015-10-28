#include "memory.h"


/* /brief Simle Linked List Memory Pool constructor*/
SLLPool::SLLPool(std::size_t bytes){
	
	//By the size passed in the constructor, calculates the number of bocks 	
	this->NumberOfBlocks = bytes/16;

	//Creats an array of blocks to be used as memory pool
	this->mp_Pool = new Block[NumberOfBlocks];

	//Reduces one block of usage for sentinel Node
	this->NumberOfBlocks--;

	//Dictates the number of nodes to the Head's list node
	this->mp_Pool[0].Lenght = this->NumberOfBlocks;

	//Secure that next Node is null
	this->mp_Pool[0].mp_Next = nullptr;

	//use the last block to create Sentinel Node
	this->mt_Sentinel = this->mp_Pool + NumberOfBlocks;

	//Now Sentinel Nodes has to show List Head's
	this->mt_Sentinel->mp_Next = this->mp_Pool;


}

SLLPool::~SLLPool(){

	delete [] mp_Pool;


}

void*
SLLPool::Allocate(std::size_t bytes){

	//stub

	return nullptr;
}


void
SLLPool::Free(void * fre){

	//stub
}