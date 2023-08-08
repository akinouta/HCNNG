//
// Created by 秋日的歌 on 2023/8/5.
//

#ifndef HCNNG_VO_H
#define HCNNG_VO_H
#include "header.h"
#include "MHT.h"
#include "dataSerialization.h"
#include "search.h"


class VO_node{
public:
    std::string data;
    bool flag; //flag==0代表为hash值
    int level;
    int site;
    friend std::ostream& operator<<(std::ostream& os, const VO_node& node);
    template<class Archive>
    void serialize(Archive &archive) {
        archive(data,flag,level,site);
    }
};
template void VO_node::serialize<cereal::BinaryOutputArchive>(cereal::BinaryOutputArchive&);

typedef std::vector<VO_node> VO;
std::ostream& operator<<(std::ostream& os, const VO &VO);
void VO_construction(const std::shared_ptr<guidedTupleSet>& gts, float ** &data, int &num, int &dim, std::shared_ptr<int_set> &visited);
void QueryReslutAuthentication(std::shared_ptr<max_queue> knn,
                               std::shared_ptr<guidedTupleSet> &visited_gts,
                               std::string &hash,
                               float **&data,
                               int &dim,
                               int &k,
                               int &start,
                               float_array &qv);
#endif //HCNNG_VO_H
