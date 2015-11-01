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

			enum { BlockSize = 16};
			union {
				Block *mp_Prev;
				Block *mp_Next;
			};
			Block () : Header(), mp_Next(nullptr){};
		};
	protected:
		unsigned int NumberOfBlocks;
		Block *mp_Pool; /* List's Head */
		Block *mt_Sentinel; /* List's End*/

	public:
		explicit DLPool(std::size_t bytes);
		~DLPool();
		void * Allocate(std::size_t bytes);
		void  Free(void * fre);
		void PoolPrint();


		}; 

#endif