//
// Created by 秋日的歌 on 2023/7/31.
//

#ifndef HCNNG_MHT_H
#define HCNNG_MHT_H
#include "header.h"
#include "dataProcess.h"
#include "MST.h"
std::string sha256(const std::string& input);
std::string sha256Vector(float **&data,int p,int dim);
std::string sha256Edge(Edge e);
std::string guidedTupleToString(std::shared_ptr<guidedTuple>& gt);
void datasetToHash(std::vector<std::string> &nodes, float **&data, int num, int dim);
void graphToHash(std::vector<std::string> &nodes, std::shared_ptr<set_edge> &graph);
void guidedTupleToHash(std::vector<std::string> &nodes, std::shared_ptr<guidedTupleSet> &gts);

std::string buildMerkleTree(std::vector<std::string> &nodes);

std::string outsourceDataset(float **&data, int num, int dim);
std::string outsourceIndexGraph(std::shared_ptr<set_edge> &hcnng);
std::string outsourceGuidedTuple(std::shared_ptr<guidedTupleSet> &gts);
#endif //HCNNG_MHT_H


// 构建 Merkle 哈希树
//std::string buildMerkleTree(const std::vector<std::vector<float>>& dataset) {
//    if (dataset.empty()) {
//        return "";
//    }
//
//    if (dataset.size() == 1) {
//        // 对单个向量进行哈希
//        return sha256Vector(dataset[0]);
//    }
//
//    std::vector<std::string> newLevel;
//    for (size_t i = 0; i < dataset.size(); i += 2) {
//        std::string concatHash = sha256Vector(dataset[i]);
//        if (i + 1 < dataset.size()) {
//            concatHash += sha256Vector(dataset[i + 1]);
//        }
//        newLevel.push_back(sha256(concatHash));
//    }
//
//    return buildMerkleTree(newLevel);
//}

