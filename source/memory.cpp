#include "memory.h"

/* /brief Simle Linked List Memory Pool constructor*/
SLLPool::SLLPool(std::size_t bytes){
	
	// \brief By the size passed in the constructor, calculates the number of bocks 	
	this->NumberOfBlocks = std::ceil ( (bytes+ sizeof(Header))/sizeof(Block) );
	

	unsigned int FreeBlocks = NumberOfBlocks;
	// \brief Sentinel Block
	NumberOfBlocks++;

	//std::cout<<"Number Of Blocks: "<<NumberOfBlocks<<"\n";

	// \brief Creats an array of blocks to be used as memory pool
	this->mp_Pool = new Block[NumberOfBlocks];

	//std::cout<<"mp_Pool Adress: "<<mp_Pool<<"\n";
	
	// \briefDictates the number of nodes to the Head's list node
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
	//declares the rectangle
	sf::RectangleShape rect;
	sf::Text gang;
	sf::Font fonte;
	if(!fonte.loadFromFile("source/data/AlteHaasGroteskBold.ttf")) {
		exit(EXIT_FAILURE);
	}

	fonte.loadFromFile("source/data/AlteHaasGroteskBold.ttf");
	//gang.setString("THE END\n(press E to end)");
	gang.setFont(fonte);			
	//gang.setPosition((20*nCol/4),10*nLin);
	//janela.draw(gang);	



	//clear the window
	janela.clear(sf::Color(0,0,0));
	//declares 2 vectors to run the memory pool
	Block *freecheck;
	Block *allcheck;
	//define the vectors initial value
	allcheck=mp_Pool;
	std::string Number;
	freecheck=mt_Sentinel->mp_Next;
	std::stringstream stream;
	gang.setCharacterSize(10);
	gang.setColor(sf::Color(0,0,0));
	//declares the counters and the auxiliar variables
	unsigned int c=0,c2=0,c3=0,aux=0,aux2=0,c4=0;
	//run the memory pool
	while(allcheck<mt_Sentinel){
		//if the area is free the vector freecheck will point to the next free area and paint this area with green
		if(allcheck ==freecheck){
			rect.setFillColor(sf::Color(0,255,0));
			freecheck=freecheck->mp_Next;
			c4++;
			Number.clear();
			stream.str("");
			stream << c4;
			std::cout<<c4;
			Number = stream.str();
			//Number="abut";
			gang.setPosition(5+c2*20,3+c3*25);
			gang.setString(Number);	
		}
		//if the area isn't free paint it with red
		else{
			rect.setFillColor(sf::Color(255,0,0));
		}

		c=0;
		//discover the size of the block
		while(allcheck->Lenght>c){
			c++;
		}
		//if it gets to the end of the line then jump to the next line
		if(c2==63){
			c2=0;
			c3++;
		}
		//if the block it too big for the rest of the line then divide it in minor blocks
		if(c2+c>63){
			aux=c2+c;
			c=63-(aux-c);
			//define the rectangle
			rect.setOutlineColor(sf::Color(255,255,255));
			rect.setOutlineThickness(1);
			rect.setPosition(5+c2*20,5+c3*25);
			rect.setSize(sf::Vector2f(20*c, 20));
			janela.draw( rect);
			janela.draw(gang);
			
			//if c is less than 63 then jump a line
			if(c<63){
				c3++;
			}
			//while the area still has blocks left keep dividing them to fit the lines and then put them in their place in the lines
			while(c>0){
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
				rect.setPosition(5+0*20,5+c3*25);
				rect.setSize(sf::Vector2f(20*c, 20));
				janela.draw( rect);
				janela.draw(gang);
				}
			c2=aux2;
			//go to the next area
			allcheck=(allcheck+allcheck->Lenght);
		}
		//if the block fits the line do
		else{
			//define the rectangle
			rect.setSize(sf::Vector2f(20*c, 20));
			rect.setOutlineColor(sf::Color(0,0,0));
			rect.setOutlineThickness(1);
			rect.setPosition(5+c2*20,5+c3*25);
			janela.draw( rect);
			janela.draw(gang);
			//go to the next area
			allcheck=(allcheck+allcheck->Lenght);
			c2=c2+c;
		}
	}
	//if it gets to the end of the line then jump to the next line
	if(c2==63){
		c2=0;
		c3++;
	}
	//adds the sentinel block
	rect.setSize(sf::Vector2f(20, 20));
	rect.setFillColor(sf::Color(0,255,0));
	rect.setOutlineColor(sf::Color(0,0,0));
	rect.setOutlineThickness(1);
	rect.setPosition(5+c2*20,5+c3*25);
	gang.setPosition(5+c2*20,3+c3*25);
	gang.setString("0");	
	janela.draw( rect);
	janela.draw( gang);

	//display the graphics
	janela.display();
}

