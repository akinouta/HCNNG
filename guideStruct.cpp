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

void get_gt(std::shared_ptr<guidedTuple> gt,
            float **&data,
            int p,
            std::shared_ptr<int_array> &neighbor,
            std::string id,
            int dim_now){
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
        gt->insert(std::make_pair(id,neighbor));
    } else {
        get_gt(gt, data, p, neg,id.append("0"), dim_now + 1);
        get_gt(gt, data, p, pos,id.append("1"), dim_now + 1);
    }

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

void get_gts(std::shared_ptr<guidedTupleSet> &gts,
             float **&data,
             std::shared_ptr<set_edge> &graph,
             int num){
    std::shared_ptr<neighbors> ns(new neighbors);
    get_all_neighbors(ns,graph, num);
    for(int i=0;i<ns->size();i++){
        std::shared_ptr<guidedTuple> gt(new guidedTuple);
        get_gt(gt,data,i,ns->at(i),"",0);
        gts->insert(std::make_pair(i,gt));
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


void search_neighbor(std::shared_ptr<int_array> &neighbor,
                     std::shared_ptr<SPT> &spt,
                     float **&data,
                     int now,
                     float_array query,
                     int dim_now){
    if(spt->isLeaf){
        neighbor=spt->points;
    } else {
        if(query[dim_now] < data[now][dim_now]){
            search_neighbor(neighbor,spt->neg,data,now,query,dim_now+1);
        } else {
            search_neighbor(neighbor,spt->pos,data,now,query,dim_now+1);
        }
    }
}


void search_neighbor(std::shared_ptr<int_array> &neighbor,
                     std::shared_ptr<guidedTuple> &gt,
                     float **&data,
                     int now,
                     int query,
                     int dim){
    std::string judge,max_code;
    int max=0;
    judge.resize(dim);
    for(int i=0;i<dim;i++){
        if(data[now][i]<data[query][i]){
            judge[i]='0';
        }
        else{
            judge[i]='1';
        }
    }
    for(const auto& code:*gt){
        int i;
        for(i=0;i<code.first.size();i++){
            if(code.first[i]!=judge[i]){
                if(i>max){
                    max=i;
                    max_code=code.first;
                    break;
                }
            }
        }
        if(i==code.first.size()){
            max=i;
            max_code=code.first;
        }
    }
    neighbor = gt->at(max_code);
}

void search_neighbor(std::shared_ptr<int_array> &neighbor,
                     std::shared_ptr<guidedTuple> &gt,
                     float **&data,
                     int now,
                     float_array query,
                     int dim){
    std::string judge,max_code;
    int max=0;
    judge.resize(dim);
    for(int i=0;i<dim;i++){
        if(data[now][i]<query[i]){
            judge[i]='0';
        }
        else{
            judge[i]='1';
        }
    }
    for(const auto& code:*gt){
        int i;
        for(i=0;i<code.first.size();i++){
            if(code.first[i]!=judge[i]){
                if(i>max){
                    max=i;
                    max_code=code.first;
                    break;
                }
            }
        }
        if(i==code.first.size()){
            max=i;
            max_code=code.first;
            break;
        }
    }
    neighbor = (*gt)[max_code];
}