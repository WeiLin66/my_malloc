#ifndef __MM_H_
#define __MM_H_

#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include <unistd.h>  // get page size from kernel
#include <sys/mman.h> // mmap(), munmap()

#define DEBUG_ON        1
#define DEBUG_OFF       0
#define MM_DEBUG        DEBUG_ON
#define MAX_NAME_LEN    32

/* Free VM Page size that can be use */
#define MAX_FAMILY_PER_PAGE                                 \
        SYSTEM_PAGE_SIZE - sizeof(vm_page_family_list_t*)/  \
        sizeof(vm_page_family_t);                           \

/* Iterative macro for searching the VM Page from bottom to top */
#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr)               \
        {                                                                         \
        curr = (vm_page_family_list_t*)&vm_page_for_families_ptr->vm_page[0];     \
        uint32_t max = MAX_FAMILY_PER_PAGE;                                       \
        for(int i=0; i<max; i++){                                                 \
            curr += i;                                                            \
            if(curr->struct_size == 0){                                           \
                break;                                                            \
            }                                                                     \
        

#define ITERATE_PAGE_FAMILIES_END(vm_page_for_families_ptr, curr) }}

typedef struct _vm_page_family{

    uint8_t struct_name[MAX_NAME_LEN];
    uint32_t struct_size;
}vm_page_family_t;

typedef struct _vm_page_family_list{

    struct _vm_page_family_list* next;
    vm_page_family_t vm_page[0];
}vm_page_family_list_t;

void mm_init(void);
void mm_debug_fn(void);

#endif /* __MM_H_ */