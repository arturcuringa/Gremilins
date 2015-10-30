#ifndef _MEMORYPULL_
#define _MEMORYPULL_

#include <iostream>
#include <cstdlib>
#include <new>
#include <exception>


class StoragePool{
	
	public:
		virtual ~StoragePool() {};
		virtual void * Allocate(std::size_t) = 0 ;
		virtual void Free (void *) = 0;

};


class SLLPool : public StoragePool {

	public:

		struct Header 
		{
			unsigned int Lenght;
			Header() : Lenght(0u){};
		};
		struct Block: public Header{

			enum { BlockSize = 16};
			union {
				Block *mp_Next;
				char mc_RawArea [BlockSize - sizeof(Header) - sizeof(mp_Next)];
			};
			Block () : Header(), mp_Next(nullptr){};


		}; 

	private:
		unsigned int NumberOfBlocks;
		Block *mp_Pool; /* List's Head */
		Block *mt_Sentinel; /* List's End*/

	public:
		explicit SLLPool(std::size_t bytes);
		~SLLPool();
		void * Allocate(std::size_t bytes);
		void  Free(void * fre);
		
}; 

#endif