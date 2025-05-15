//
// Created by libin on 2025/3/28.
//

#ifndef KNOWLEDGETEST_CONTAINERPRACTICE_H
#define KNOWLEDGETEST_CONTAINERPRACTICE_H

#include <iostream>
#include <string>
#include <deque>
#include <sstream>
#include <list>
#include <forward_list>
#include <stack>
#include <cctype>
#include <stdexcept>

void _9_18() {
    std::deque<std::string> deq;
    std::string all;
    std::cout << "please input string: " << std::endl;
    std::getline(std::cin, all);
    std::istringstream is(all);
    for (std::string str; is >> str; deq.emplace_back(str)) ;
    std::cout << "your input is: " << std::endl;
    for (auto & item : deq) {
        std::cout << item << std::endl;
    }
    is.clear();
    std::cin.clear();
}

void _9_19() {
    std::list<std::string> list;
    std::string all;
    std::cout << "please input string: ";
    std::getline(std::cin, all);
    std::istringstream is(all);
    for (std::string str; is >> str; list.emplace_back(str));
    std::cout << "your input is: " << std::endl;
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void _9_20() {
    std::list<int> lst{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::deque<int> odd;
    std::deque<int> even;
    for (std::list<int>::const_iterator it = lst.cbegin(); it != lst.cend(); ++it) {
        *it % 2 == 0 ? even.emplace_back(*it) : odd.emplace_back(*it);
    }

    for (auto & item : odd) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    for (auto & item : even) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void _9_24() {
    std::vector<int> vec;
//    int &a = vec.at(0);
//    int b = vec[0];
//    int c = vec.front();
    int d = *vec.begin();
}

void _9_26() {
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    size_t ia_size = sizeof (ia) / sizeof (int);
    std::vector<int> vec;
    std::list<int> lst;
    for (int i = 0; i < ia_size; ++i) {
        vec.emplace_back(ia[i]);
        lst.emplace_back(ia[i]);
    }

    std::vector<int>::iterator vit = vec.begin();
    std::list<int>::iterator lit = lst.begin();
    while (vit != vec.end() || lit != lst.end()) {
        if (*vit % 2 == 0) {
            vit = vec.erase(vit);
            ++lit;
        } else {
            lit = lst.erase(lit);
            ++vit;
        }
    }

    for (auto & item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    for (auto & item : lst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void _9_27() {
    std::forward_list<int> flst{0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    auto prev = flst.before_begin();
    auto curr = flst.begin();
    while (curr != flst.end()) {
        if (*curr % 2 == 0) {
            curr = flst.erase_after(prev);
        } else {
            prev = curr;
            ++curr;
        }
    }

    for (auto & item : flst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void _9_28_insertString(std::forward_list<std::string> & flst, const std::string &s1, const std::string & s2) {
    auto curr = flst.begin();
    while (curr != flst.end() && *curr != s1) {
        ++curr;
    }
    if (curr != flst.end()) {
        flst.insert_after(curr, s2);
    }
}

void _9_28() {
    std::forward_list<std::string> flst{"i", " ", "love", " ", "life"};
    std::string s1{"life"};
    std::string s2{" fuck you"};
    _9_28_insertString(flst, s1, s2);

    for (auto & item : flst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void _9_33() {
    std::vector<int> vec{0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    auto begin = vec.begin();
    while (begin != vec.end()) {
        ++begin;
        begin = vec.insert(begin, 42); // 若不给 begin 赋新值，begin 会失效
        ++begin;
    }

    for (auto & item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void _9_34() {
    std::vector<int> vec{0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    auto iter = vec.begin();
    while (iter != vec.end()) {
        if (*iter % 2){
            iter = vec.insert(iter, *iter);
            iter += 2;
        }else {
            ++iter;
        }
    }

    for (auto & item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void testStringConstructor() {
    const char * cp = "Hello World!!";      // 以空字符结束的数组
    char noNull[] = {'H', 'i'};     // 不是以空字符结束
    std::string s1(cp);                 // 拷贝 cp 中的字符直到遇到空字符；s1 == "Hello World!!"
    std::string s2(noNull, 2);        // 从 noNull 拷贝两个字符;s2 == "Hi"
    std::string s3(noNull);             // 未定义行为。noNull 不是以空字符结尾
    std::string s4(cp + 6, 5);        // 从 cp[6] 开始拷贝 5 个字符。
    std::string s5(s1, 6, 5);  // 在 s1[6] 开始拷贝 5 个字符
    std::string s6(s1, 6);          // 从 s1[6] 开始拷贝，直到 s1 末尾
    std::string s7(s1, 6, 20);  // 从 s1[6] 开始拷贝，直到 s1 末尾
    std::string s8(s1, 18);         // 抛出 out_of_range 异常
}

void testSubstr() {
    std::string s("Hello world");
    std::string s1 = s.substr(0, 5);        // s1 = Hello
    std::string s2 = s.substr(6);              // s2 = world
    std::string s3 = s.substr(6, 11);       // s3 = world
    std::string s4 = s.substr(12);             // 抛出 out_of_range 异常
}

void _9_41() {
    std::vector<char> vec{'h', 'e', 'l', 'l', 'o'};
    std::string s(vec.begin(), vec.end());
}

void replace_with_insert(std::string &s, const std::string & oldVal, const std::string & newVal) {
    auto curr = s.begin();
    while (curr <= s.end() - oldVal.size()) {
        if (oldVal == std::string{curr, curr + oldVal.size()}) {
            curr = s.erase(curr, curr + oldVal.size());
            curr = s.insert(curr, newVal.begin(), newVal.end());
            curr += newVal.size();
        } else {
            ++curr;
        }
    }
}

void _9_43() {
    std::string s{ "To drive straight thru is a foolish, tho courageous act." };
    replace_with_insert(s, "tho", "though");
    replace_with_insert(s, "thru", "through");
    std::cout << s << std::endl;
}

void replace_with_pos(std::string & s, const std::string & oldVal, const std::string & newVal) {
    int pos = 0;
    while (pos <= s.size() - oldVal.size()) {
        if (oldVal == s.substr(pos, oldVal.size())) {
            s.replace(pos, oldVal.size(), newVal);
            pos += newVal.size();
        } else {
            ++pos;
        }
    }
}

void _9_44() {
    std::string s{ "To drive straight thru is a foolish, tho courageous act." };
    replace_with_pos(s, "tho", "though");
    replace_with_pos(s, "thru", "through");
    std::cout << s << std::endl;
}

std::string & add_pre_and_suffix(std::string &name, const std::string & pre, const std::string & suffix) {
    name.insert(name.begin(), pre.cbegin(), pre.cend());
    name.append(suffix);
    return name;
}

void _9_45() {
    std::string name("Wang");
    std::cout << add_pre_and_suffix(name, "Mr.", ", Jr.");
}

std::string & add_pre_and_suffix2(std::string &name, const std::string &pre, const std::string & suffix) {
    name.insert(0, pre);
    name.insert(name.size(), suffix);
    return name;
}

void _9_46() {
    std::string name("Wang");
    std::cout << add_pre_and_suffix2(name, "Mr.", ", Jr.");
}

// 循环搜索子字符串出现的所有位置
void find_substring_pos() {
    std::string name("dfadafdasfd343245232t434543254545435132343476y 55243eq6tr6");
    std::string number("34");
    std::string::size_type pos = 0;
    while ((pos = name.find_first_of(number, pos)) != std::string::npos) {
        std::cout << "find number at index: " << pos << ", element is " << name[pos] << std::endl;
        ++pos;
    }
}

void find_numbers_and_letters(const std::string & target) {
    std::string capital_letters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::string small_letters("abcdefghijklmnopqrstuvwxyz");
    std::string numbers("0123456789");

    std::string::size_type pos = 0;
    std::cout << "number of target: " << std::endl;
    while ((pos = target.find_first_of(numbers, pos)) != std::string::npos) {
        std::cout << "find number at index: " << pos << ", element is " << target[pos] << std::endl;
        ++pos;
    }
    pos = 0;
    std::cout << "letter of target: " << std::endl;
    while ((pos = target.find_first_of(capital_letters + small_letters, pos)) != std::string::npos) {
        std::cout << "find letter at index: " << pos << ", element is " << target[pos] << std::endl;
        ++pos;
    }
}

void find_numbers_and_letters2(const std::string & target) {
    std::string capital_letters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::string small_letters("abcdefghijklmnopqrstuvwxyz");
    std::string numbers("0123456789");

    std::string::size_type pos = 0;
    std::cout << "letter of target: " << std::endl;
    while ((pos = target.find_first_not_of(numbers, pos)) != std::string::npos) {
        std::cout << "find letter at index: " << pos << ", element is " << target[pos] << std::endl;
        ++pos;
    }
    pos = 0;
    std::cout << "number of target: " << std::endl;
    while ((pos = target.find_first_not_of(capital_letters+small_letters, pos)) != std::string::npos) {
        std::cout << "find number at index: " << pos << ", element is " << target[pos] << std::endl;
        ++pos;
    }
}

void _9_47() {
    std::string target("ab2c3d7R4E6");
    find_numbers_and_letters(target);
    find_numbers_and_letters2(target);
}

void checkMax(std::string & currWord, std::string & maxWord){
    maxWord = currWord.size() > maxWord.size() ? currWord : maxWord;
}

bool checkAscenderOrDescender(const std::string & word) {
    std::string target("acemnorsuvwxz");
    std::string::size_type pos = word.find_first_not_of(target);
    return pos == std::string::npos;
}
void find_longest_noAscender_noDescender(std::ifstream & ifs) {
    std::string maxWord, currWord;
    while (ifs >> currWord) {
        if(checkAscenderOrDescender(currWord))
            checkMax(currWord, maxWord);
    }
    std::cout << maxWord << std::endl;
}

void _9_49() {
//    char cwd[1024];
//    if (_getcwd(cwd, sizeof(cwd)) != NULL)
//        std::cout << "current work directory: " << cwd << std::endl;

    std::ofstream ofs("../Resource/letter.txt");
    ofs << "rqerewqrfd  erqwqer grrewtret dfsafdsaFG FGDSAFDSA fasfdasf dgadsfdsafzffdqerw fgdsfadsf abcdfrer fda"
           "fdasffdsaf fdasf fdsbjmn acemnorsuvwxz qwerfe ace cdcccccc cccccccccccccccccccccccccccccccc" << std::flush;
    ofs.close();

    std::ifstream ifs("../Resource/letter.txt");
    if(!ifs) return;
    find_longest_noAscender_noDescender(ifs);
}


void testChangeNumber() {
    int i = 42;
    std::string s = std::to_string(i);
    double d = std::stod(s);

    std::string s2 = "pi = 3.14";
    // 转换 s2 中以数字开始的第一个子串
    d = std::stod(s.substr(s.find_first_of("+-.0123456789")));     // d = 3.14
}

int sum_integer(const std::vector<std::string> & vec) {
    int sum = 0;
    for (auto & item : vec) {
        sum += std::stoi(item);
    }
    return sum;
}

float sum_float(const std::vector<std::string> & vec) {
    float sum = 0.0;
    for (auto & item : vec) {
        sum += std::stof(item);
    }
    return sum;
}

void _9_50() {
    std::vector<std::string> vec1{"1", "2", "3", "4", "5", "6"};
    std::vector<std::string> vec2{"1.1", "2.2", "3.3", "4.4", "5.5", "6.6"};
    std::cout << sum_integer(vec1) << std::endl;
    std::cout << sum_float(vec2) << std::endl;
}

/*class Date{
public:
    // 构造函数接受表示日期的 string 参数
    // 可以处理如 January 1, 1990、1/1/1990、Jan 1 1990 等不同数据格式
    Date(std::string & date);
    void print();
private:
    unsigned monthCovert(std::string & s);
    unsigned _year;
    unsigned _month;
    unsigned _day;
};

void Date::print() {
    std::cout << "year: " << _year << " "
            << "month: " << _month << " "
            << "day: " << _day << std::endl;
    std::cout << _year << " 年 " << _month << " 月 " << _day << " 日" << std::endl;
}

Date::Date(std::string &date) {
    unsigned format = 0;
    if (date.find_first_of('/') != std::string::npos)
        format = 0;
    else if (date.find_first_of(',') != std::string::npos){
        format = 1;
    } else if (date.find_first_of('/') == std::string::npos && date.find_first_of(',') == std::string::npos) {
        format = 2;
    }

    switch (format) {
        // 1/1/1990
        case 0:
        {
            _month = std::stoi(date.substr(0, date.find_first_of('/')));
            _day = std::stoi(date.substr(date.find_first_of('/') + 1,
                                           date.find_last_of('/') - date.find_first_of('/')));
            _year = std::stoi(date.substr(date.find_last_of('/') + 1, 4));
            break;
        }
        // January 1, 1990
        case 1:
        {
            auto month = date.substr(0, date.find_first_of(' '));
            _month = monthCovert(month);
            _day = std::stoi(date.substr(date.find_first_of(' ') + 1,
                                         date.find_first_of(',') - date.find_first_of(' ')));
            _year = std::stoi(date.substr( date.find_first_of("123456789", date.find_first_of(',')), 4));
            break;
        }
        // Jan 1 1990
        case 2:
        {
            auto month = date.substr(0, date.find_first_of(' '));
            _month = monthCovert(month);
            _day = std::stoi(date.substr(date.find_first_of(' ') + 1,
                                         date.find_last_of(' ') - date.find_first_of(' ')));
            _year = std::stoi(date.substr(date.find_last_of(' ') + 1, 4));
            break;
        }
    }
}

unsigned Date::monthCovert(std::string & s) {
    if (s.find("Jan") != std::string::npos) return 1;
    else if (s.find("Feb") != std::string::npos) return 2;
    else if (s.find("Mar") != std::string::npos) return 3;
    else if (s.find("Apr") != std::string::npos) return 4;
    else if (s.find("May") != std::string::npos) return 5;
    else if (s.find("Jun") != std::string::npos) return 6;
    else if (s.find("Jul") != std::string::npos) return 7;
    else if (s.find("Aug") != std::string::npos) return 8;
    else if (s.find("Sep") != std::string::npos) return 9;
    else if (s.find("Oct") != std::string::npos) return 10;
    else if (s.find("Nov") != std::string::npos) return 11;
    else if (s.find("Dec") != std::string::npos) return 12;
    else return 0;
}

void _9_51() {
    std::string str;
    std::getline(std::cin, str);
    Date date(str);
    date.print();
}*/

// 判断字符是否为操作符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 返回操作符优先级
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 接受两个整数和一个操作符，返回计算结果
int calculator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Division by zero");
            return a / b;
        default:
            throw std::runtime_error("Invalid operator");
    }
}



int handleExpression(std::string & expr) {
    std::stack<char> ops_stk;
    std::stack<int> v_stk;
    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if(isspace(c))
            continue;

        // 如果是数字，解析完整字符并压入栈
        if (isdigit(c)) {
            int value = 0;
            while (i < expr.size() && isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                ++i;
            }
            v_stk.push(value);
            --i;      // 回退 1 位, 在 for 循环中 i 还要 ++
        }

        // 如果遇到 ’(' ,直接压入操作符栈
        else if (c == '(')
            ops_stk.push(c);

        // 如果遇到 ‘)' 则弹出操作符直到遇到左括号
        else if (c == ')') {
            while (!ops_stk.empty() && ops_stk.top() != '(') {
                int a = v_stk.top(); v_stk.pop();
                int b = v_stk.top(); v_stk.pop();
                char op = ops_stk.top(); ops_stk.pop();
                v_stk.push(calculator(a, b, op));
            }
            if (!ops_stk.empty() && ops_stk.top() == '(')
                ops_stk.pop();
            else
                throw std::runtime_error("Mismatched Parenthesis");
        }

        // 如果遇到操作符
        else if(isOperator(c)) {
            while (!ops_stk.empty() && getPrecedence(ops_stk.top()) >= getPrecedence(c)) {
                int a = v_stk.top(); v_stk.pop();
                int b = v_stk.top(); v_stk.pop();
                char op = ops_stk.top(); ops_stk.pop();
                v_stk.push(calculator(a, b, op));
            }
            ops_stk.push(c);
        }
    }

    // 处理剩余操作符
    while (!ops_stk.empty()) {
        int a = v_stk.top(); v_stk.pop();
        int b = v_stk.top(); v_stk.pop();
        char op = ops_stk.top(); ops_stk.pop();
        v_stk.push(calculator(a, b, op));
    }
    if (v_stk.size() != 1) {
        std::runtime_error("Error in expression evaluation");
    }
    return v_stk.top();
}

void _9_52() {
    std::string str;
    std::cout << "请输入一个数学表达式：";
    std::getline(std::cin, str);

    try {
        int result = handleExpression(str);
        std::cout << "计算结果是：" << result << std::endl;
    } catch (const std::exception & e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }
}

#endif //KNOWLEDGETEST_CONTAINERPRACTICE_H
