#include "memory.h"

/* /brief Simle Linked List Memory Pool constructor*/
SLLPool::SLLPool(std::size_t bytes){
	
	//By the size passed in the constructor, calculates the number of bocks 	
	this->NumberOfBlocks = (bytes+ sizeof(Header))/sizeof(Block);

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

/* \brief Allocates memory to user, method inside new(Pool) overloaded method*/
void*
SLLPool::Allocate(std::size_t bytes){

	//Calculats the numbers of blocks needed
	unsigned int BlocksNeed = (bytes+ sizeof(Header))/sizeof(Block);

	//Block Pointer Right Had side -> Selected Block 
	Block* _rhs = this->mt_Sentinel;

	//Block Pointer Ledft Hand Side -> Previous selected Block
	Block* _lrs  = nullptr;
	
	//Loop until find empty block with enought space to fit user's stuff
	while(_rhs != nullptr){


		//Points to previous Block
		_lrs = _rhs;

		//Points to Next empty block 
		_rhs = _rhs->mp_Next;

		if (_rhs->Lenght == BlocksNeed )
		{
			//Pasing exact size to user
			_lrs->mp_Next = _rhs->mp_Next;

			//Return the exatc location to user data AFTER the Header 
			return static_cast<void*>(_rhs + sizeof(Header) );
		}
		if (_rhs->Lenght > BlocksNeed)
		{
			//Determine the Lenght of new empty block
			(_rhs+BlocksNeed)->Lenght = _rhs->Lenght - BlocksNeed;

			//Determine Mp-next, next empt space
			(_rhs+BlocksNeed)->mp_Next = _rhs->mp_Next;

			//Make conecton between previous and next Block
			_lrs->mp_Next = _rhs+BlocksNeed;

			//Return the exatc location to user data AFTER the Header 
			return static_cast<void*>(_rhs + sizeof(Header) );
		}

	}


	return nullptr;
}


void
SLLPool::Free(void * fre){

	//stub
}