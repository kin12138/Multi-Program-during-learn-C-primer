//
// Created by libin on 2025/3/30.
//

#ifndef KNOWLEDGETEST_GENERICALGORITHM_H
#define KNOWLEDGETEST_GENERICALGORITHM_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <iterator>

void _10_1() {
    std::vector<int> vec;
    int val;
    while (std::cin >> val) {
        vec.emplace_back(val);
    }

    int target = 5;
    std::cout << std::count(vec.cbegin(), vec.cend(), target) << std::endl;
}

void _10_2() {
    std::list<std::string> lst;
    std::string str;
    while (std::cin >> str) {
        lst.emplace_back(str);
    }
    std::cout << std::count(lst.cbegin(), lst.cend(), "a");
}

void _10_6() {
    std::vector<int> vec;

    vec.reserve(10);
    std::fill_n(vec.begin(), 10, 0);
//    std::fill_n(vec.begin(), vec.size(), 0);
//
//    auto iter = std::back_inserter(vec);
//    std::fill_n(iter, vec.size(), 0);
}

void _10_9() {
    std::vector<std::string> vec{"sdfa", "wo", "wo", "wo", "i", "i", "i", "love", "love", "love"};
    std::sort(vec.begin(), vec.end());
    auto end_unique = std::unique(vec.begin(), vec.end());
    for(auto & item : vec) {
        std::cout << item << " ";
    }
    std::cout << "\n";
    vec.erase(end_unique, vec.end());
    for(auto & item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

bool isShorter(const std::string & s1, const std::string & s2) {
    return s1.size() < s2.size();
}

void _10_11() {
    std::vector<std::string> vec{"sdfa", "wo", "wo", "wo", "i", "i", "i", "love", "love", "love"};
    std::stable_sort(vec.begin(), vec.end(), isShorter);
    for(auto & item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    auto end_unique = std::unique(vec.begin(), vec.end());
    vec.erase(end_unique, vec.end());

    for(auto & item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

bool compareSize(const std::string & s) {
    return s.size() >= 5;
}

void _10_13() {
    std::vector<std::string> vec{"fd", "fds", "qw", "123", "fdasf", "dfsdafd", "afd", "fadsf", "dfasdsaf", "fdakhuiohiohu"};
    auto end_true = std::partition(vec.begin(), vec.end(), compareSize);
    for (auto it = vec.begin(); it != end_true; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void elimDups(std::vector<std::string> & words) {
    std::sort(words.begin(), words.end());
    auto iter = std::unique(words.begin(), words.end());
    words.erase(iter, words.end());
}

std::string make_plural(size_t count, const std::string & str, const std::string & ending) {
    return count > 1 ? str + ending : str;
}

void biggies(std::vector<std::string> & words, std::vector<std::string>::size_type sz) {
    // 将 words 按字典序排序，删除重复元素
    elimDups(words);
    // 按长度排序，长度相同的维持字典序
    std::stable_sort(words.begin(), words.end(),
                     [] (const std::string & s1, const std::string & s2)
                     { return s1.size() < s2.size();});
    // 获取一个迭代器，指向第一个满足 size() >= sz 的元素

//    auto wc = std::find_if(words.begin(), words.end(),
//                           [sz] (const std::string & s)
//                           { return s.size() >= sz;});
    // 使用 partition 算法代替 find_if
//    auto wc = std::partition(words.begin(), words.end(),
//                             [sz] (const std::string & s)
//                             { return s.size() < sz; });
    // 使用 stable_partition 算法
    auto wc = std::stable_partition(words.begin(), words.end(),
                                    [sz] (const std::string &s)
                                    { return s.size() < sz; });
    // 计算满足 size() >= sz 的元素数量
    auto count = words.end() - wc;
    std::cout << count << " " << make_plural(count, "word", "s") << " of length " << sz
                << " or longer." << std::endl;
    // 打印长度大于等于给定值的单词，每个单词后接一个空格
    std::for_each(wc, words.end(),
                  [sz] (const std::string & s)
                  {std::cout << s << " ";});
    std::cout << std::endl;
}

void testBiggies() {
    std::vector<std::string> words{"fd", "fds", "qw", "123", "fdasf", "dfsdafd", "afd", "fadsf", "dfasdsaf", "fdakhuiohiohu"};
    biggies(words, 5);
}

void _10_20() {
    std::vector<std::string> words{"fd", "fds", "qw", "123", "fdasf", "dfsdafd", "afd", "fadsf", "dfasdsaf", "fdakhuiohiohu"};
    std::cout << std::count_if(words.begin(), words.end(),
                               [](const std::string &s)
                               { return s.size() > 6; })
                               << std::endl;
}

void _10_21() {
    int val = 10;
    auto f = [&] () -> bool {
        while (val != 0) {--val;} return true;
    };
    std::cout << f() << std::endl;
}

void _10_27() {
    std::vector<int> vec{1,1, 2,2,2,3,3,4,4,5,5,5,6,6,7,7};
    std::list<int> lst;
    std::unique_copy(vec.begin(), vec.end(), std::inserter(lst, lst.begin()));

    for (const auto & item : lst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void _10_29() {
    std::ifstream ifs("../Resource/letter.txt");
    std::istream_iterator<std::string> cin_str(ifs), eof;
    std::vector<std::string> vec(cin_str, eof);
}

void _10_30() {
    std::istream_iterator<int> in_int(std::cin), eof;
    std::ostream_iterator<int> out_int(std::cout, " ");
    std::vector<int> vec(in_int, eof);
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), out_int);
    std::cout << std::endl;
}

void _10_31() {
    std::istream_iterator<int> in_int(std::cin), eof;
    std::vector<int> vec(in_int, eof);
    std::sort(vec.begin(), vec.end());
    std::unique_copy(vec.begin(), vec.end(), std::ostream_iterator<int> (std::cout, " "));
    std::cout << std::endl;
}

void divide_odd_even(const std::string & input_filename,
                     const std::string & output_odd_filename, const std::string & output_even_filename) {
    std::ifstream ifs(input_filename);
    std::ofstream ofs_odd(output_odd_filename), ofs_even(output_even_filename);

    std::istream_iterator<int> in_iter(ifs), eof;
    std::ostream_iterator<int> out_odd(ofs_odd, " "), out_even(ofs_even, " ");

    std::for_each(in_iter, eof,
                  [&out_odd, &out_even] (const int i)
                  {
                      *(i & 0x1 ? out_odd : out_even)++ = i;
                  });
}

void _10_33() {
    std::string inputFile("../Resource/number.txt"),
                outputOdd("../Resource/odd.txt"), outputEven("../Resource/even.txt");

    std::ofstream ofs(inputFile);
    std::vector<int> vec{1,1, 2,2,2,3,3,4,4,5,5,5,6,6,7,7};
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(ofs, " "));
    ofs.close();

    divide_odd_even(inputFile, outputOdd, outputEven);
}

void _10_34() {
    std::vector<int> vec{1,1, 2,2,2,3,3,4,4,5,5,5,6,6,7,7};
    std::for_each(vec.rbegin(), vec.rend(),
                  [] (const int i) { std::cout << i << " ";});
}

void _10_35() {
    std::vector<int> vec{1,1, 2,2,2,3,3,4,4,5,5,5,6,6,7,7};
    ;
    std::ostream_iterator<int> out(std::cout, " ");
    for (auto it = --vec.end(); true; --it) {
        *out++ = *it;
        if (it == vec.begin()) break;
    }
    std::cout << std::endl;
}

void _10_36() {
    std::list<int> lst{1,1, 2,2,0,2,3,3,4,4,5,0,0,5,5,6,6,7,7};
    auto it = std::find(lst.crbegin(), lst.crend(), 0);
    std::cout << std::distance(it, lst.crend()) << std::endl;
}

void _10_37() {
    std::vector<int> vec{1, 2, 3, 4 ,5 ,67, 7, 8, 9, 10};
    std::copy(vec.crbegin()+ 2, vec.crbegin() + 7, std::ostream_iterator<int>(std::cout, " "));
}

#endif //KNOWLEDGETEST_GENERICALGORITHM_H