void
SLLPool::PoolPrint(){
	Block *freecheck;
	Block *allcheck;
	allcheck=mp_Pool;
	freecheck=mt_Sentinel->mp_Next;
	unsigned int c=0,c4=0;
	std::cout<<"\n";
	while(allcheck<mt_Sentinel){
		if(allcheck ==freecheck){
			c4++;
			std::cout<<" |"<<allcheck->Lenght;
			while(allcheck->Lenght>c){
				c++;
				std::cout<<" -";
			}
			c=0;
			std::cout<<"(bloco livre numero: "<<c4<<")|";
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
	std::cout<<" |BLOCO SENTINEL:1 -(bloco livre numero: 0)|\n\n";

}

/* \brief Allocates memory to user, method inside new(Pool) overloaded method*/
void*
SLLPool::Allocate(std::size_t bytes){

	//Calculats the numbers of blocks needed
	unsigned int BlocksNeed = std::ceil ( (bytes+ sizeof(Header))/sizeof(Block) );
	//std::cout << "Bytes : " << bytes << "\n Blocks Need: " << BlocksNeed << "\n";
	//Block Pointer Right Had side -> Selected Block 
	Block* _rhs = mt_Sentinel->mp_Next;

	//Block Pointer Ledft Hand Side -> Previous selected Block
	Block* _lhs  = mt_Sentinel;


	//Loop until find empty block with enought space to fit user's stuff
	while(_rhs != nullptr && _rhs->Lenght < BlocksNeed){

		//Points to previous Block
		_lhs = _rhs;

		//Points to Next empty block 
		_rhs = _rhs->mp_Next;
	}
		//std::cout<<"_rhs Current Adress: "<<_rhs<<"\n";
		
	if (_rhs == nullptr)
		throw std::bad_alloc();

		if (_rhs->Lenght == BlocksNeed )
		{

			//Pasing exact size to user
			_lhs->mp_Next = _rhs->mp_Next;

			//Return the exatc location to user data
			return static_cast<void*>(reinterpret_cast<Header*>(_rhs) + 1u );
		}

		if (_rhs->Lenght > BlocksNeed)
		{
			Block * resz = _rhs+BlocksNeed;
			//Determine the Lenght of new empty block
			resz->Lenght = _rhs->Lenght - BlocksNeed;

			//How many blocks allocated
			_rhs->Lenght = BlocksNeed;

			//std::cout<<"Next Empty Block Adress after allocation: "<<(_rhs+BlocksNeed)<<"\n";
			//Determine Mp-next, next empt space
			resz->mp_Next = _rhs->mp_Next;

			//Make conecton between previous and next Block
			_lhs->mp_Next = resz;
			
			/*Return the exatc location to user data by converting _rhs to Header*
				add +1 and converting to void *
			  */ 
			return static_cast<void*>(reinterpret_cast<Header*>(_rhs) + 1u );
		}

	//Throw Bad_alloc if MemoryPull can't fit the memory request
	
	
	return nullptr;
}

void
SLLPool::Free(void * fre){
	Block* now = static_cast<Block*>(reinterpret_cast<Header*>(fre) - 1u);
	Block* prev;
	Block* next;
	prev = mt_Sentinel;
	next = mt_Sentinel->mp_Next;
	//runs the list untill fre is between prev and next or till next gets to the end of the list
	while( next<now && next!=nullptr ){
		prev = next;
		next = next->mp_Next;
	}
	if((prev+prev->Lenght)==now){
		prev->Lenght = now->Lenght + prev->Lenght;
		now = prev;
	}
	else{
		prev->mp_Next = now;
	}
	if((now+now->Lenght)==next){
		now->Lenght = now->Lenght + next->Lenght;
		now->mp_Next = next->mp_Next;
		
	}
	else{
		now->mp_Next = next;
	}
	return ;
}
void *
BestSLLPool::Allocate(std::size_t bytes){

	//Calculats the numbers of blocks needed
	unsigned int BlocksNeed = std::ceil ( (bytes+ sizeof(Header))/sizeof(Block) );

	//std::cout << "Bytes : " << bytes << "\n Blocks Need: " << BlocksNeed << "\n";
	//Block Pointer Right Had side -> Selected Block 
	Block* _rhs = mt_Sentinel->mp_Next;

	//Block Pointer Ledft Hand Side -> Previous selected Block
	Block* _lhs  = mt_Sentinel;
	
	//Diference between Blocks need and avaliable space
	unsigned int difLenght = NumberOfBlocks + 1;
	//Pointer to possible block
	Block* difPointer;
	//Previous block of diPointer
	Block* prevdifP;
	//Loop until find empty block with enought space to fit user's stuff
	while(_rhs != nullptr){

		//std::cout<<"_rhs Current Adress: "<<_rhs<<"\n";

		if (_rhs->Lenght == BlocksNeed )
		{

			//Pasing exact size to user
			_lhs->mp_Next = _rhs->mp_Next;

			//Return the exatc location to user data
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

		//Points to previous Block
		_lhs = _rhs;

		//Points to Next empty block 
		_rhs = _rhs->mp_Next;

	}
	if (difPointer->Lenght > BlocksNeed)
	{
		(difPointer+BlocksNeed)->Lenght = difPointer->Lenght - BlocksNeed;

		//Quantidade de Blocos a serem alocados
		difPointer->Lenght = BlocksNeed;

		//std::cout<<"Next Empty Block Adress after allocation: "<<(difPointer+BlocksNeed)<<"\n";
		//Determine Mp-next, next empt space
		(difPointer+BlocksNeed)->mp_Next = difPointer->mp_Next;

		//Make conecton between previous and next Block
		prevdifP->mp_Next = (difPointer+BlocksNeed);
		
		/*Return the exatc location to user data by converting difPointer to Header*
			add +1 and converting to void *
		  */ 
		return static_cast<void*>(reinterpret_cast<Header*>(difPointer) + 1u );
	}
	//Throw Bad_alloc if MemoryPull can't fit the memory request
	else
		throw std::bad_alloc();
	//std::cout<<"bug";
	return nullptr;


}