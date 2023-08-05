//
// Created by 秋日的歌 on 2023/8/5.
//
#include "header/VO.h"
std::ostream& operator<<(std::ostream& os, const VO_node& node) {
    if(!node.flag){
        os << "[ ";
        os << std::hex << std::noshowbase;
        for (unsigned char ch : node.data) {
            os << std::setw(2) << std::setfill('0') << static_cast<int>(ch) << " ";
        }
        os << std::dec;
        os << "]," << node.level;
    } else{
        os << node.data << "," << node.level;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const VO &VO){
    for(const auto& node:VO){
        os << node << std::endl;
    }
    return os;
}

void VOconstruction(float ** &data, int &num, int &dim,std::shared_ptr<int_set> &visited){
    std::vector<VO_node> VO_data;
    int i,l;
    VO_data.reserve(num);
    for(i=0;i<num;i++){
        if(visited->find(i) == visited->end()){
            //in set
            VO_data.push_back({sha256Vector(data,i,dim), false, 0});
        }
        else{
            VO_data.push_back({std::to_string(i), true, 0});
            if(visited->empty()){
                break;
            }else{
                visited->erase(i);
            }
        }
    }
    std::cout << VO_data;

    for(l=1;l<num;l*=2){
        std::vector<VO_node> new_VO_data;
        int l1=static_cast<int>(VO_data.size());
        for(i=0;i<l1;i+=2){
            if(i+1<l1 && !VO_data.at(i).flag && !VO_data.at(i+1).flag){
                new_VO_data.push_back({
                    sha256(VO_data.at(i).data + VO_data.at(i + 1).data),
                    false,
                    VO_data.at(i).level + 1
                });
//                std::cout << std::endl << VO_data;
            } else{
                new_VO_data.push_back({VO_data.at(i).data,VO_data.at(i).flag,VO_data.at(i).level});
                if(i+1<l1){
                    new_VO_data.push_back({VO_data.at(i+1).data,VO_data.at(i+1).flag,VO_data.at(i+1).level});
                }
            }
        }
        VO_data = new_VO_data;
    }
    std::cout << std::endl << VO_data;
}