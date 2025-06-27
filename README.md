# 单链表通讯录
通过单链表储存一套包含姓名、电话、email、备注字段的通讯录。
## 项目结构
```text
LinkListConcact
├── include/              # 头文件目录
│   ├── contact.h         # 定义联系人结构体、函数声明
│   └── csv_io.h          # 声明 CSV 导入导出相关函数
|
├── src/                  # 源码目录
│   ├── csv_io.c          # 实现 CSV 的读取与写入功能
│   ├── function.c        # 实现增删查改等联系人操作
│   ├── init.c            # 实现链表的初始化、节点创建等基础功能
│   └── main.c            # 主程序入口，调用其他模块功能
|
├── CMakeLists.txt        # CMake 构建配置文件
└── README.md             # 项目说明文档

```
## To-Do List
- [x] 实现针对链表的增删查改. 
- [x] 完成仅有增删查改功能的完整主程序.
- [x] 支持将通讯录导出为```.csv``` / 从```.csv```导入通讯录.
- [ ] 通过 JNI 将代码引入 Android 并为程序添加 Android GUI.
- [ ] 接入 Android 通讯录 API，实现单链表通讯录与 Android 设备通讯录的双向转换.
