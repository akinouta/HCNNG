//
// Created by 秋日的歌 on 2023/8/7.
//

#ifndef HCNNG_VOSERIALIZATION_H
#define HCNNG_VOSERIALIZATION_H
#include "header.h"
#include "VO.h"
void saveVO(std::shared_ptr<VO> &vo,std::string path);
void loadVO(std::shared_ptr<VO> &vo,std::string path);
#endif //HCNNG_VOSERIALIZATION_H
