#define NULL 0
#define MEMSIZE 8096

typedef double Align;
typedef union header{
    struct {
        union header *next;
        unsigned usedsize;
        unsigned freesize;
    } s;
    Align a;
} Header;

static Header mem[MEMSIZE];
static Header *memptr = NULL;

void *malloc (unsigned nbytes){
    Header *p, *newp;
    unsigned nunits;
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if (memptr == NULL){
        memptr->s.next = memptr = mem;
        memptr->s.usedsize = 1;
        memptr->s.freesize = MEMSIZE - 1;
    }
    for (p = memptr;
            (p->s.next != memptr) && (p->s.freesize < nunits);
            p = p->s.next);
    if (p->s.freesize < nunits) {
        return NULL;
    }
    newp = p + p->s.usedsize;
    newp->s.usedsize = nunits;
    newp->s.freesize = p->s.freesize - nunits;
    newp->s.next = p->s.next;
    p->s.freesize = 0;
    p->s.next = newp;
    memptr = newp;
    return (void *) (newp + 1);
}

void free(void *ap){
    Header *bp, *p, *prev;
    bp = (Header *)ap - 1;
    for (prev = memptr; p = memptr->s.next;
            p != bp && p != memptr; prev = p, p = p->s.next);
    if (p != bp) {
        return;
    }

    prev->s.freesize += p->s.usedsize + p->s.freesize;
    prev->s.next = p->s.next;
    memptr = prev;
}
