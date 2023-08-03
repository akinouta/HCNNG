//
// Created by 秋日的歌 on 2023/8/2.
//

#include "header/dataOwner.h"


void saveEdge(std::shared_ptr<set_edge> &graph){
    std::ofstream file("../disk/graph.bin", std::ios::binary);
    if (file.is_open()){
        cereal::BinaryOutputArchive archive(file);
        archive(*graph);
    }else{
        std::cout << "Failed to open output file!" << std::endl;
    }
}
