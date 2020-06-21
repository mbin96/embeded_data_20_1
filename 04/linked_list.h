
typedef struct _node
{
    int key;
    struct _node *next;
} node;

node *head, *tail;

node *insertAfter(int key, node *t);
void initList();
int deleteNext(node *t);
node *findNode(int key);
int deleteNode(int key);
node *orderedInsert(unsigned int key);
node *deleteAll();
void printList();