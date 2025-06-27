#include "contact.h"
#include "stdio.h"
#include <stdlib.h>   // malloc, free, exit
#include <string.h>   // memset
#include <assert.h>   // assert

Contact *createContact() {
    Contact *p = (Contact *)malloc(sizeof(Contact));
    assert(p != NULL);
    memset(p, 0, sizeof(Contact));
    p->next = NULL;
    return p;
}

Email *createEmail() {
    Email *p = (Email *)malloc(sizeof(Email));
    assert(p != NULL);
    memset(p, 0, sizeof(Email));
    p->next = NULL;
    return p;
}

Phone *createPhone() {
    Phone *p = (Phone *)malloc(sizeof(Phone));
    assert(p != NULL);
    memset(p, 0, sizeof(Phone));
    p->next = NULL;
    return p;
}

void initContactList(ContactList *contact){
    contact->head = createContact(); // 哨兵节点，空数据
    contact->size = 0;
}
