#include "DLPool.h"

/* \brief Simle Linked List Memory Pool constructor*/
DLPool::DLPool(std::size_t bytes){
	
	// \brief By the size passed in the constructor, calculates the number of bocks 	
	this->NumberOfBlocks = (bytes+ sizeof(Header))/sizeof(Block);
	// \brief "Celeing " function
	if ((bytes+ sizeof(Header))%sizeof(Block) != 0)
	{
		NumberOfBlocks++;
	}

	// \var Number of Free Blocks
	unsigned int FreeBlocks = NumberOfBlocks;
	// \briefSentinel Block
	NumberOfBlocks +=2;

	std::cout<<"Number Of Blocks: "<<NumberOfBlocks<<"\n";
	// \var Creats an array of blocks to be used as memory pool
	this->mp_Pool = new Block[NumberOfBlocks];

	std::cout<<"mp_Pool Adress: "<<mp_Pool+1<<"\n";
	
	// \brief Dictates the number of nodes to the Head's list node
	this->mp_Pool[1].Lenght = FreeBlocks;

	// \brief use the first block to create Sentinel Node
	this->mt_Sentinel = this->mp_Pool;
	// \brief Use the last block to create Tail Node
	this->mt_Tail = this->mp_Pool + FreeBlocks +1 ;

	// \brief Now Sentinel Nodes has to show List Head's
	this->mt_Sentinel->mp_Next = this->mp_Pool + 1;
	// \brief Next of mpPool to Tail
		mp_Pool[1].mp_Next = mt_Tail;
	// \brief Set Tails Prev ro Mp-Pool
	this->mt_Tail->mp_Prev = this->mp_Pool+1;
	
	// \brief Set Tail's Next to null
	this->mt_Tail->mp_Next = nullptr;

	// \brief Prev of mp_Poo = Sentinel
	this->mp_Pool[1].mp_Prev = mt_Sentinel;

	std::cout<<"mpPool_Prev: " << (mp_Pool + 1)-> mp_Prev << "\n";
	std::cout <<"mt_Sentinel : "<< mt_Sentinel;
	std::cout << "mp_Pool Next" << (mp_Pool + 1)->mp_Next << "\n";
	std::cout << "mt_Tail: " << mt_Tail << "\n";
}

DLPool::~DLPool(){

	delete [] mp_Pool;


}

void
DLPool::PoolPrint(){
	// \brief declares 2 pointers, freecheck to run the list and allcheck to run all the headers
	Block *freecheck;
	Block *allcheck;
	// \brief define the pointers initial value, allcheck points to the first Block of the pool after the sentinel and freecheck points to the sentinel->mp_Next
	allcheck=mp_Pool + 1;
	freecheck=mt_Sentinel->mp_Next;
	// \brief declares the counters
	unsigned int c=0,c4=0;
	// \brief jump a line and Print the sentinel block
	std::cout<<"\n |BLOCO SENTINEL:1 -(bloco livre numero: 0)|";
	// \brief run the memory pool
	while(allcheck<mt_Tail){
		// \brief if the area is free print the block size with the symbol "-" and position on the list
		if(allcheck ==freecheck){
			std::cout<<" |"<<allcheck->Lenght;
			while(allcheck->Lenght>c){
				c++;
				std::cout<<" -";
			}
			c=0;
			c4++;
			std::cout<<"(bloco livre numero: "<<c4<<")|";
			// \brief allcheck goes to the next header and freecheck goes to the next free Block
			allcheck=(allcheck+allcheck->Lenght);
			freecheck=freecheck->mp_Next;
		}
		// \brief if the area is free print the block size with the symbol "+" to say its not free
		else{
			std::cout<<" |"<<allcheck->Lenght;
			while(allcheck->Lenght>c){
				c++;
				std::cout<<" +";
			}
			c=0;
			std::cout<<"|";
			// \brief allcheck goes to the next header
			allcheck=(allcheck+allcheck->Lenght);
		}

	}	
		c4++;
		// \brief Print the tail block
		std::cout<<" |BLOCO TAIL:1 -(bloco livre numero: "<<c4<<")|\n";

}

