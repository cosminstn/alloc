#include <stddef.h>
#include <stdio.h>

const int MAX_MEM_SIZE = 30000;

char *totalMemory;

typedef struct {
    size_t size;
    int free;
    block *next;
} block;

block *init = (void*) totalMemory;

void initialize() {
    totalMemory = 
    init->size = MAX_MEM_SIZE - sizeof(block);
    init->free = 1;
    init->next = NULL;
}

void sliceBlock(block* host, size_t size) {
    block *new = (void*)((void*)host + sizeof(block) + size);
    new->size = host->size - size - sizeof(block);
    new->free = 1;
    new->next = host->next;
    host->size = size;
    host->next = new;
    host->free = 0;
}

void *secs_alloc(size_t nrOfBytes) {
    if(!(init->size)) {
        //INITIALIZE THE MEMORY BLOCK
        initialize();
    }

    block *cBlock;     //current block
    cBlock = init;

    //Caut urmatorul block liber care sa aiba dimensiunea cel putin egala cu nrOfBytes
    while((cBlock->size < nrOfBytes || cBlock->free == 0) && cBlock->next != NULL) {
        cBlock = cBlock->next;
    } 

    if(cBlock->size == nrOfBytes) {
        cBlock->free = 0;
        return (void*)(++cBlock);
    }

    if(cBlock->size > nrOfBytes + sizeof(block)) {
        sliceBlock(cBlock, nrOfBytes);
        return (void*)(cBlock->next);
    }

    printf("insufficient memory");
    return NULL;
}

void merge() {
    //Solves fragmentation
    block *cBlock;
    cBlock = init;
    while(cBlock->next != NULL) {
        if((cBlock->free) && (cBlock->next->free)) {
            cBlock->size += cBlock->next->size + sizeof(block);
            cBlock->next = cBlock->next->next;
        }
        cBlock = cBlock->next;
    }
}

void secs_free(void* p) {
    if(p >= (void*)totalMemory && (p <= (void*)(totalMemory + MAX_MEM_SIZE))) {
        block* cBlock = p;
        --cBlock;   //p pointeaza catre zona unde se pun date in Block. Noi vrem adresa blockului
        cBlock->free = 1;
        merge();
    }
    else 
        printf("Please provide a valid memory location");
}