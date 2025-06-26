#include "contact.h"
#include "stdio.h"

Contact *createContact() {
    Contact *p = (Contact *)malloc(sizeof(Contact));
    if (p == NULL) {
        perror("Contact节点内存分配失败");
        exit(1);
    }
    memset(p, 0, sizeof(Contact));
    p->next = NULL;
    return p;
}

Email *createEmail() {
    Email *p = (Email *)malloc(sizeof(Email));
    if (p == NULL) {
        perror("Email节点内存分配失败");
        exit(1);
    }
    memset(p, 0, sizeof(Email));
    p->next = NULL;
    return p;
}

Phone *createPhone() {
    Phone *p = (Phone *)malloc(sizeof(Phone));
    if (p == NULL) {
        perror("Phone节点内存分配失败");
        exit(1);
    }
    memset(p, 0, sizeof(Phone));
    p->next = NULL;
    return p;
}

void initContactList(ContactList *contact){
    contact->head = createContact(); // 哨兵节点，空数据
    contact->size = 0;
}
