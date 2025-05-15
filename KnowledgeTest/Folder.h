//
// Created by libin on 2025/4/19.
//

#ifndef KNOWLEDGETEST_FOLDER_H
#define KNOWLEDGETEST_FOLDER_H
#include <set>
#include <string>

class Message;

class Folder {
    friend class Message;
    friend void swap(Folder &, Folder &);
public:
    Folder() = default;
    //拷贝控制成员
    Folder(const Folder&);
    Folder & operator=(const Folder&);
    ~Folder();

private:
    void addMsg(Message *);
    void remMsg(Message *);
    void add_to_Message(const Folder&);
    void remove_from_Message();

private:
    std::set<Message *> messages;
};
void swap(Folder &, Folder &);


#endif //KNOWLEDGETEST_FOLDER_H
