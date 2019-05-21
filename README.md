# 基于Socket编程的多人聊天室 <C语言实现>

###### Multi-clients chat room based on Scoket Programming <C implementation>

## 功能

* 服务器端
  - [x] 开放接收客户连接，可部署于支持TCP/IP的任一台计算机中
  - [x] 接收来自客户端的连接并判断昵称是否重复
  - [x] 与客户端交互，如果有客户端登录、退出、提交聊天，将信息发给所有的客户端
  - [x] 支持最多100人同时聊天
* 客户端
  - [x] 根据输入IP地址连接特定服务器
  - [x] 在服务器中拥有唯一标识用户的昵称
  - [x] 发送信息、接收包括其他用户信息以及服务器信息

> 图片展示及说明信息

![demo-image](<https://raw.githubusercontent.com/gujing0023/Chatroom-Demo/master/demo/demo.png?token=AITVCCD236I2JPBVPXDKQH244P3BI>)

## 食用方法

clone项目至本地，使用

```shell
git clone "https://github.com/gujing0023/Chatroom-Demo.git"
```

进入```src```文件夹，使用```make```命令编译```cli.c```以及```ser.c```文件生成服务器端和客户端程序，并使用```make copy```命令创建多个客户端(可选)

```shell
cd Chatroom-Demo/src
make
make copy
```

将生成的```ser```作为服务器端程序置于一台你想作为服务器端的计算机上（**需明确服务器端IP地址**），将```cli1```，```cli2```，```cli3```等客户端文件置于你想作为客户端的计算机们上

服务器端运行等待连接

````shell
./ser
the server is ready and listening
````

客户端运行，输入服务器地址：

* 若服务器与客户端都运行于本地，直接回车即可
* 若服务器运行于一台远程服务器上，则需输入特定IP地址。在示例中，我使用了一台位于美国迈阿密的Linux服务器，IP地址为```104.238.136.201```，直接输入该地址即可

输入昵称并回车，如返回

```shell
You have entered the chatroom, Start CHATTING Now!
```

说明连接成功，可以进行聊天了！！下表列出了客户端可以进行的操作

| 输入格式                      | 示例                | 效果                                         |
| ----------------------------- | ------------------- | -------------------------------------------- |
| ":" + “<空格>” + "你想说的话" | : Hello！I‘m llht！ | 所有聊天室中的客户均可收到该消息             |
| ":" + "q!"                    | :q!                 | 结束客户程序并退出，所有客户收到你退出的消息 |

## 实现方法及部分细节

待更新

