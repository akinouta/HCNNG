//
// Created by 秋日的歌 on 2023/5/16.
//
#include "header/HCNNG.h"


void MST3(std::shared_ptr<set_edge> &mst,float **&data, std::shared_ptr<int_array> &index, int dim){

//    std::shared_ptr<set_edge> full(new set_edge);
//
//    fullGraph(full,data,index, dim);
//    kruskal(mst, full,index);

    std::shared_ptr<MGraph> full(new MGraph);
    fullGraph(full,data,index, dim);
    prim(mst,full,index);
}

std::shared_ptr<set_edge> HierarchicalClustering(float **&data,
                                                 std::shared_ptr<int_array> &index,
                                                 int min_size_cluster,
                                                 int dim){
    int size_index = static_cast<int>(index->size());
    int p1,p2;

    std::shared_ptr<int_array> index1(new int_array);
    std::shared_ptr<int_array> index2(new int_array);


    std::shared_ptr<set_edge> e(new set_edge);
    std::shared_ptr<set_edge> e1(new set_edge);
    std::shared_ptr<set_edge> e2(new set_edge);


    if (size_index<min_size_cluster){
        MST3(e, data, index, dim);
    }
    else
    {
        get_two_rand(p1,p2,index);

        for(auto p:*index){
            if (distance(data,p,p1,dim)<distance(data,p,p2,dim)){
                index1->push_back(p);
            } else{
                index2->push_back(p);
            }
        }
        e1 = HierarchicalClustering(data,index1, min_size_cluster, dim);
        e2 = HierarchicalClustering(data,index2, min_size_cluster, dim);
        e->insert(e1->begin(),e1->end());
        e->insert(e2->begin(),e2->end());
    }
    return e;
}

std::shared_ptr<set_edge> CreateHCNNG(float **&data,std::shared_ptr<int_array> &index, int dim,int min_size_cluster, int num_cluster){

    std::shared_ptr<set_edge> hcnng(new set_edge);
    for(int i=0;i<num_cluster;i++){
        auto tmp=HierarchicalClustering(data, index, min_size_cluster, dim);
        hcnng->insert(tmp->begin(),tmp->end());
    }
    return hcnng;
}