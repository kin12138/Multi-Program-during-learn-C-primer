//
// Created by libin on 2025/4/17.
//

#include "QueryResult.h"
#include "strBlobPtr.h"

std::ostream & print(std::ostream & os, const QueryResult & qr){
    size_t count = qr.lines->size();
    os << qr.sought << " occurs " << count
    << (count > 1 ? " times " : " time ")
    << "\n";

    // 逐个打印
    for (auto lineno : *qr.lines) {
        strBlobPtr pb(qr.contents, lineno);
        os << "\t(line " << lineno + 1 << ") "
            << pb.deref()
            << "\n";

    }

    return os;
}