#include "memory_functions.h"
#include"io.h"

void* memcpy(void* dest, const void* src, size_t n) {
    // Cast pointers to char* for byte-wise copying
    unsigned char* d = (unsigned char*) dest;
    const unsigned char* s = (const unsigned char*) src;

    // Copy bytes from src to dest
    while (n--) {
        *d++ = *s++;
    }

    return dest;
}

void* memset(void* ptr, int value, size_t n) {
    unsigned char* p = (unsigned char*) ptr; // Cast to unsigned char* for byte-wise manipulation
    unsigned char v = (unsigned char) value; // Cast value to unsigned char to ensure it's a byte

    while (n--) {
        *p++ = v; // Set the current byte to the specified value and move to the next byte
    }

    return ptr; // Return the original pointer
}

int memcmp(const void* ptr1, const void* ptr2, size_t n) {
    const unsigned char* p1 = (const unsigned char*) ptr1; // Cast to unsigned char* for byte-wise comparison
    const unsigned char* p2 = (const unsigned char*) ptr2;

    while (n--) {
        if (*p1 != *p2) {
            return (*p1 < *p2) ? -1 : 1; // Return -1 if ptr1 < ptr2, 1 if ptr1 > ptr2
        }
        p1++;
        p2++;
    }

    return 0; // Return 0 if all bytes are equal
}


extern uint32_t _heap,_heap_end;

static uint8_t* memory_pool = NULL; // End of the memory pool
static uint8_t* pool_end = NULL; // End of the memory pool
static uint8_t* heap_ptr = NULL; // Pointer to the current end of the heap
long HEAP_SIZE;
typedef struct Block {
    size_t size;
    struct Block* next;
    int free;
} Block;
static Block* free_list = NULL;

void Heap_Init(){
	memory_pool = (uint8_t*)&_heap;
	heap_ptr = (uint8_t*)&_heap;
	pool_end = (uint8_t*)&_heap_end;
	HEAP_SIZE = &_heap_end - &_heap;
	log_debug("Memory :%x\n",memory_pool);
	log_debug("Heap Start  :%x\n",heap_ptr);
	log_debug("Heap End :%x\n",pool_end);
	log_debug("HEAP_SIZE :%x\n",HEAP_SIZE);
	size_t size = HEAP_SIZE;
    free_list = (Block*)heap_ptr;
    free_list->size = size - sizeof(Block);
    free_list->next = NULL;
    free_list->free = 1;
}

void* malloc(size_t size) {
    Block* current = free_list;
    while (current) {
        // Check if the block is free and large enough
        if (current->free && current->size >= size) {
            // Split the block if it's significantly larger than requested
            if (current->size > size + sizeof(Block)) {
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->next = current->next;
                new_block->free = 1;

                current->size = size;
                current->next = new_block;
            }
            current->free = 0; // Mark the block as used
            return (char*)current + sizeof(Block); // Return pointer to memory after block header
        }
        current = current->next;
    }
	log_error("Malloc cannot allocate memory\n");
    return NULL; // No suitable block found
}
void free(void* ptr) {
    if (ptr == NULL) return;

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->free = 1; // Mark the block as free
    // Coalesce adjacent free blocks
    Block* current = free_list;
    while (current) {
        if (current->free && current->next && current->next->free) {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}
void heap_cleanup() {
    free(heap_ptr);
    heap_ptr = NULL;
    free_list = NULL;
}
void *calloc(size_t size1,size_t size2)
{
    size_t totalbytes = size1*size2;
	void *start_ptr = malloc(totalbytes);
	if(start_ptr == NULL){
	log_error("Calloc cannot allocate required memory");
	return NULL;
	}
	memset((uint8_t*)start_ptr,0,totalbytes);
	return start_ptr;
}