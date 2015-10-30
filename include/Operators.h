#ifndef __Operators__
#define __Operators__

	#include "memory.h"

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

		void* operator new[] (std::size_t bytes, StoragePool &p ) {
			Tag * const tag = reinterpret_cast<Tag *> (p.Allocate(bytes + sizeof(Tag)));
			tag->pool = &p;

			return tag + 1u; 
		}
		void*  operator new[] (std::size_t bytes ) {
			Tag * const tag = reinterpret_cast<Tag *> (std::malloc(bytes + sizeof(Tag)));
			tag->pool = nullptr;
			return (reinterpret_cast<void*>(tag + 1u));
		}
		void  operator delete[] (void * arg){
			Tag * const tag = reinterpret_cast<Tag *>(arg) - 1u;
			if (nullptr != tag->pool)
			{
				tag->pool->Free(tag);
			}
			else
				std::free(tag);
		}
#endif