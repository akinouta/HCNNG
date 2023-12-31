#include "header/header.h"
#include "header/dataOwner.h"
#include "header/server.h"

t time_s;
t time_e;

int main() {


    std::string dataPath=R"(D:\soft\CLion\installament\project\HCNNG\dataset\siftsmall_base.fvecs)";
    //参数
    float **data;
    int num,dim;
    int min_size_cluster = 5;
    int num_cluster = 20;
    //结果
    std::string hash;
    dataOwner(hash,dataPath,data,num,dim,min_size_cluster,num_cluster);



    //参数
    int k=2;
    int start=2;
    int query=50;
    float_array qv={1,15,35,5,32,31,14,10,11,78,55,10,45,83,11,6,14,57,102,75,90,8,3,5,67,17,19,26,5,0,1,28,60,26,7,1,18,22,84,53,85,119,119,4,24,18,7,7,1,81,106,102,72,30,6,0,9,1,9,119,72,1,4,33,119,29,6,1,0,1,14,52,119,30,3,0,0,55,92,111,2,5,4,9,22,89,96,14,1,0,1,82,59,16,20,5,25,14,11,4,0,0,1,26,47,23,4,0,0,4,38,83,30,14,9,4,9,17,23,41,0,0,2,8,19,25,23,1};
    //结果
    std::shared_ptr<max_queue> knn(new max_queue);
    std::shared_ptr<guidedTupleSet> visited_gts(new guidedTupleSet);
    server(knn, visited_gts, data, num, dim, k, start, query, qv);


    QueryReslutAuthentication(knn, visited_gts, hash, data, dim, k, start, qv);

    return 0;
}

