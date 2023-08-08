//
// Created by 秋日的歌 on 2023/8/8.
//

#ifndef HCNNG_DATAOWNER_H
#define HCNNG_DATAOWNER_H
#include "dataProcess.h"
#include "HCNNG.h"
#include "guideStructure.h"
#include "VO.h"

void dataOwner(
        std::string &hash,
        std::string &dataPath,
        float **&data,
        int &num,
        int &dim,
        int &min_size_cluster,
        int &num_cluster
);


#endif //HCNNG_DATAOWNER_H
