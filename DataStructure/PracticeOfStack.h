//
// Created by libin on 2025/6/26.
//

#ifndef DATASTRUCTURE_PRACTICEOFSTACK_H
#define DATASTRUCTURE_PRACTICEOFSTACK_H
#include <string>
#include <vector>
#include <queue>
#include "SequenceStack.h"

// 给定只包含 (, ), {, }, [ 和 ] 的字符串，判断字符串是否有效（括号配对且顺序正确）。
bool judgeString(const std::string & str) {
    SequenceStack<char> stack;
    for (auto & c : str) {
        if (c == '(' || c == '{' || c == '[')
            stack.push(c);
        else {
            if (stack.empty()) return false;
            char t = stack.top(); stack.pop();
            if (!((t == '('&& c==')') || (t=='{'&&c=='}') || (t=='['&&c==']')))
                return false;
        }
    }
    return stack.empty();
}

// 题目：设计一个支持 push、pop、top 和检索最小元素 getMin 的栈，要求所有操作都是 O(1) 时间。
//
//要点：可用辅助栈或在节点中记录“当前最小值”。

class MinStack{
    SequenceStack<int> dataSt, minSt;
public:
    void push(int x){
        dataSt.push(x);
        if (minSt.empty() || x < minSt.top())
            minSt.push(x);
    }

    void pop() {
        if (dataSt.top()==minSt.top()) minSt.pop();
        dataSt.pop();
    }
    int top() { return dataSt.top(); }
    int getMin() { return minSt.top(); }
};


// 题目：根据逆波兰表示法（后缀表达式）求值，如给定 ["2","1","+","3","*"] 输出 (2+1)*3 = 9。
int evalRPN(std::vector<std::string> &tokens) {
    SequenceStack<int> st;
    for(auto & t : tokens){
        if (isdigit(t.back())){
            st.push(std::stoi(t));
        } else{
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            if (t=="+") st.push(a+b);
            else if(t=="-") st.push(a-b);
            else if(t=="*") st.push(a*b);
            else st.push(a/b);
        }
    }
    return st.top();
}

// 题目：仅用两个栈来实现一个队列，支持 push、pop、peek 和 empty 操作。
class MyQueue{
    SequenceStack<int> inSt, outSt;
    void move(){
        if (outSt.empty()) {
            while (!inSt.empty()) {
                outSt.push(inSt.top());
                inSt.pop();
            }
        }
    }

public:
    void push(int x){ inSt.push(x);}
    int pop() {move(); int t = outSt.top(); outSt.pop(); return t; }
    int peek() { move(); return outSt.top(); }
    bool empty() const { return inSt.empty() && outSt.empty(); }
};

// 用队列实现栈
// 两队列 q1、q2；保持 q1 中始终保存栈内容，push(x) 时先 q2.push(x)，再将 q1 全部搬到 q2，然后 swap 两队列；
//
// pop() / top() 直接作用在 q1。
class MyStack{
    std::queue<int> q1, q2;
public:
    void push(int x){
        q2.push(x);
        while (!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        std::swap(q1, q2);
    }

    int pop() { int t = q1.front(); q1.pop(); return t; }
    int top() { return q1.front(); }
    bool empty() { return q1.empty(); }
};

// 滑动窗口最大值（Sliding Window Maximum）
//
// 题目：给定数组和窗口大小 k，返回每个窗口的最大值。
//
// 要点：虽然更常用双端队列，但也可用单调栈技巧做单次扫描。


#endif //DATASTRUCTURE_PRACTICEOFSTACK_H
