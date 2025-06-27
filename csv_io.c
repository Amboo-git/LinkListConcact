#include "csv_io.h"
#include <stdio.h>
#include <string.h>

/* -------- 导出电话 / 邮箱 -------- */
int exportContactsToCsv(const ContactList *list, const char *filename)
{
    if (!list || !filename) return -1;

    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("无法写文件"); return -2; }

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
    if (!list || !filename) return -1;

    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("无法打开 CSV"); return -2; }

    char line[512];
    /* 跳过表头行 */
    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return -3; }

    int imported = 0;
    while (fgets(line, sizeof(line), fp)) {
        /* 去掉行尾 \r\n */
        line[strcspn(line, "\r\n")] = '\0';

        /* 依次取四列 */
        char *name  = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *note  = strtok(NULL, ",");

        if (!name || *name == '\0') continue;   /* 跳过空姓名 */

        Contact *c = createContact();
        strncpy(c->displayName, name,  sizeof(c->displayName)-1);
        if (note) strncpy(c->note, note, sizeof(c->note)-1);

        /* 只有一个手机号 */
        if (phone && *phone) {
            Phone *p = createPhone();
            strncpy(p->number, phone, sizeof(p->number)-1);
            c->phones = p;
        }

        /* 只有一个邮箱 */
        if (email && *email) {
            Email *e = createEmail();
            strncpy(e->address, email, sizeof(e->address)-1);
            c->emails = e;
        }

        appendContact(list, c);
        ++imported;
    }

    fclose(fp);
    printf("已导入 %d 条联系人\n", imported);
    return imported;
}