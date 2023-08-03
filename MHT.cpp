//
// Created by 秋日的歌 on 2023/7/31.
//



#include "header/MHT.h"

std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)input.c_str(), input.length(), hash);
    std::string result;
    result.assign(reinterpret_cast<const char*>(hash),SHA256_DIGEST_LENGTH);
    return result;
}

std::string sha256Vector(float **&data,int p,int dim){
    std::string input;
    for (int i=0;i<dim;i++) {
        // 将浮点数转换为字符串，保留6位小数以确保一致性
        input += std::to_string(data[p][i]) + ",";
    }
    return sha256(input);
}

std::string sha256Edge(Edge e){
    return sha256(std::to_string(e.start)+","+std::to_string(e.end)+","+std::to_string(e.weight));
}

std::string guidedTupleToString(std::shared_ptr<guidedTuple>& gt){
    std::string result;
    for(const auto& i:*gt){
        result+= "<" + i.first + ",";
        for(auto j: *i.second){
            result+= "{" + std::to_string(j) + ",";
        }
        result+="}>";
    }
    return result;
}

void datasetToHash(std::vector<std::string> &nodes, float **&data, int num, int dim){
    for(int i=0;i<num;i++){
        nodes.push_back(sha256Vector(data,i,dim));
    }
}

void graphToHash(std::vector<std::string> &nodes, std::shared_ptr<set_edge> &graph){
    for(auto e:*graph){
        nodes.push_back(sha256Edge(e));
    }
}

void guidedTupleToHash(std::vector<std::string> &nodes, std::shared_ptr<guidedTupleSet> &gts){
    for(const auto& item:*gts){
        int p=item.first;
        auto gt= item.second;
        auto gt_s = guidedTupleToString(gt);
        std::string input= std::to_string(p)+","+gt_s;
        nodes.push_back(sha256(input));
    }
}


std::string buildMerkleTree(std::vector<std::string> &nodes){
    if(nodes.size()==1){
        return nodes.at(0);
    }
    while (nodes.size()!=1){
        std::vector<std::string> new_nodes;
        for(int i=0;i<nodes.size();i+=2){
            std::string concatHash = nodes.at(i);
            if(i+1<nodes.size()){
                concatHash += nodes.at(i+1);
            }
            new_nodes.push_back(sha256(concatHash));
        }
        nodes = new_nodes;
    }
    return nodes.at(0);
}

std::string outsourceDataset(float **&data, int num, int dim){
    std::vector<std::string> nodes;
    datasetToHash(nodes,data,num,dim);
    return buildMerkleTree(nodes);
}

std::string outsourceIndexGraph(std::shared_ptr<set_edge> &hcnng){
    std::vector<std::string> nodes;
    graphToHash(nodes,hcnng);
    return buildMerkleTree(nodes);
}

std::string outsourceGuidedTuple(std::shared_ptr<guidedTupleSet> &gts){
    std::vector<std::string> nodes;
    guidedTupleToHash(nodes,gts);
    return buildMerkleTree(nodes);
}