//
// Created by libin on 2025/4/19.
//

#ifndef KNOWLEDGETEST_MESSAGE_H
#define KNOWLEDGETEST_MESSAGE_H
#include <string>
#include <iostream>
#include <set>

class Folder;
class Message {
    friend class Folder;
    friend void swap(Message &, Message &);
public:
    // folders 被隐式初始化为空集合
    explicit Message(const std::string & str = "") : contents(str) { }
    // 拷贝控制成员，用来管理指向本 Message 的指针
    Message(const Message &);
    Message & operator=(const Message &);
    ~Message();
    Message(Message &&);
    Message & operator=(Message &&rhs);
    // 从给定 Folder 集合中添加或删除本条 Message
    void save(Folder &);
    void remove(Folder &);

private:
    // 拷贝构造函数、拷贝赋值运算符、析构函数中所使用的工具函数
    //将 Message 添加到指向参数的 Folder 中
    void add_to_Folders(const Message &);
    // 从 Folders 中的每个 Folder 中删除本条 Message
    void remove_from_Folders();

    void addFolder(Folder *);
    void remFolder(Folder *);

    // 从本 Message 移动 Folder 指针
    void move_Folders(Message *);

private:
    std::string contents;       // 实际消息内容
    std::set<Folder*> folders;      // 包含本条 Message 的 Folder
};

void swap(Message &, Message &);

#endif //KNOWLEDGETEST_MESSAGE_H
