//
// Created by libin on 2025/4/5.
//

#ifndef KNOWLEDGETEST_ASSOCIATIVE_CONTAINER_H
#define KNOWLEDGETEST_ASSOCIATIVE_CONTAINER_H

#include <fstream>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <utility>
#include <sstream>
#include <unordered_map>

void _11_3() {
    std::map<std::string, size_t> word_count;
    std::ifstream ifs("../Resource/article.txt");
    std::istream_iterator<std::string> in(ifs), eof;

    std::for_each(in, eof,
                  [&word_count] (const std::string &word)
                  { ++word_count[word]; });
}

void _11_4() {
    std::map<std::string , size_t > word_count;
    std::ifstream ifs("../Resource/article.txt");
    std::string word;

    while (ifs >> word) {
        for (auto &c : word)
            c = std::tolower(c);
        word.erase(std::remove_if(word.begin(), word.end(), ispunct),
                   word.end());
        ++word_count[word];
    }
}

void _11_7() {
    std::map<std::string, std::vector<std::string>> families;
    std::string f_name;
    std::string children;
    std::cin >> f_name;
    while (std::cin >> children) {
        families[f_name].push_back(children);
    }
}

void _11_12() {
    std::vector<std::pair<std::string, int>> vec;
    std::string str; int i;
    while (std::cin >> str >> i) {
//        vec.push_back(std::pair<std::string, int> (str, i));
        vec.push_back(std::make_pair(str, i));
    }
}

void _11_14() {
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> families;
}

void _11_20() {
    std::ifstream ifs("../Resource/article.txt");
    std::map<std::string, size_t> word_count;
    std::string word;

    while (ifs >> word) {
        for (auto &ch : word)
            ch = std::tolower(ch);
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        auto it = word_count.insert({word, 1});
        if (!it.second) {
            ++it.first->second;
        }
    }
}

void _11_31() {
    std::multimap<std::string, std::string> map;
    std::string author = "li";
    for (auto pos = map.find(author); pos != map.end(); map.erase(pos));

    for (auto & item : map) {
        std::cout << item.first << ": " << item.second << std::endl;
    }
}

std::string transform(const std::string & str, const std::map<std::string, std::string> &map) {
    auto map_it = map.find(str);
    if (map_it != map.end())
        return map_it->second;     // 返回转换后的 string
    else
        return str;     // 返回原 string
}

std::map<std::string, std::string> buildMap(std::ifstream & map_file) {
    std::map<std::string, std::string> trans_rule;
    std::string word, sentence;
    while (map_file >> word && std::getline(map_file, sentence)) {
        if (sentence.size() > 1)        // 检查是否有转换规则
            trans_rule[word] = sentence.substr(1);  // 跳过空格
//            trans_rule.insert({word, sentence.substr(1)});
        else
            throw std::runtime_error("no rule for " + word);
    }
    return trans_rule;
}

void word_transform(std::ifstream & map_file, std::ifstream & input) {
    auto trans_map = buildMap(map_file);
    std::string text;       // 保存输入的每行文本
    while (std::getline(input, text)) {
        std::istringstream stream(text);
        std::string word;
        bool firstword = true;      // 控制是否打印空格
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                std::cout << " ";
            // transform 返回它的第一个参数或者抓换后的形式
            std::cout << transform(word, trans_map);
        }
        std::cout << std::endl;     // 完成一行转换
    }
}

void _11_3_6() {
    std::ifstream map_file("../Resource/convertRule.txt"),
                    input("../Resource/converted.txt");
    word_transform(map_file,input);
}

std::string transform2(const std::string &str, const std::unordered_map<std::string, std::string> & rules) {
    auto map_it = rules.find(str);
    if (map_it != rules.end()) {
        return map_it->second;
    } else {
        return str;
    }
}

std::unordered_map<std::string, std::string> build_map2(std::ifstream & map_file) {
    std::unordered_map<std::string, std::string> rules;
    std::string word, sentence;
    while (map_file >> word && std::getline(map_file, sentence)) {
        if (sentence.size() > 1) {
            rules[word] = sentence;
        } else {
            throw std::runtime_error("no rule for " + word);
        }
    }
    return rules;
}

void word_transform2(std::ifstream & map_file, std::ifstream & input) {
    auto rules = build_map2(map_file);
    std::string text;
    while (std::getline(input, text)) {
        std::string word;
        std::istringstream stream(text);
        bool firstword = true;
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                std::cout << " ";
            std::cout << transform2(word, rules);
        }
        std::cout << std::endl;     // 一行文本转换完毕
    }
}

#endif //KNOWLEDGETEST_ASSOCIATIVE_CONTAINER_H
