#ifndef _MEMORYPULL_
#define _MEMORYPULL_

#include <iostream>
#include <cstdlib>


class StoragePool{
	
	public:
		~StoragePool() {};
		virtual void * Allocate(std::size_t) = 0 ;
		virtual void Free (void *) = 0;

		struct  Tag {StoragePool * pool;};

		void* operator new (std::size_t bytes, StoragePool &p ){
			Tag * const tag = reinterpret_cast<Tag *> (p.Allocate(bytes + sizeof(Tag)));
			tag->pool = &p;

			return tag + 1u; 
		}
		void*  operator new (std::size_t bytes ) {
			Tag * const tag = reinterpret_cast<Tag *> (std::malloc(bytes + sizeof(Tag)));
			tag->pool = nullptr;
			return (reinterpret_cast<void*>(tag + 1u));
		}
		void  operator delete (void * arg){
			Tag * const tag = reinterpret_cast<Tag *>(arg) - 1u;
			if (nullptr != tag->pool)
			{
				tag->pool->Free(tag);
			}
			else
				std::free(tag);
		}

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
				char mc_RawArea [BlockSize - sizeof(Header)];
			};
			Block () : Header(), mp_Next(nullptr){};


		}; 

	private:
		unsigned int NumberOfBlocks;
		Block *mp_Pool; /* List's Head */
		Block *mt_Sentinel; /* Lis's End*/

	public:
		explicit SLLPool(std::size_t bytes);
		~SLLPool();
		void * Allocate(std::size_t bytes);
		void  Free(void * fre);

}; 

#endif