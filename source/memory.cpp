#include "memory.h"

/* /brief Simle Linked List Memory Pool constructor*/
SLLPool::SLLPool(std::size_t bytes){
	
	// \brief By the size passed in the constructor, calculates the number of bocks 	
	this->NumberOfBlocks = std::ceil ( (bytes+ sizeof(Header))/sizeof(Block) );
	

	unsigned int FreeBlocks = NumberOfBlocks;
	// \brief Sentinel Block
	NumberOfBlocks++;

	// \brief Creats an array of blocks to be used as memory pool
	this->mp_Pool = new Block[NumberOfBlocks];
	
	// \brief  \briefDictates the number of nodes to the Head's list node
	this->mp_Pool[0].Lenght = FreeBlocks;

	// \brief Secure that next Node is null
	this->mp_Pool[0].mp_Next = nullptr;

	// \brief use the last block to create Sentinel Node
	this->mt_Sentinel = this->mp_Pool + FreeBlocks ;

	// \brief Now Sentinel Nodes has to show List Head's
	this->mt_Sentinel->mp_Next = this->mp_Pool;


}

SLLPool::~SLLPool(){

	delete [] mp_Pool;


}
void 
SLLPool::Barprint(sf::RenderWindow &janela){
	// \brief declares the rectangle
	sf::RectangleShape rect;
	// \brief declares the font and text to enumerate the free blocks
	sf::Text gang;
	sf::Font fonte;
	// \brief if the font is missing exit
	if(!fonte.loadFromFile("source/data/AlteHaasGroteskBold.ttf")) {
		exit(EXIT_FAILURE);
	}
	// \brief load the font
	fonte.loadFromFile("source/data/AlteHaasGroteskBold.ttf");
	// \brief set the font to the text
	gang.setFont(fonte);			


	// \brief clear the window
	janela.clear(sf::Color(0,0,0));
	// \brief declares 2 pointers, freecheck to run the list and allcheck to run all the headers
	Block *freecheck;
	Block *allcheck;
	// \brief define the pointers initial value, allcheck points to the first Block of the pool and freecheck points to the sentinel->mp_Next
	allcheck=mp_Pool;
	freecheck=mt_Sentinel->mp_Next;
	// \brief declares the string and stream used to enumerate the free blocks
	std::string Number;
	std::stringstream stream;
	// \brief define the size and color of the text
	gang.setCharacterSize(10);
	gang.setColor(sf::Color(0,0,0));
	// \brief declares the counters and the auxiliar variables
	unsigned int c=0,c2=0,c3=0,aux=0,aux2=0,c4=0;
	// \brief run the memory pool
	while(allcheck<mt_Sentinel){
		// \brief if the area is free the pointer freecheck will point to the next free area and paint this area with green
		if(allcheck ==freecheck){
			rect.setFillColor(sf::Color(0,255,0));
			freecheck=freecheck->mp_Next;
			c4++;
			// \brief clear the string and stream to define the text content and then define its position
			Number.clear();
			stream.str("");
			stream << c4;
			std::cout<<c4;
			Number = stream.str();
			gang.setString(Number);	
			gang.setPosition(5+c2*20,3+c3*25);
		}
		// \brief if the area isn't free paint it with red
		else{
			rect.setFillColor(sf::Color(255,0,0));
		}
		// \brief gets the size of the block
		c=allcheck->Lenght;
		// \brief if it gets to the end of the line then jump to the next line
		if(c2==63){
			c2=0;
			c3++;
		}
		// \brief if the block it too big for the rest of the line then divide it in minor blocks
		if(c2+c>63){
			aux=c2+c;
			c=63-(aux-c);
			// \brief define the rectangle
			rect.setOutlineColor(sf::Color(255,255,255));
			rect.setOutlineThickness(1);
			rect.setPosition(5+c2*20,5+c3*25);
			rect.setSize(sf::Vector2f(20*c, 20));
			// \brief draw the rectangle and the text
			janela.draw( rect);
			janela.draw(gang);
			
			// \brief if c is less than 63 then jump a line
			if(c<63){
				c3++;
			}
			// \brief while the area still has blocks left keep dividing them to fit the lines and then put them in their place in the lines
			while(c>0){
				// \brief calculates the size and position of the next rectangle
				if(c>=63){
					c3++;
				}
				aux2 = c;
				c=aux-(c2+c);
				aux = c;
				c2=0;
				if(c>=63){
					c= 63;
				}
				// \brief define the size and position of the next rectangle and then draw it
				rect.setPosition(5+0*20,5+c3*25);
				rect.setSize(sf::Vector2f(20*c, 20));
				janela.draw( rect);
				}
			c2=aux2;
			// \brief go to the next header
			allcheck=(allcheck+allcheck->Lenght);
		}
		// \brief if the block fits the line do
		else{
			// \brief define the rectangle
			rect.setSize(sf::Vector2f(20*c, 20));
			rect.setOutlineColor(sf::Color(0,0,0));
			rect.setOutlineThickness(1);
			rect.setPosition(5+c2*20,5+c3*25);
			// \brief draw the rectangle and the text
			janela.draw( rect);
			janela.draw(gang);
			// \brief go to the next header
			allcheck=(allcheck+allcheck->Lenght);
			c2=c2+c;
		}
	}
	// \brief if it gets to the end of the line then jump to the next line
	if(c2==63){
		c2=0;
		c3++;
	}
	// \brief adds the sentinel block
	rect.setSize(sf::Vector2f(20, 20));
	rect.setFillColor(sf::Color(0,255,0));
	rect.setOutlineColor(sf::Color(0,0,0));
	rect.setOutlineThickness(1);
	rect.setPosition(5+c2*20,5+c3*25);
	gang.setPosition(5+c2*20,3+c3*25);
	gang.setString("0");	
	janela.draw( rect);
	janela.draw( gang);

	// \brief display the graphics
	janela.display();
}

