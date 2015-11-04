#include <iostream>
#include "memory.h"
#include "Operators.h"
#include <cstdlib>
#include <queue>
#include <chrono>

class Events{
	public:
	std::size_t releaseTime;
	void * Aloc; 
	Events(std::size_t timepam, void* Alocprt) : releaseTime(timepam), Aloc(Alocprt) {}
};

unsigned int RandomSize(){
	
	return rand() % 2000 + 100;

}

unsigned int TimeRandom(){
	
	return rand() % 100 +1;
}

 struct comp{

	bool operator () (Events& a , Events &b){

		if (a.releaseTime <= b.releaseTime)
		{
			return true;
		}
		return false;
	}

};



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

	StoragePool* p;
	std::size_t  memSize = 2000000000;
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto dif = end - start;
	for (size_t i = 10; i < 10000000; i = i * 10)
	{
		std::cout<<">>>Starting Time Test of SLLPool with " << i <<"interactions:" <<"\n";
		std::cout<<">>>Creating a SLLPool with " << memSize << "bytes\n";

		p = new SLLPool (memSize);
		start = std::chrono::steady_clock::now();
		StoragePoolTest(*p, i);
		end = std::chrono::steady_clock::now();
		dif = end - start;
		std::cout<<">>>SLLPool used :";
		std::cout << std::chrono::duration <double, std::milli> (dif).count() << " ms" << std::endl;
		std::cout<<" >>>Deleting SLLPool \n\n";
		delete p;


		std::cout<<">>>Starting Time Test of BestSLLPool with " << i <<"interactions:" <<"\n";
		std::cout<<">>>Creating a BestSLLPool with " << memSize << "bytes\n";

		p = new BestSLLPool (memSize);

		start = std::chrono::steady_clock::now();
		StoragePoolTest(*p, i);
		end = std::chrono::steady_clock::now();
		dif = end - start;
		std::cout<<">>>BestSLLPool used :";
		std::cout << std::chrono::duration <double, std::milli> (dif).count() << " ms" << std::endl;
		std::cout<<" >>>Deleting SLLPool \n\n";

		delete p;

		std::cout<<">>>Starting Time Test of STL Heap Alloc with " << i <<"interactions:" <<"\n";
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