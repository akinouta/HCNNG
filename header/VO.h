//
// Created by 秋日的歌 on 2023/8/5.
//

#ifndef HCNNG_VO_H
#define HCNNG_VO_H
#include "header.h"
#include "MHT.h"

class VO_node{
public:
    std::string data;
    bool flag; //flag==0代表为hash值
    int level;
    friend std::ostream& operator<<(std::ostream& os, const VO_node& node);
};
typedef std::vector<VO_node> VO;
std::ostream& operator<<(std::ostream& os, const VO &VO);
void VOconstruction(float ** &data, int &num, int &dim,std::shared_ptr<int_set> &visited);

#endif //HCNNG_VO_H
