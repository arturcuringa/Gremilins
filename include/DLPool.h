#ifndef __DLPOOL__
#define __DLPOOL__


#include "memory.h"

class DLPool : public StoragePool {
	
	public:

		struct Header 
		{
			unsigned int Lenght;
			Header() : Lenght(0u){};
		};
		struct Block: public Header{

			enum { BlockSize = 24};
			Block *mp_Prev;
			union {
				Block *mp_Next;
				char mc_RawArea [BlockSize - sizeof(Header) - sizeof(mp_Next)- sizeof(mp_Prev)];
			};
			Block () : Header(), mp_Next(nullptr){};
		};
	protected:
		unsigned int NumberOfBlocks;
		Block *mp_Pool; /* List's Head */
		Block *mt_Sentinel; /* List's End*/
		Block *mt_Tail;
	public:
		explicit DLPool(std::size_t bytes);
		~DLPool();
		void * Allocate(std::size_t bytes);
		void  Free(void * fre);
		void PoolPrint();


		}; 

#endif