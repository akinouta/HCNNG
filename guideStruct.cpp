//
// Created by 秋日的歌 on 2023/5/18.
//
#include "header/guideStructure.h"

void get_all_neighbors(std::shared_ptr<neighbors> &neighbors,
                       std::shared_ptr<set_edge> &graph,
                       int num){
//    neighbors->reserve(num);

    neighbors->resize(num, nullptr);
    for(int i=0;i<num;i++){
        neighbors->at(i).reset(new int_array);
    }

    for(auto e:*graph){
        neighbors->at(e.start)->push_back(e.end);
        neighbors->at(e.end)->push_back(e.start);
    }
}

//void get_spts(std::vector<SPT> *&spts,float **&data,neighbors *&neighbors,int num,int dim_now){
//    for(int i=0;i<neighbors->size();i++){
//        for(int j=0;j<neighbors->at(i).size();j++){
//
//        }
//    }
//}

std::shared_ptr<SPT> get_spt(float **&data,
                             int p,
                             std::shared_ptr<int_array> &neighbor,
                             int dim_now) {
    std::shared_ptr<SPT> spt(new SPT(dim_now+1));
    std::shared_ptr<int_array> neg(new int_array);
    std::shared_ptr<int_array> pos(new int_array);

    for (auto n: *neighbor) {
        if (data[n][dim_now] < data[p][dim_now]) {
            neg->push_back(n);
        } else {
            pos->push_back(n);
        }
    }

    if (neg->empty() || pos->empty()) {
        spt->isLeaf = true;
        spt->points = neighbor;
    } else {
        spt->neg = get_spt(data, p, neg, dim_now + 1);
        spt->pos = get_spt(data, p, pos, dim_now + 1);
    }

    return spt;
}

void get_all_spt(std::shared_ptr<SPTs> &spts,
                 float **&data,
                 std::shared_ptr<set_edge> &graph,
                 int num){

    std::shared_ptr<neighbors> ns(new neighbors);

    get_all_neighbors(ns,graph, num);
    for(int i=0;i<ns->size();i++){
//        std::shared_ptr<int_array> n(&ns->at(i));
        auto spt = get_spt(data,i,ns->at(i),0);
        spts->push_back(spt);

//        std::cout << "---" << i << "---" << std::endl;
//        std::cout << *spt;
//        std::cout << "***" << i << "***" << std::endl;
    }
}

void search_neighbor(std::shared_ptr<int_array> &neighbor,
                     std::shared_ptr<SPT> &spt,
                     float **&data,
                     int now,
                     int query,
                     int dim_now){
    if(spt->isLeaf){
        neighbor=spt->points;
    } else {
        if(data[query][dim_now] < data[now][dim_now]){
            search_neighbor(neighbor,spt->neg,data,now,query,dim_now+1);
        } else {
            search_neighbor(neighbor,spt->pos,data,now,query,dim_now+1);
        }
    }
}
