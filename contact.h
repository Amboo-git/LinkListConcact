#ifndef CONTACT_H //ifndef = if not defined, then / define CONTACT_H
#define CONTACT_H

typedef struct Phone {
    char number[30];
    int  type;           // 取值对标 Phone.TYPE
    struct Phone *next;
} Phone;

typedef struct Email {
    char address[64];
    int  type;           // 对标 Email.TYPE
    struct Email *next;
} Email;

typedef struct Contact {
    long  contactId;        // 同步后可保存 Android 的 _ID
    char  accountName[64];  // RawContacts 所需
    char  accountType[32];

    char  displayName[64];
    char  givenName[32];
    char  familyName[32];

    Phone *phones;          // 多电话号码链表
    Email *emails;          // 多邮箱链表

    char  note[128];

    struct Contact *next;   // 指向下一联系人
} Contact;

typedef struct ContactList {
    Contact *head;
    int size;
} ContactList;


Contact *createContact();
Email *createEmail();
Phone *createPhone();
void initContactList(ContactList *contact);

#endif
