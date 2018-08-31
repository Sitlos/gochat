#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 文件名：client.py

import socket               # 导入 socket 模块
list1 = []

for i in range(10000000) :
    s = socket.socket()         # 创建 socket 对象
    list1.append(s);
    host = '212.64.12.219' # 获取本地主机名
    port = 9838             # 设置端口号
    list1[i].connect((host, port))
    print i
s.close()  
