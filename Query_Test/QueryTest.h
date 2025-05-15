//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_QUERYTEST_H
#define QUERY_TEST_QUERYTEST_H
#include "Query.h"
#include "AndQuery.h"
#include "OrQuery.h"

void _15_36(){
    std::ifstream ifs("../Resource/letter.txt");
    TextQuery tq(ifs);
    Query q = Query("fiery") & Query("bird") | Query("wind");
    std::cout << "\n";
    std::cout << q;
    std::cout << "\n";
    print(std::cout, q.eval(tq));
}
#endif //QUERY_TEST_QUERYTEST_H
