//
// Created by libin on 2025/4/19.
//

#include "Folder.h"
#include "Message.h"

void Folder::addMsg(Message *msg) {
    messages.insert(msg);
}

void Folder::remMsg(Message *msg) {
    messages.erase(msg);
}

void Folder::add_to_Message(const Folder &f) {
    for (auto m : f.messages) m->addFolder(this);
}

Folder::Folder(const Folder &rhs) :
        messages(rhs.messages){
    add_to_Message(rhs);
}

void Folder::remove_from_Message() {
    for (auto m : messages) m->remFolder(this);
}

Folder::~Folder() {
    remove_from_Message();
}

Folder & Folder::operator=(const Folder &rhs){
    // 从左侧运算对象中的每个 Message 中删除指向左侧运算对象的指针
    remove_from_Message();
    // 拷贝右侧对象的 messages 成员
    messages = rhs.messages;
    // 向每个拥有 rhs 指针的 Message 添加指向本 Folder 的指针
    add_to_Message(rhs);
    return *this;
}

void swap(Folder &lhs, Folder &rhs) {
    using std::swap;
    // 将每个 Folder 指针从它原来所在的 Message 中删除
    lhs.remove_from_Message();
    rhs.remove_from_Message();

    // 交换两个 Folder 的 messages 成员
    swap(lhs.messages, rhs.messages);   // 使用 swap(set&, set&)

    // 将两个交换内容的 Folder 指针重新添加到它的新 Message 中
    lhs.add_to_Message(lhs);
    rhs.add_to_Message(rhs);
}