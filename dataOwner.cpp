//
// Created by 秋日的歌 on 2023/8/2.
//

#include "header/dataOwner.h"


//void saveEdge(std::shared_ptr<set_edge> graph){
//    std::string filePath="header/index_graph.bin";
//    std::ofstream outputFile(filePath, std::ios::binary);
//    if (outputFile.is_open()) {
//        for (auto item : *graph) {
//            outputFile.write(reinterpret_cast<char*>(&item), sizeof(Edge));
//        }
//        outputFile.close();
//        std::cout << "内容已保存到文件" << filePath << std::endl;
//    } else {
//        std::cerr << "无法打开文件" << std::endl;
//    }
//}
//
//void saveGuidedTuple(std::shared_ptr<guidedTupleSet> gts){
//    std::string filePath="header/index_graph.bin";
//    std::ofstream outputFile(filePath, std::ios::binary);
//    if (outputFile.is_open()) {
//        for (auto item : *gts) {
//            outputFile.write(reinterpret_cast<char*>(&item), sizeof(int));
//        }
//        outputFile.close();
//        std::cout << "内容已保存到文件" << filePath << std::endl;
//    } else {
//        std::cerr << "无法打开文件" << std::endl;
//    }
//}