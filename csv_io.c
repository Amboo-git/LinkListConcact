#include "csv_io.h"
#include <stdio.h>
#include <string.h>

/* -------- 导出电话 / 邮箱 -------- */
int exportContactsToCsv(const ContactList *list, const char *filename)
{
    if (!list || !filename) return -1;

    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("无法写文件"); return -2; }
    
    fputs("\xEF\xBB\xBF", fp);          // 写入 UTF-8 BOM
    fprintf(fp, "displayName,phone,email,note\n");

    /* 遍历联系人 */
    for (Contact *c = list->head ? list->head->next : NULL; c; c = c->next) {
        /* ---------- 合并电话号码 ---------- */
        char phoneOut[1000] = "";
        for (Phone *p = c->phones; p; p = p->next) {
            strncat(phoneOut, p->number,
                    sizeof(phoneOut) - strlen(phoneOut) - 1);
            if (p->next) {
                strncat(phoneOut, "/",
                        sizeof(phoneOut) - strlen(phoneOut) - 1);
            }
        }

        /* ---------- 合并邮箱地址 ---------- */
        char emailOut[1000] = "";
        for (Email *e = c->emails; e; e = e->next) {
            strncat(emailOut, e->address,
                    sizeof(emailOut) - strlen(emailOut) - 1);
            if (e->next) {
                strncat(emailOut, "/",
                        sizeof(emailOut) - strlen(emailOut) - 1);
            }
        }

        /* ---------- 写入 CSV ---------- */
        fprintf(fp, "%s,%s,%s,%s\n",
                c->displayName,
                phoneOut,
                emailOut,
                c->note);
    }

    fclose(fp);
    printf("通讯录已导出至%s\n",filename);
    return 0;
}

int importContactsFromCsv(ContactList *list)
{
    char filename[100];
    printf("请输入要导入的通讯录名称（仅支持CSV文件，且需要输入.csv扩展名）\n");
    scanf("%d",&filename);

    /* ----------- 参数检查 ----------- */
    if (!list || !filename || *filename == '\0')     /* 空指针 / 空串 */
        return -1;

    FILE *fp = fopen(filename, "r");
    if (!fp) {                                       /* 文件打开失败 */
        perror("无法打开 CSV");
        return -2;
    }

    char line[512];

    /* 跳过表头：displayName,phone,email,note */
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        return -3;                                  /* 空文件或读取失败 */
    }

    int imported = 0;

    /* ----------- 读取数据行 ----------- */
    while (fgets(line, sizeof(line), fp)) {

        /* 去掉行尾 \r 或 \n */
        line[strcspn(line, "\r\n")] = '\0';
        
        /* 解析四个字段 */
        char *name  = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *note  = strtok(NULL, ",");

        if (!name || *name == '\0') continue;        /* 空姓名直接跳过 */

        /* 创建联系人节点 */
        Contact *c = createContact();
        strncpy(c->displayName, name, sizeof(c->displayName) - 1);

        if (note && *note)
            strncpy(c->note, note, sizeof(c->note) - 1);

        /* 单一电话 */
        if (phone && *phone) {
            Phone *p = createPhone();
            strncpy(p->number, phone, sizeof(p->number) - 1);
            c->phones = p;                           /* 直接挂到联系人上 */
        }

        /* 单一邮箱 */
        if (email && *email) {
            Email *e = createEmail();
            strncpy(e->address, email, sizeof(e->address) - 1);
            c->emails = e;
        }

        /* ----------- 追加到链表尾部 ----------- */
        Contact *tail = list->head;
        while (tail->next)              /* head 是哨兵，找到最后一个节点 */
            tail = tail->next;
        tail->next = c;                 /* 挂新节点 */
        list->size++;                   /* 更新计数 */

        ++imported;
    }

    fclose(fp);
    printf("已导入 %d 条联系人\n", imported);
    return 0;                    /* 返回成功导入数 */
}