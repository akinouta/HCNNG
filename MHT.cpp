//
// Created by 秋日的歌 on 2023/7/31.
//

#include "header/MHT.h"

std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)input.c_str(), input.length(), hash);

    std::string result;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        result += hash[i];
    }
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

void datasetToHash(std::vector<std::string> &nodes, float **&data, int num, int dim){
    for (int i = 0; i < num; i += 2) {
        std::string concatHash = sha256Vector(data,i,dim);
        if (i + 1 < num) {
            concatHash += sha256Vector(data,i+1,dim);
        }
        nodes.push_back(sha256(concatHash));
    }
}

std::string buildMerkleTree(std::vector<std::string> &nodes){
    if(nodes.size()==1){
        return nodes.at(0);
    }
    while (nodes.size()>1){
        std::vector<std::string> new_nodes;
        for(int i=0;i<nodes.size();i+=2){
            std::string concatHash = sha256(nodes.at(i));
            if(i+1<nodes.size()){
                concatHash += sha256(nodes.at(i+1));
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