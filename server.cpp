//
// Created by 秋日的歌 on 2023/8/3.
//

#include "header/server.h"

void loadEdge(std::shared_ptr<set_edge> &graph){
    std::ifstream file("../disk/graph.bin", std::ios::binary);
    if (file.is_open()){
        cereal::BinaryInputArchive archive(file);
        archive(*graph);
    }else{
        std::cout << "Failed to open output file!" << std::endl;
    }
}
