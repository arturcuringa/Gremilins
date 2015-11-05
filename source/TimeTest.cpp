#include <iostream>
#include "memory.h"
#include "Operators.h"
#include <cstdlib>
#include <stdlib.h>
#include <queue>
#include <chrono>




// \brief Class Event with realease time and void pointer to allocate
class Events{
	public:
	std::size_t releaseTime;
	void * Aloc; 
	Events(std::size_t timepam, void* Alocprt) : releaseTime(timepam), Aloc(Alocprt) {}
};

// \brief  Generates a random number [100,2000]
unsigned int RandomSize(){
	srand (1);
	return rand() % 2000 + 100;

}
// \brief Generates random number [1,100]
unsigned int TimeRandom(){
	 srand (2);
	return rand() % 100 +1;
}

// \brief Funtor to compare Events by RealeaseTime
 struct comp{

	bool operator () (Events& a , Events &b){

		if (a.releaseTime > b.releaseTime)
		{
			return true;
		}
		return false;
	}

};


// \brief Simulates a heavy and random load to memory pull
void StoragePoolTest( StoragePool& _pool,std::size_t _timeLimit ){
	
	std::priority_queue<Events, std::vector<Events>, comp> pq;

	for (std::size_t i = 0; i < _timeLimit; ++i)
	{
		while(!pq.empty()){

			Events ev = pq.top();

			if (ev.releaseTime > i)
			{
				break;
			}

			pq.pop();

			_pool.Free(ev.Aloc);

			
		}

		unsigned int memSize = RandomSize();
		void* const add = _pool.Allocate(memSize);
		std::size_t timestamp = TimeRandom();
		std::size_t timer = i + timestamp;

		pq.push( Events (timer, add) )  ;


	}


}
// \brief Similar to StoragePoolTest, test with stl malloc and free
void NewAlloc(std::size_t _timeLimit){

	std::priority_queue<Events, std::vector<Events>, comp> pq;

	for (std::size_t i = 0; i < _timeLimit; ++i)
	{
		while(!pq.empty()){

			Events ev = pq.top();

			if (ev.releaseTime > i)
			{
				break;
			}

			pq.pop();

			std::free(ev.Aloc);

			
		}

		unsigned int memSize = RandomSize();
		void* const add = std::malloc(memSize);
		std::size_t timestamp = TimeRandom();
		std::size_t timer = i + timestamp;

		pq.push( Events (timer, add) )  ;


	}


}

int main (){
	// \brief Pointer to any memory pool
	std::size_t  memoSize = 0;

	// \brief Time control
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto dif = end - start;

		
		std::size_t i = 10000000;
		// \brief Creates a big memory pull
		memoSize = 200000;

		// \brief SLLPool Test
		std::cout<<">>>Starting Time Test of SLLPool with " << i <<"interactions:" <<"\n";
		std::cout<<">>>Creating a SLLPool with " << memoSize << "bytes\n";
		for (int j = 0; j < 10; ++j)
		{
			SLLPool  z(memoSize);
			start = std::chrono::steady_clock::now();
			StoragePoolTest(z, i);
			end = std::chrono::steady_clock::now();
			dif = end - start;
			std::cout<<">>>SLLPool used :";
			std::cout << std::chrono::duration <double, std::milli> (dif).count() << " ms" << std::endl;
			std::cout<<" >>>Deleting SLLPool \n\n";
		}
		

		// \brief BestSLLPool Test
		std::cout<<">>>Starting Time Test of BestSLLPool with " << i <<"interactions:" <<"\n";
		std::cout<<">>>Creating a BestSLLPool with " << memoSize << "bytes\n";
		for (int j = 0; j < 10; ++j)
		{
			BestSLLPool x(memoSize);

			start = std::chrono::steady_clock::now();
			StoragePoolTest(x, i);
			end = std::chrono::steady_clock::now();
			dif = end - start;
			std::cout<<">>>BestSLLPool used :";
			std::cout << std::chrono::duration <double, std::milli> (dif).count() << " ms" << std::endl;
			std::cout<<" >>>Deleting SLLPool \n\n";

		}
		
		
		std::cout<<">>>Starting Time Test of STL Heap Alloc with " << i <<"interactions:" <<"\n";
		
		for (int j = 0; j < 10; ++j)
		{
			start = std::chrono::steady_clock::now();


			NewAlloc(i);

			end = std::chrono::steady_clock::now();
			dif = end - start;

			std::cout<<">>>STL Heap Alloc used :";
			std::cout << std::chrono::duration <double, std::milli> (dif).count() << " ms" << std::endl;
			std::cout<<"\n";
		}
		

	

	return 0;
}