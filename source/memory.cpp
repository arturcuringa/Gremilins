#include "memory.h"

/* /brief Simle Linked List Memory Pool constructor*/
SLLPool::SLLPool(std::size_t bytes){
	
	//By the size passed in the constructor, calculates the number of bocks 	
	this->NumberOfBlocks = (bytes+ sizeof(Header))/sizeof(Block);
	if ((bytes+ sizeof(Header))%sizeof(Block) != 0)
	{
		NumberOfBlocks++;
	}
	std::cout<<"Number Of Blocks: "<<NumberOfBlocks<<"\n";
	//Creats an array of blocks to be used as memory pool

	this->mp_Pool = new Block[NumberOfBlocks];

	std::cout<<"mp_Pool Adress: "<<mp_Pool<<"\n";
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
void
SLLPool::PoolPrint(){
	Block *freecheck;
	Block *allcheck;
	allcheck=mp_Pool;
	freecheck=mt_Sentinel->mp_Next;
	unsigned int c=0;
	std::cout<<"\n";
	while(allcheck<mt_Sentinel){
		if(allcheck ==freecheck){
			std::cout<<" |"<<allcheck->Lenght;
			while(allcheck->Lenght>c){
				c++;
				std::cout<<" -";
			}
			c=0;
			std::cout<<"|";
			allcheck=(allcheck+allcheck->Lenght);
			freecheck=freecheck->mp_Next;
		}
		else{
			std::cout<<" |"<<allcheck->Lenght;
			while(allcheck->Lenght>c){
				c++;
				std::cout<<" +";
			}
			c=0;
			std::cout<<"|";
			allcheck=(allcheck+allcheck->Lenght);
		}

	}
	std::cout<<" |BLOCO SENTINEL:1 -|\n\n";

}


/* \brief Allocates memory to user, method inside new(Pool) overloaded method*/
void*
SLLPool::Allocate(std::size_t bytes){

	//Calculats the numbers of blocks needed
	unsigned int BlocksNeed = (bytes+ sizeof(Header))/sizeof(Block);
	if ((bytes+ sizeof(Header))%sizeof(Block) != 0)
	{
		BlocksNeed++;
	}
	//Block Pointer Right Had side -> Selected Block 
	Block* _rhs = this->mt_Sentinel;

	//Block Pointer Ledft Hand Side -> Previous selected Block
	Block* _lhs  = nullptr;
	
	//Loop until find empty block with enought space to fit user's stuff
	while(_rhs != nullptr){


		//Points to previous Block
		_lhs = _rhs;

		//Points to Next empty block 
		_rhs = _rhs->mp_Next;

		std::cout<<"_rhs Current Adress: "<<_rhs<<"\n";

		if (_rhs->Lenght == BlocksNeed )
		{
			//Pasing exact size to user
			_lhs->mp_Next = _rhs->mp_Next;

			//Return the exatc location to user data
			return static_cast<void*>(_rhs + sizeof(Header) );
		}
		if (_rhs->Lenght > BlocksNeed)
		{
			std::cout<<_rhs->Lenght<<"\n";
			//Determine the Lenght of new empty block
			(_rhs+BlocksNeed)->Lenght = _rhs->Lenght - BlocksNeed;

			//Quantidade de Blocos a serem alocados
			_rhs->Lenght = BlocksNeed;

			std::cout<<"Next Empty Block Adress after allocation: "<<(_rhs+BlocksNeed)<<"\n";
			//Determine Mp-next, next empt space
			(_rhs+BlocksNeed)->mp_Next = _rhs->mp_Next;

			//Make conecton between previous and next Block
			_lhs->mp_Next = (_rhs+BlocksNeed);
			
			/*Return the exatc location to user data by converting _rhs to Header*
				add +1 and converting to void *
			  */ 
			return static_cast<void*>(reinterpret_cast<Header*>(_rhs) + 1u );
		}

	}
	//Throw Bad_alloc if MemoryPull can't fit the memory request
	if (_rhs == nullptr)
		throw std::bad_alloc();

	return nullptr;
}


void
SLLPool::Free(void * fre){
	//
	Block* now = static_cast<Block*>(reinterpret_cast<Header*>(fre) - 1u);
	//stub
	std::cout<<"Bloco a ser deletado adress: "<< now<<std::endl;

	
	Block* prev;
	Block* next;
	prev = mt_Sentinel;
	next = mt_Sentinel->mp_Next;
	//runs the list untill fre is between prev and next or till next gets to the end of the list
	while( next<now && next!=nullptr ){
		prev = next;
		next = next->mp_Next;
	}
	if((now+now->Lenght)==next){
		now->Lenght = now->Lenght + next->Lenght;
		now->mp_Next = next->mp_Next;
	}
	else{
		now->mp_Next = next;
	}
	if((prev+prev->Lenght)==now){
		prev->Lenght = now->Lenght + prev->Lenght;
		prev->mp_Next = now->mp_Next;
	}
	else{
		prev->mp_Next = now;
	}
	


	std::cout<< "Tamanho do bloco a ser deletado: " << now->Lenght <<"\n";
	//now = nullptr;
	return ;
}