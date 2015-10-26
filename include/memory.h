#ifndef _MEMORYPULL_
#define _MEMORYPULL_




class StoragePool{
	
	public :
		virtual ~StoragePool();
		virutal void * Allocate(size_t) = 0;
		virutal void Free (void  * ) = 0;
		struct  Tag {StoragePool * pool;};

		void *operator new (size_t bytes, StoragePool &p ){
			Tag * const tag = reinterpret_cast<Tag *> (p.Allocate(bytes + sizeof(Tag)));
			tag->pool = &p;

			return tag + 1u; 
		}
		void * operator new (size_t bytes ) {
			Tag * const tag = reinterpret_cast<Tag *> (std::malloc(bytes + sizeof(Tag)));
			tag->pool = nullptr;
			return (reinterpret_cast<void*>(tag + 1u));
		}
		void * operator delete (void * arg) noexcept {
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
		struct block: public Header{

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
		Block &mt_Sentinel; /* Lis's End*/

	public:
		explicit SLLPool(size_t);
		~SLLPool();
}; 

#endif