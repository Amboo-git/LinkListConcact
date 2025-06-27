#include "contact.h"
#include "stdio.h"
#include <string.h>   // strcmp, strstr
#include <stdlib.h>   // free
#include <assert.h>   // assert

void addPhone(Contact *contact) {
    assert(contact);
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
    assert(contact);
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
    assert(list);
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

//清空删除对象的手机号链表
void clearPhones(Phone *head) {
    Phone *p = head;
    while (p) {
        Phone *next = p->next;
        free(p);
        p = next;
    }
}

//清空删除对象的邮箱链表
void clearEmails(Email *head) {
    Email *e = head;
    while (e) {
        Email *next = e->next;
        free(e);
        e = next;
    }
}

//删除一个联系人
void deleteContactByName(ContactList *list) {
    char name[64];
    printf("请输入被删除联系人的姓名：\n");
    scanf("%s",&name);

    if (!list || !list->head || !name) return;

    Contact *prev = list->head;
    Contact *curr = list->head->next;

    while (curr != NULL) {
        if (strcmp(curr->displayName, name) == 0) {
            // 断链
            prev->next = curr->next;

            // 清空手机号和邮箱链表
            clearPhones(curr->phones);
            clearEmails(curr->emails);

            // 释放联系人节点
            free(curr);
            list->size--;

            printf("联系人 \"%s\" 已成功删除。\n", name);
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    printf("未找到名为 \"%s\" 的联系人。\n", name);
}

//根据姓名或手机号关键词打印联系人相关信息
void searchContact(ContactList *list) {
    printf("请输入搜索关键字（电话号码 或 姓名）\n");
    char keyword[64];
    scanf("%s",&keyword);
    assert(list);
    assert(keyword);
    if (!list || !list->head || !keyword) return;

    int found = 0;
    Contact *curr = list->head->next;

    while (curr != NULL) {
        int match = 0;

        // 1. 匹配姓名
        if (strstr(curr->displayName, keyword) != NULL) {
            match = 1;
        }

        // 2. 匹配手机号
        Phone *p = curr->phones;
        while (!match && p != NULL) {
            if (strstr(p->number, keyword) != NULL) {
                match = 1;
                break;
            }
            p = p->next;
        }

        // 如果匹配，打印联系人信息
        if (match) {
            found++;
            printf("\n🔍 匹配到联系人 #%d\n", found);
            printf("姓名: %s\n", curr->displayName);
            printf("备注: %s\n", curr->note);

            // 打印所有电话
            printf("电话号码:\n");
            Phone *pp = curr->phones;
            while (pp) {
                printf("  - %s\n", pp->number);
                pp = pp->next;
            }

            // 打印所有邮箱
            printf("邮箱地址:\n");
            Email *ee = curr->emails;
            while (ee) {
                printf("  - %s\n", ee->address);
                ee = ee->next;
            }
        }

        curr = curr->next;
    }

    if (found == 0) {
        printf("未找到包含 \"%s\" 的联系人。\n", keyword);
    }
}

/*根据“姓名”查找联系人（精确匹配）；

找到后提供一个简单菜单，让用户选择修改内容：

修改姓名

修改某个电话号码

修改某个邮箱地址

可多次修改，直到用户选择退出。*/
void modifyContact(ContactList *list) {
    printf("请输入被修改联系人的姓名");
    char name[64];
    scanf("%s",&name);

    assert(list);
    assert(name);
    if (!list || !list->head || !name) return;

    Contact *curr = list->head->next;
    while (curr) {
        if (strcmp(curr->displayName, name) == 0) {
            printf("已找到联系人: %s\n", curr->displayName);
            int choice;

            do {
                printf("\n请选择要修改的内容：\n");
                printf("1. 修改姓名\n");
                printf("2. 修改某个电话号码\n");
                printf("3. 修改某个邮箱地址\n");
                printf("0. 退出修改\n");
                printf("你的选择: ");
                scanf("%d", &choice);
                getchar(); // 清除换行符

                if (choice == 1) {
                    printf("请输入新姓名: ");
                    scanf("%63s", curr->displayName);
                    printf("姓名已更新为: %s\n", curr->displayName);

                } else if (choice == 2) {
                    // 遍历电话号码并编号显示
                    int index = 1;
                    Phone *p = curr->phones;
                    while (p) {
                        printf("%d. %s\n", index++, p->number);
                        p = p->next;
                    }

                    if (index == 1) {
                        printf("该联系人没有电话号码。\n");
                        continue;
                    }

                    int target;
                    printf("请选择要修改的号码编号: ");
                    scanf("%d", &target);

                    p = curr->phones;
                    for (int i = 1; i < target && p != NULL; i++) p = p->next;

                    if (p) {
                        printf("请输入新号码: ");
                        scanf("%29s", p->number);
                        printf("号码已更新为: %s\n", p->number);}
                    else printf("无效编号。\n");
                    }

                    else if (choice == 3) {
                    int index = 1;
                    Email *e = curr->emails;
                    while (e) {
                        printf("%d. %s\n", index++, e->address);
                        e = e->next;}

                    if (index == 1) {
                        printf("该联系人没有邮箱地址。\n");
                        continue;}

                    int target;
                    printf("请选择要修改的邮箱编号: ");
                    scanf("%d", &target);

                    e = curr->emails;
                    for (int i = 1; i < target && e != NULL; i++) e = e->next;

                    if (e) {
                        printf("请输入新邮箱: ");
                        scanf("%63s", e->address);
                        printf("邮箱已更新为: %s\n", e->address);}
                    else printf("无效编号。\n");
                }
            } while (choice != 0);
            return;
        }
        curr = curr->next;
    }
    printf("未找到名为 \"%s\" 的联系人。\n", name);
}

int countContacts(ContactList *list) {
    if (!list || !list->head) return 0;

    int count = 0;
    Contact *p = list->head->next;  // 跳过哨兵节点

    while (p != NULL) {
        count++;
        p = p->next;
    }

    return count;
}

void printAllContacts(ContactList *list) {
    if (!list || !list->head) {
        printf("联系人列表为空。\n");
        return;
    }

    Contact *p = list->head->next;  // 跳过哨兵节点
    if (!p) {
        printf("当前没有任何联系人。\n");
        return;
    }

    printf("=== 联系人列表 ===\n");

    while (p != NULL) {
        printf("显示名: %s\n", p->displayName);
        printf("备注: %s\n", p->note);

        // 打印所有电话
        Phone *phone = p->phones;
        int phoneIndex = 1;
        while (phone != NULL) {
            printf("电话%d: %s \n", phoneIndex++, phone->number);
            phone = phone->next;
        }

        // 打印所有邮箱
        Email *email = p->emails;
        int emailIndex = 1;
        while (email != NULL) {
            printf("邮箱%d: %s \n", emailIndex++, email->address);
            email = email->next;
        }

        p = p->next;
    }

    printf("\n=== 全部联系人输出完毕 ===\n");
}

/* 清空整个联系人链表 —— 仅释放数据节点，不动哨兵节点 */
void ClearList(ContactList *list)
{
    assert(list && list->head);        /* list / head 不应为空 */

    Contact *curr = list->head->next;  /* 跳过哨兵节点 */
    while (curr) {
        Contact *next = curr->next;

        /* 先把该联系人的电话号码链表全清掉 */
        clearPhones(curr->phones);     /* 实现在 function.c 已有 */
        /* 再清邮箱链表 */
        clearEmails(curr->emails);

        free(curr);                    /* 释放联系人节点本身 */
        curr = next;
    }

    /* 复位哨兵 */
    list->head->next = NULL;
    list->size       = 0;
}
