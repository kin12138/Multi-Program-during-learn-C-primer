//
// Created by libin on 2025/5/10.
//

#include "QueryResult.h"


std::ostream & print(std::ostream & os, const QueryResult & qr) {
    size_t counts = qr.lines->size();
    os << qr.sought << " occurs " << counts
        << (counts > 1 ? "time" : "times")
        << "\n";

    // 逐个打印
    for (auto & lineNo : *qr.lines) {
        os << "\t(line " << lineNo + 1 << ") "
            << qr.files->at(lineNo)
            << "\n";
    }
    return os;
}