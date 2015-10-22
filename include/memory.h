#ifndef _MEMORYPULL_
#define _MEMORYPULL_


class StoragePool{
	
	public :
		virtual ~StoragePool();
		virutal void * Allocate(size_t) = 0;
		virutal void Free (void  * ) = 0;


};


#endif