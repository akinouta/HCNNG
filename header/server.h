//
// Created by 秋日的歌 on 2023/8/8.
//

#ifndef HCNNG_SERVER_H
#define HCNNG_SERVER_H
#include "header.h"
#include "dataProcess.h"
#include "search.h"
#include "dataSerialization.h"
#include "VO.h"
void server(
        std::shared_ptr<max_queue> knn,
        std::shared_ptr<guidedTupleSet> &result_gts,
        float **&data,
        int &num,
        int &dim,
        int &k,
        int &start,
        int &query,
        float_array &qv
);
#endif //HCNNG_SERVER_H
