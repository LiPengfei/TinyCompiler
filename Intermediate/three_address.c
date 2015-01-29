typedef enum { rd, gt, if_f, san, lab, mul, sub, eq, wri, halt } OpKind;
typedef enum { Empty, IntConst, String } AddrKind;
typedef struct {
    AddrKind kind;
    union{
        int val;
        char *name;
    }contents;
} Address;
typedef struct {
    OpKind op;
    Address addr1, addr2, addr3;
} Quad;
