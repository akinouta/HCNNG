//
// Created by 秋日的歌 on 2023/8/7.
//
//
// Created by 秋日的歌 on 2023/8/5.
//

#include "header/dataSerialization.h"
void saveData(std::shared_ptr<int_array> &a,std::string path){
    std::ofstream file(path, std::ios::binary);
    if (file.is_open()){
        cereal::BinaryOutputArchive archive(file);
        archive(a);
    }else{
        std::cout << "Failed to open output file!" << std::endl;
    }
}

void saveEdge(std::shared_ptr<set_edge> &graph,std::string path){
    std::ofstream file(path, std::ios::binary);
    if (file.is_open()){
        cereal::BinaryOutputArchive archive(file);
        archive(graph);
    }else{
        std::cout << "Failed to open output file!" << std::endl;
    }
}

void saveGuidedTuple(std::shared_ptr<guidedTupleSet> &gts,std::string path){
    std::ofstream file(path, std::ios::binary);
    if (file.is_open()){
        cereal::BinaryOutputArchive archive(file);
        archive(gts);
    }else{
        std::cout << "Failed to open output file!" << std::endl;
    }
}




void loadData(std::shared_ptr<int_array> &a,std::string path){
    std::ifstream file(path, std::ios::binary);
    if (file.is_open()){
        cereal::BinaryInputArchive archive(file);
        archive(a);
    }else{
        std::cout << "Failed to open output file!" << std::endl;
    }
}


void loadEdge(std::shared_ptr<set_edge> &graph,std::string path){
    std::ifstream file(path, std::ios::binary);
    if (file.is_open()){
        cereal::BinaryInputArchive archive(file);
        archive(graph);
    }else{
        std::cout << "Failed to open output file!" << std::endl;
    }
}

void loadGuidedTuple(std::shared_ptr<guidedTupleSet> &gts,std::string path){
    std::ifstream file(path, std::ios::binary);
    if (file.is_open()){
        cereal::BinaryInputArchive archive(file);
        archive(gts);
    }else{
        std::cout << "Failed to open output file!" << std::endl;
    }
}

