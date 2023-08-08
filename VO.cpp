//
// Created by 秋日的歌 on 2023/8/7.
//
//
// Created by 秋日的歌 on 2023/8/5.
//
#include "header/VO.h"
#include "header/VOSerialization.h"
std::ostream& operator<<(std::ostream& os, const VO_node& node) {
    if(!node.flag){
        os << "[ ";
        os << std::hex << std::noshowbase;
        for (unsigned char ch : node.data) {
            os << std::setw(2) << std::setfill('0') << static_cast<int>(ch) << " ";
        }
        os << std::dec;
        os << "],level:" << node.level<<",site:"<<node.site<<std::endl;
    } else{
        os << node.data << ",level:" << node.level<<",site:"<<node.site<<std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const VO &VO){
    os<<"------------------start------------------"<<std::endl;
    for(const auto& node:VO){
        os << node << std::endl;
    }
    os<<"-------------------end-------------------"<<std::endl;

    return os;
}

void VO_construction(
        const std::shared_ptr<guidedTupleSet>& gts,
        float ** &data,
        int &num,
        int &dim,
        std::shared_ptr<int_set> &visited
){
    std::shared_ptr<VO> vo(new VO);
    vo->reserve(num);
    for(int i=0;i<num;i++){
        if(visited->find(i) == visited->end()){
            //in set
            vo->push_back({sha256VGT(gts->at(i), data, i, dim), false, 0, i});
        }
        else{
            vo->push_back({std::to_string(i), true, 0, i});
        }
    }
//    std::cout << *vo;

    for(int l=1;l<num;l*=2){
        VO new_vo;
        int size_vo=static_cast<int>(vo->size());
        for(int i=0; i < size_vo; i++){
            if(i+1 < size_vo
                && vo->at(i).site%2==0
                && !vo->at(i).flag
                && !vo->at(i + 1).flag
                && vo->at(i).level==vo->at(i+1).level
                ){
                new_vo.push_back({
                                              sha256(vo->at(i).data + vo->at(i + 1).data),
                                              false,
                                              vo->at(i).level + 1,
                                              vo->at(i).site/2
                                      });
                i++;
            } else{
                new_vo.push_back(vo->at(i));
            }
        }
        *vo = new_vo;
    }
    saveVO(vo, VOPath);
}

void QueryReslutAuthentication(std::shared_ptr<max_queue> knn,
                               std::shared_ptr<guidedTupleSet> &visited_gts,
                               std::string &hash,
                               float **&data,
                               int &dim,
                               int &k,
                               int &start,
                               float_array &qv){
    std::shared_ptr<VO> vo;

    int p;
    loadVO(vo,VOPath);
    for(auto & i : *vo){
        if(i.flag) {
            p = std::stoi(i.data);
            i.data = sha256VGT(visited_gts->at(p), data, p, dim);
            i.flag = false;
        }
    }

    while(vo->size()!=1){
        VO new_vo;
        auto vo_size = static_cast<int>(vo->size());
        for(int i=0;i<vo_size;i++){
            //向上合并
            if(i+1<vo_size && vo->at(i).site%2==0 && vo->at(i).level==vo->at(i+1).level) {
                new_vo.push_back(
                        {
                                sha256(vo->at(i).data + vo->at(i + 1).data),
                                false,
                                vo->at(i).level + 1,
                                vo->at(i).site/2
                        });
                i++;
            }else{
                new_vo.push_back(vo->at(i));
            }
        }
        auto last=new_vo.size()-1;
        if(last>0 && new_vo.at(last).level < new_vo.at(last-1).level){
            auto difference = new_vo.at(last-1).level - new_vo.at(last).level;
            new_vo.at(last).level=new_vo.at(last-1).level;
            for(int ii=0;ii<difference;ii++){
                new_vo.at(last).data= sha256(new_vo.at(last).data);
                new_vo.at(last).site/=2;
            }

        }
//        std::cout<<*vo;
        *vo=new_vo;
    }

    auto hash_=vo->at(0).data;
    if(hash_ == hash){
        print("hash pass");
    }else{
        printf("hash not pass");
    }

    if(knn->size() == k){
        print("k pass");
    }else{
        printf("k not pass");
    }

    std::shared_ptr<max_queue> knn_(new max_queue);
    search(knn_,k,data,visited_gts,start,qv,dim);

    if(isEqualKnn(*knn,*knn_)){
            print("pass");
        }else{
            printf("not pass");
        }

}