/* \brief Allocates memory to user, method inside new(Pool) overloaded method*/
void*
DLPool::Allocate(std::size_t bytes){

	// \brief Calculats the numbers of blocks needed
	unsigned int BlocksNeed = (bytes+ sizeof(Header))/sizeof(Block);
	// \brief "Celeing " function
	if ((bytes+ sizeof(Header))%sizeof(Block) != 0)
	{
		BlocksNeed++;
	}
	std::cout << "Bytes : " << bytes << "\n Blocks Need: " << BlocksNeed << "\n";
	// \brief Block Pointer Right Had side -> Selected Block 
	Block* _rhs = mt_Sentinel->mp_Next;
	
	// \brief Loop until find empty block with enought space to fit user's stuff
	while(_rhs != mt_Tail){

		std::cout<<"_rhs Current Adress: "<<_rhs<<"\n";
		// \brief If there's a block with exact size of request
		if (_rhs->Lenght == BlocksNeed )
		{

			// \brief Pasing exact size to user
			_rhs->mp_Prev->mp_Next = _rhs->mp_Next;

			_rhs->mp_Next->mp_Prev = _rhs->mp_Prev;

			// \brief Return the exatc location to user data
			return static_cast<void*>(reinterpret_cast<Header*>(_rhs) + 1u );
		}
		// \brief If there's a block with bigger than request
		if (_rhs->Lenght > BlocksNeed)
		{
			std::cout<<_rhs->Lenght<<"\n";
			// \brief Determine the Lenght of new empty block
			(_rhs+BlocksNeed)->Lenght = _rhs->Lenght - BlocksNeed;

			// \brief How many blocks allocated
			_rhs->Lenght = BlocksNeed;

			std::cout<<"Next Empty Block Adress after allocation: "<<(_rhs+BlocksNeed)<<"\n";
			// \brief Determine Mp-next, next empt space
			(_rhs+BlocksNeed)->mp_Next = _rhs->mp_Next;
			// \brief Sets Next Free block prev to _rhs prev
			(_rhs+BlocksNeed)->mp_Prev = _rhs->mp_Prev;

			// \brief Make conecton between previous and next Block
			(_rhs->mp_Prev)->mp_Next = (_rhs+BlocksNeed);

			// \brief Make conection between next block and request block
			(_rhs->mp_Next)->mp_Prev = (_rhs+BlocksNeed);
			std::cout<<"AUQIUAIAIUA   "<<(_rhs->mp_Prev) << " "<< "\n"<<mt_Sentinel;
			/* \Brief Return the exatc location to user data by converting _rhs to Header*
				add +1 and converting to void *
			  */ 
			return static_cast<void*>(reinterpret_cast<Header*>(_rhs) + 1u );
		}

		//Points to Next empty block 
		_rhs = _rhs->mp_Next;



	}
	// \brief Throw Bad_alloc if MemoryPull can't fit the memory request
	
	if (_rhs == nullptr)
		throw std::bad_alloc();
	
	return nullptr;
}


void
DLPool::Free(void * fre){
	// \brief Convert void Poiner to Block Pointer after reduces 1u of Head
	Block* now = static_cast<Block*>(reinterpret_cast<Header*>(fre) - 1u);
	// \brief declare a pointer to run the list
	Block* next;
	// \brief set the pointer to point to sentinel->mp_Next
	next = mt_Sentinel->mp_Next;
	//runs the list untill next has a bigger adress than now
	while( next<now && next!=mt_Tail ){
		next = next->mp_Next;
	}
	// \brief if next->mp_Prev and now touches then combine them and now points to prev
	if(( next->mp_Prev + next->mp_Prev->Lenght)==now && next->mp_Prev!=mt_Sentinel){
		next->mp_Prev->Lenght = now->Lenght + next->mp_Prev->Lenght;
		now = next->mp_Prev;
		
	}
	// \brief if now and prev has any Block between them, then prev->mp_Next will point to now and now->mp_Prev will point to next->mp_Prev
	else{
		next->mp_Prev->mp_Next = now;
		now->mp_Prev=next->mp_Prev;
	}
	// \brief if prev and now touches then combine them
	if((now+now->Lenght)==next && next!=mt_Tail){
		now->Lenght = now->Lenght + next->Lenght;
		now->mp_Next = next->mp_Next;
		next->mp_Next->mp_Prev=now;

	}
	// \brief if now and next has any Block between them, then now->mp_Next will point to next and next->mp_Prev will point to now
	else{
		now->mp_Next=next;
		next->mp_Prev=now;
	}

	return ;
}