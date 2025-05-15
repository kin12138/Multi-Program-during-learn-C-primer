//
// Created by libin on 2025/4/19.
//

#include "Message.h"
#include "Folder.h"

void Message::save(Folder & f) {
    // 将给定的 Folder 添加到本 Message 的 folders 列表中
    folders.insert(&f);
    // 将本 Message 添加到f 的 Message 集合中
    f.addMsg(this);
}

void Message::remove(Folder &f) {
    // 从 folders 列表中删除给定 f
    folders.erase(&f);
    // 从 f 的 Message 集合中删除本 Message
    f.remMsg(this);
}

void Message::add_to_Folders(const Message & m) {
    for (auto f : m.folders) f->addMsg(this);       // 向每个包含 m 的 Folder 添加指向本 Message 的指针
}

Message::Message(const Message & m) :
        contents(m.contents), folders(m.folders) {
    add_to_Folders(m);      // 将本 Message 添加到所有包含 m 的 Folder 中
}

// 从对应的 Folder 中删除指向本 Message 的指针
void Message::remove_from_Folders() {
    for (auto f : folders) f->remMsg(this);       // 对 folders 中的每个指针, 从该 Folder 中删除指向本 Message 的指针
}

Message::~Message() {
    remove_from_Folders();
}

Message & Message::operator=(const Message &rhs) {
    remove_from_Folders();  // 从包含左侧运算对象的 Folder 中删除指向左侧 Message 的指针
    contents = rhs.contents;    // 拷贝右侧 Message 的内容
    folders = rhs.folders;      // 拷贝右侧 Message 的 folders 集合
    add_to_Folders(rhs);    // 向每个包含 rhs 的 Folder 添加指向本 Message 的指针
    return *this;
}

void swap(Message &lhs, Message &rhs) {
    using std::swap;
    // 将每个 Message 的指针从它原来所在的 Folder 中删除
    lhs.remove_from_Folders();
    rhs.remove_from_Folders();

    swap(lhs.contents, rhs.contents);   // 交换 message 内容, 使用 swap(string &, string &)
    swap(lhs.folders, rhs.folders);     // 交换 folders 元素，使用 swap(set&, set&)

    // 将每个交换内容后的 Message 指针添加到它的新 Folder 中
    lhs.add_to_Folders(lhs);
    rhs.add_to_Folders(rhs);
}

void Message::addFolder(Folder *f) {
    folders.insert(f);
}

void Message::remFolder(Folder *f) {
    folders.erase(f);
}

void Message::move_Folders(Message *m) {
    folders = std::move(m->folders);    // 调用 set 的移动赋值运算符
    for (auto f : folders) {
        f->remMsg(m);   // 从 Folder 中删除旧 Message 指针
        f->addMsg(this);    // 向 Folder 中添加新 Message 指针
    }
    m->folders.clear();     // 确保销毁 m 是无害的
}

Message::Message(Message &&rhs) : contents(std::move(rhs.contents)){
    move_Folders(&rhs);     // 移动 folders 并更新 Folder 指针
}

Message & Message::operator=(Message &&rhs) {
    if (this != &rhs) {                 // 检查自赋值
//        remove_from_Folders();
        contents = std::move(rhs.contents);
        move_Folders(&rhs);
    }
    return *this;
}