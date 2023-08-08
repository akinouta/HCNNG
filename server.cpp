//
// Created by 秋日的歌 on 2023/8/8.
//

#include "header/server.h"
void server(
        std::shared_ptr<max_queue> knn,
        std::shared_ptr<guidedTupleSet> &visited_gts,
        float **&data,
        int &num,
        int &dim,
        int &k,
        int &start,
        int &query,
        float_array &qv
        ){
    t_s();
    std::shared_ptr<int_set> visited(new int_set);
    std::shared_ptr<guidedTupleSet> gts(new guidedTupleSet);
    loadGuidedTuple(gts,guideTuplePath);
    search(knn,visited,k,data,gts,start,qv,dim);
    std::cout << *knn;
    t_e();
    VO_construction(gts, data, num, dim, visited);
    for(auto v:*visited){
        visited_gts->insert(std::make_pair(v,gts->at(v)));
    }
}