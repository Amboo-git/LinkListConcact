#include "contact.h"
#include <stdio.h>
#include <assert.h>
#define VERSION_STR "v0.0.1"


void printTitle() {
    printf("██╗     ██╗███╗   ██╗██╗  ██╗██╗     ██╗███████╗████████╗\n");
    printf("██║     ██║████╗  ██║██║ ██╔╝██║     ██║██╔════╝╚══██╔══╝\n");
    printf("██║     ██║██╔██╗ ██║█████╔╝ ██║     ██║███████╗   ██║   \n");
    printf("██║     ██║██║╚██╗██║██╔═██╗ ██║     ██║╚════██║   ██║   \n");
    printf("███████╗██║██║ ╚████║██║  ██╗███████╗██║███████║   ██║   \n");
    printf("╚══════╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝╚══════╝   ╚═╝   \n");
    printf(" ██████╗ ██████╗ ███╗   ██╗ ██████╗ █████╗  ██████╗████████╗\n");
    printf("██╔════╝██╔═══██╗████╗  ██║██╔════╝██╔══██╗██╔════╝╚══██╔══╝\n");
    printf("██║     ██║   ██║██╔██╗ ██║██║     ███████║██║        ██║   \n");
    printf("██║     ██║   ██║██║╚██╗██║██║     ██╔══██║██║        ██║   \n");
    printf("╚██████╗╚██████╔╝██║ ╚████║╚██████╗██║  ██║╚██████╗   ██║   \n");
    printf(" ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝   ╚═╝   \n");
}


void runMenu(ContactList *plist){
	assert(plist != NULL);
    int select = 0;
    printTitle();
    printf("LinkList Contact %s\n", VERSION_STR);
    printf("\n");
    do{
        printf("****************************************************\n");
        printf("[1] 新建联系人，包含 姓名（必填）、电话号码、email、备注\n");
        printf("[2] 删除联系人\n");
        printf("[3] 更改联系人部分信息\n");
        printf("[4] 按姓名或手机号查找联系人信息\n");
        printf("[5] 打印所有联系人\n");
        printf("[6] 以 CSV 格式导出通讯录\n");
        printf("[7] 导入 CSV 格式通讯录\n");
        printf("[0] 退出程序\n");
        printf("****************************************************\n");
        printf("请选择 []\n");
		scanf("%d", &select);
        while (select > 7 || select < 0){
            printf("请输入有效字符！\n");
            scanf("%d", &select);
        }
            
		switch (select){
            case 0: break;
            case 1: 
                addContact(plist);
                break;
            case 2:
                deleteContactByName(plist);
                break;
            case 3:
                modifyContact(plist);
                break;
            case 4:
                searchContact(plist);
                break;
            case 5:
                printAllContacts(plist);
                break;
            case 6:
                exportContactsToCsv(plist,"contacts.csv");
                break;
            case 7:
                importContactsFromCsv(plist);
                break;
    		default:
			    printf("选择错误 ，请重新选择  .... \n");
			    break; 
            }
    } while (select != 0);
}

void DestroyList(ContactList* plist)
{
	assert(plist != NULL);
    ClearList(plist);          // 先清数据节点
    free(plist->head);         // 再彻底释放哨兵
    plist->head = NULL;
}

int main()
{
	ContactList studlist;
	initContactList(&studlist);
	runMenu(&studlist);
	DestroyList(&studlist);
	return 0;
}