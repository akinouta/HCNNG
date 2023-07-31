//
// Created by 秋日的歌 on 2023/5/15.
//

#ifndef HCNNG_SPT_H
#define HCNNG_SPT_H

#include "header.h"
#include "dataProcess.h"
typedef std::map<std::string,std::shared_ptr<int_array>> guidedTuple;
typedef std::map<int,std::shared_ptr<guidedTuple>> guidedTupleSet;
/*
 * 分割树
 */
class SPT{
public:
    std::shared_ptr<SPT> neg;
    std::shared_ptr<SPT> pos;
    std::shared_ptr<int_array> points;
    bool isLeaf;
    int level;
    SPT();
    explicit SPT(int level);
    friend std::ostream& operator<<(std::ostream& os, const SPT& node);
};

typedef std::vector<std::shared_ptr<SPT>> SPTs;
std::ostream& operator<<(std::ostream& os, const SPTs &spts);

#endif //HCNNG_SPT_H