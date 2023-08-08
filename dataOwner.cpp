//
// Created by 秋日的歌 on 2023/8/8.
//
#include "header/dataOwner.h"

void dataOwner(
        std::string &hash,
        std::string &dataPath,
        float **&data,
        int &num,
        int &dim,
        int &min_size_cluster,
        int &num_cluster
        ){



    load_data(dataPath, data, num, dim);
//    num=5000;


    std::shared_ptr<int_array> index(new int_array);
    get_range(index,num);

    t_s();
    auto hcnng = CreateHCNNG(data, index, dim, min_size_cluster, num_cluster);
    t_e();
//    std::cout << *hcnng;


    t_s();
    std::shared_ptr<guidedTupleSet> gts(new guidedTupleSet);
    get_gts(gts,data,hcnng,num);
    t_e();

    saveGuidedTuple(gts,guideTuplePath);
    hash = outsourceVGT(gts,data,num,dim);
    std::cout<<printHash(hash);
}
