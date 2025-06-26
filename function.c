#include "contact.h"
#include "stdio.h"

void addPhone(Contact *contact) {
    Phone *newPhone = createPhone();
    printf("请输入电话号码: ");
    scanf("%29s", newPhone->number);
    newPhone->type = 1; // 默认类型 mobile，可拓展用户选择

    Phone *p = contact->phones;
    if (p == NULL) {
        contact->phones = newPhone;
    } else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newPhone;
    }
}

void addEmail(Contact *contact) {
    Email *newEmail = createEmail();
    printf("请输入邮箱: ");
    scanf("%63s", newEmail->address);
    newEmail->type = 1; // 默认 personal

    Email *p = contact->emails;
    if (p == NULL) {
        contact->emails = newEmail;
    } else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newEmail;
    }
}

void addContact(ContactList *list) {
    Contact *newContact = createContact();
    printf("请输入联系人姓名: ");
    scanf("%63s", newContact->displayName);
    printf("请输入联系人备注: ");
    scanf("%127s", newContact->note);

    // 添加多个号码
    char choice;
    do {
        addPhone(newContact);
        printf("继续添加号码？(y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');

    // 添加多个邮箱
    do {
        addEmail(newContact);
        printf("继续添加邮箱？(y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');

    // 插入链表尾部
    Contact *p = list->head;
    while (p->next != NULL) p = p->next;
    p->next = newContact;
    list->size++;
}
