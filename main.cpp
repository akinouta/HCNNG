#include "header/header.h"
#include "header/dataProcess.h"
#include "header/HCNNG.h"
#include "header/guideStructure.h"
#include "header/search.h"
#include "header/MHT.h"
#include "header/dataOwner.h"
#include "header/server.h"

t time_s;
t time_e;
int main() {


    std::string dataPath=R"(D:\soft\CLion\installament\project\HCNNG\dataset\siftsmall_base.fvecs)";


    int k=2;
    int start=2;
    int query=50;

    float **data;
    int num,dim;
    int min_size_cluster = 5;
    int num_cluster = 20;
    load_data(dataPath, data, num, dim);

    num=20;

    std::shared_ptr<int_array> index(new int_array);
    get_range(index,num);

    t_s();
    auto hcnng = CreateHCNNG(data, index, dim, min_size_cluster, num_cluster);
    t_e();

    std::cout << *hcnng;


    t_s();
    std::shared_ptr<guidedTupleSet> gts(new guidedTupleSet);
    get_gts(gts,data,hcnng,num);
    t_e();

    std::cout << "data hash:" << printHash(outsourceDataset(data, num, dim));
    std::cout << "index hash:" << printHash(outsourceIndexGraph(hcnng));
    std::cout << "gts hash:" << printHash(outsourceGuidedTuple(gts));


    float_array qv={1,15,35,5,32,31,14,10,11,78,55,10,45,83,11,6,14,57,102,75,90,8,3,5,67,17,19,26,5,0,1,28,60,26,7,1,18,22,84,53,85,119,119,4,24,18,7,7,1,81,106,102,72,30,6,0,9,1,9,119,72,1,4,33,119,29,6,1,0,1,14,52,119,30,3,0,0,55,92,111,2,5,4,9,22,89,96,14,1,0,1,82,59,16,20,5,25,14,11,4,0,0,1,26,47,23,4,0,0,4,38,83,30,14,9,4,9,17,23,41,0,0,2,8,19,25,23,1};


//    t_s();
//    std::shared_ptr<max_queue> knn(new max_queue);
//    search(knn,k,data,gts,start,qv,dim);
//    std::cout << *knn;
//    t_e();

    return 0;
}