void
SLLPool::PoolPrint(){
	// \brief declares 2 pointers, freecheck to run the list and allcheck to run all the headers
	Block *freecheck;
	Block *allcheck;
	// \brief define the pointers initial value, allcheck points to the first Block of the pool and freecheck points to the sentinel->mp_Next
	allcheck=mp_Pool;
	freecheck=mt_Sentinel->mp_Next;
	// \brief declares the counters
	unsigned int c=0,c4=0;
	// \brief jump a line
	std::cout<<"\n";
	// \brief run the memory pool
	while(allcheck<mt_Sentinel){
		// \brief if the area is free print the block size with the symbol "-" and position on the list
		if(allcheck ==freecheck){
			c4++;
			std::cout<<" |"<<allcheck->Lenght;
			while(allcheck->Lenght>c){
				c++;
				std::cout<<" -";
			}
			c=0;
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
	// \brief Print the sentinel block
	std::cout<<" |BLOCO SENTINEL:1 -(bloco livre numero: 0)|\n\n";

}

/* \brief Allocate memory to user, method inside new(Pool) overloaded method*/
void*
SLLPool::Allocate(std::size_t bytes){

	// \brief Calculates the numbers of blocks needed
	unsigned int BlocksNeed = std::ceil ( (bytes+ sizeof(Header))/sizeof(Block) );
	// \brief std::cout << "Bytes : " << bytes << "\n Blocks Need: " << BlocksNeed << "\n";
	// \brief Block Pointer Right Had side -> Selected Block 
	Block* _rhs = mt_Sentinel->mp_Next;

	// \brief Block Pointer Ledft Hand Side -> Previous selected Block
	Block* _lhs  = mt_Sentinel;


	// \brief Loop until find empty block with enought space to fit user's stuff
	while(_rhs != nullptr && _rhs->Lenght < BlocksNeed){

		// \brief Points to previous Block
		_lhs = _rhs;

		// \brief Points to Next empty block 
		_rhs = _rhs->mp_Next;
	}
		
	if (_rhs == nullptr)
		throw std::bad_alloc();

		if (_rhs->Lenght == BlocksNeed )
		{

			// \brief Pasing exact size to user
			_lhs->mp_Next = _rhs->mp_Next;

			// \brief Return the exatc location to user data
			return static_cast<void*>(reinterpret_cast<Header*>(_rhs) + 1u );
		}

		if (_rhs->Lenght > BlocksNeed)
		{
			Block * resz = _rhs+BlocksNeed;
			// \brief Determine the Lenght of new empty block
			resz->Lenght = _rhs->Lenght - BlocksNeed;

			// \brief How many blocks allocated
			_rhs->Lenght = BlocksNeed;

			// \brief Determine Mp-next, next empt space
			resz->mp_Next = _rhs->mp_Next;

			// \brief Make conecton between previous and next Block
			_lhs->mp_Next = resz;
			
			/* \brief Return the exatc location to user data by converting _rhs to Header*
				add +1 and converting to void *
			  */ 
			return static_cast<void*>(reinterpret_cast<Header*>(_rhs) + 1u );
		}

	// \brief Throw Bad_alloc if MemoryPull can't fit the memory request
	
	
	return nullptr;
}

// \brief free an allocated Block and insert it in the list of free Blocks 
void
SLLPool::Free(void * fre){
	// \brief Convert void Poiner to Block Pointer after reduces 1u of Head
	Block* now = static_cast<Block*>(reinterpret_cast<Header*>(fre) - 1u);
	// \brief declares two pointers to run the list
	Block* prev;
	Block* next;
	// \brief set prev and next to point respectively to the sentinel block and to the next block on the list
	prev = mt_Sentinel;
	next = mt_Sentinel->mp_Next;
	// \brief runs the list untill now is between prev and next or till next gets to the end of the list
	while( next<now && next!=nullptr ){
		prev = next;
		next = next->mp_Next;
	}
	// \brief if prev and now touches then combine them and now points to prev
	if((prev+prev->Lenght)==now){
		prev->Lenght = now->Lenght + prev->Lenght;
		now = prev;
	}
	// \brief if now and prev has any Block between them, then prev->mp_Next will point to now
	else{
		prev->mp_Next = now;
	}
	// \brief if prev and now touches then combine them
	if((now+now->Lenght)==next){
		now->Lenght = now->Lenght + next->Lenght;
		now->mp_Next = next->mp_Next;
		
	}
	// \brief if now and next has any Block between them, then now->mp_Next will point to next
	else{
		now->mp_Next = next;
	}
	return ;
}
void *
BestSLLPool::Allocate(std::size_t bytes){

	// \brief Calculats the numbers of blocks needed
	unsigned int BlocksNeed = std::ceil ( (bytes+ sizeof(Header))/sizeof(Block) );

	// \brief Block Pointer Right Had side -> Selected Block 
	Block* _rhs = mt_Sentinel->mp_Next;

	// \brief Block Pointer Ledft Hand Side -> Previous selected Block
	Block* _lhs  = mt_Sentinel;
	
	// \brief Diference between Blocks need and avaliable space
	unsigned int difLenght = NumberOfBlocks + 1;
	// \brief Pointer to possible block
	Block* difPointer;
	// \brief Previous block of diPointer
	Block* prevdifP;
	// \brief Loop until find empty block with enought space to fit user's stuff
	while(_rhs != nullptr){

		if (_rhs->Lenght == BlocksNeed )
		{

			// \brief Pasing exact size to user
			_lhs->mp_Next = _rhs->mp_Next;

			// \brief Return the exatc location to user data
			return static_cast<void*>(reinterpret_cast<Header*>(_rhs) + 1u );
		}
		if (_rhs->Lenght > BlocksNeed)
		{
			if (_rhs->Lenght - BlocksNeed < difLenght )
			{
				difPointer = _rhs;
				prevdifP = _lhs;
			}
		}

		// \brief Points to previous Block
		_lhs = _rhs;

		// \brief Points to Next empty block 
		_rhs = _rhs->mp_Next;

	}
	if (difPointer->Lenght > BlocksNeed)
	{
		(difPointer+BlocksNeed)->Lenght = difPointer->Lenght - BlocksNeed;

		// \brief Quantidade de Blocos a serem alocados
		difPointer->Lenght = BlocksNeed;

		// \brief Determine Mp-next, next empt space
		(difPointer+BlocksNeed)->mp_Next = difPointer->mp_Next;

		// \brief Make conecton between previous and next Block
		prevdifP->mp_Next = (difPointer+BlocksNeed);
		
		/* \brief Return the exatc location to user data by converting difPointer to Header*
			add +1 and converting to void *
		  */ 
		return static_cast<void*>(reinterpret_cast<Header*>(difPointer) + 1u );
	}
	// \brief Throw Bad_alloc if MemoryPull can't fit the memory request
	else
		throw std::bad_alloc();
	return nullptr;


}