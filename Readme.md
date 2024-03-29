### Readme

## About Project
```
一个利用QTGui和Socket，SQLite 完成的聊天室Demo
在Server和Client封装了一套句柄来解决Socket数据粘黏问题
```


QtChatRoomDemo用于总结和使用一些需要学习的模块，在实际项目中来熟悉和使用

- [x] Git的使用  （已同步至GitLab仓库）
- [x] MarkDown语法 （使用Typora来编写md格式的Readme文档）
- [x] 多线程的使用 (聊天室中多用户多线程)
- [x] Qt动画的使用 (用户登陆Login窗口淡入动画)
- [x] 布局 (用手写布局和定义组件对象的方式取代UI中拖拽控件)
- [x] TCP/IP (聊天室基于Socket方式完成信息传送)
- [x] QSQLITE (用户名密码使用QT+SQLITE来存储)
- [x] 增加Github的仓库


QtChatRoomDemo 数据库中默认提供3个用户供以最初登陆使用，登陆过后可以通过admin管理员账号添加新用户

| Username | Password |
| :------: | :------: |
|   test   |  123456  |
|  admin   |  123456  |
|  guest   |  123456  |

![image](https://user-images.githubusercontent.com/30315297/140594776-f58193dd-9bcc-40f2-b089-eb6b6258eab9.png)
![image](https://user-images.githubusercontent.com/30315297/140594872-6570d7e0-afa1-46ca-bbaa-eea08804c880.png)
