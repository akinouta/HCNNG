#include "header/header.h"
#include "header/dataProcess.h"
#include "header/HCNNG.h"
#include "header/guideStructure.h"
#include "header/search.h"

t time_s;
t time_e;
int main() {


    std::string dataPath=R"(D:\soft\CLion\installament\project\HCNNG\dataset\siftsmall_base.fvecs)";


    int k=2;
    int start=2;
    int query=50;

    float **data;
    int num,dim;
    int min_size_cluster = 1000;
    int num_cluster = 20;
    load_data(dataPath, data, num, dim);


//    num=100;

    std::shared_ptr<int_array> index(new int_array);
//    get_random_range(index,num,0,1000);
    get_range(index,num);

//    std::shared_ptr<set_edge> mst(new set_edge);
//    MST3(mst,data,index,dim);
//    std::cout << *mst;
//    std::cout << mst->size() <<std::endl;


//    auto hcnng=HierarchicalClustering(data, index, min_size_cluster, dim);
//    std::cout << *hcnng ;
//    std::cout << hcnng->size() <<std::endl;


    t_s();
    auto hcnng = CreateHCNNG(data, index, dim, min_size_cluster, num_cluster);
    std::shared_ptr<neighbors> nb(new neighbors);
    t_e();
    t_s();
    get_all_neighbors(nb,hcnng ,num);
//    std::cout << *nb;
    std::shared_ptr<SPTs> spts(new SPTs);
    get_all_spt(spts,data,hcnng,num);
    t_e();



//    std::cout << *hcnng;
//    std::cout << hcnng->size() <<std::endl;


//    std::cout << *spts->at(1);

//    int test=1;
//    std::shared_ptr<int_array> part(new int_array);
//
//    search_neighbor(part,spts->at(test),data,test,28,0);
//    show_index(part);



    t_s();
    std::shared_ptr<max_queue> knn(new max_queue);
    search(knn,k,data,hcnng,spts,start,query,dim);
    std::cout << *knn;
    t_e();

    max_queue test;
    for(auto i:*index){
        test.emplace(i, distance(data,i,query,dim));
    }
    std::cout << test;

    return 0;
}
