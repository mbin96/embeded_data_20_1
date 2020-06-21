#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void main()
{
    node *t;

    initList();

    orderedInsert(9);
    orderedInsert(3);
    orderedInsert(5);
    orderedInsert(1);
    orderedInsert(7);

    printList();

    node * tmp = findNode(9);
    
    insertAfter(6,tmp);
    printList();
    
    deleteNode(5);
    printList();
    
    deleteAll();
}