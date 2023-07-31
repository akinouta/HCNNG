//
// Created by 秋日的歌 on 2023/5/25.
//

#ifndef HCNNG_SEARCH_H
#define HCNNG_SEARCH_H

#include "spt.h"
#include "MST.h"
#include "guideStructure.h"

class Compare {
public:
    bool operator()(std::pair<int,float> a, std::pair<int,float> b) const;
};
class Compare2 {
public:
    bool operator()(std::pair<int,float> a, std::pair<int,float> b) const;
};

typedef std::priority_queue<std::pair<int,float>, std::deque<std::pair<int,float>>, Compare> min_queue;
typedef std::priority_queue<std::pair<int,float>, std::deque<std::pair<int,float>>, Compare2> max_queue;

std::ostream& operator<<(std::ostream& os, const max_queue &queue);

void search(std::shared_ptr<max_queue> &nn,
            int k,
            float **&data,
            std::shared_ptr<SPTs> &spts,
            int start,
            int query,
            int dim);

void search(std::shared_ptr<max_queue> &nn,
            int k,
            float **&data,
            std::shared_ptr<SPTs> &spts,
            int start,
            float_array query,
            int dim);

#endif //HCNNG_SEARCH_H
