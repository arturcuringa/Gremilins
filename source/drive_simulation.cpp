//#include "SLPool.h"
#include "memory.h"
#include "Operators.h"
#include <cstdlib>
#include <ctime>
#include <queue>
#include <utility>
#include <chrono>

using namespace std;

std::size_t getRandomForSize(){
	return (rand() % 500 + 101);
}

int getRandomTimeInterval(){
	return (rand() % 100 + 1);
}

void StoragePoolTest( StoragePool & _pool, std::time_t _timeLimit ){
	srand(1);
	std::priority_queue<std::pair<char*,int>> pq;

	for(std::time_t t(0); t < _timeLimit; ++t){
		while(!pq.empty()){
			auto ev = pq.top();
			if( ev.second  > t) break;

			pq.pop();
			char * toDelete = ev.first;
			//_pool.Free( toDelete );			
			delete toDelete;
		}

		auto memSize = getRandomForSize();
		//void  * const add = _pool.Allocate( memSize );
		//char * add = new char[ memSize ];
		char * add = new (_pool) char[ memSize ];
		
		auto elapsedTime = getRandomTimeInterval();
		std::time_t releaseTime = t + elapsedTime;
		pq.push( std::make_pair(add,releaseTime) );

		while(!pq.empty() && t >= _timeLimit - 1){
			auto ev = pq.top();

			pq.pop();
			void * toDelete = ev.first;
			//_pool.Free( toDelete );
			delete toDelete;
		}
	}
	
}

int main() {

	SLLPool p(500000000);
	//SLPoolBF p {50000000};
	StoragePoolTest(p, 1000000);
	auto average = chrono::steady_clock::now() - chrono::steady_clock::now();
	for(int j = 0; j < 100; ++j){
		auto start = chrono::steady_clock::now(); //Start the timer; 
			
		StoragePoolTest(p, 1000000);
		auto end = chrono::steady_clock::now(); //Stop the timer;
		average += (end - start); //Sum from current average plus the difference between end and start timers
	}

	cout<<chrono::duration <long double, milli> (average/100).count()<<endl;

	return 0;	
}