//
// Created by 秋日的歌 on 2023/5/18.
//
#include "header/spt.h"

SPT::SPT():neg(nullptr),pos(nullptr),points(nullptr),isLeaf(false),level(0) {}
SPT::SPT(int level):neg(nullptr),pos(nullptr),points(nullptr),isLeaf(false),level(level) {}

std::ostream& operator<<(std::ostream& os, const SPT& node){
    if(!node.isLeaf){
//        if(node.neg->isLeaf){
            os << "neg:";
//        }
        os << *node.neg;
//        if(node.pos->isLeaf){
            os << "pos:";
//        }
        os << *node.pos;
    }
    else{
        os << "level:" << node.level << std::endl;
        if(node.points== nullptr){
            os << "empty" << std::endl;
        }
        else{
            os << "{ ";
            for(auto p:*(node.points)){
                os << p << " ";
            }
            os << "}" <<std::endl;
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const SPTs &spts){
    for(int i=0;i<spts.size();i++){
        os << "---" << i << "---" << std::endl;
        os << *(spts.at(i));
        os << "***" << i << "***" << std::endl;
    }
    return os;
}