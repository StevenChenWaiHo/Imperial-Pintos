#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <hash.h>
#include "threads/palloc.h"

struct ft_entry
{
    void *kernel_page;              /*page allocated in kernel virtual memory*/
    void *upage;
    struct file *file;              /*name of the file this frame is storing*/
    struct list owners;             /*processes that owns the frame*/
    struct thread *t;
    bool pinned;                    /* Boolean for pinned frame*/
    struct list_elem ele_elem;      /*list elem for eviction round robin list*/
    struct hash_elem ft_elem;       /*hash elem for frame table*/
};

struct owner
{
    struct thread *process;
    struct list_elem owner_elem;
};

void ft_init(void);
struct hash *get_ft(void);
void *get_frame(enum palloc_flags, void *, struct file*);
void ft_access_lock(void);
void ft_access_unlock(void);
struct ft_entry * ft_search_entry(void *);
struct ft_entry *ft_search_frame_with_owner(struct thread *);
void ft_free (struct thread *);
void free_frame(void *);
void ft_add_page_entry(struct ft_entry *);

#endif /* vm/frame.h */