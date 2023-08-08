//
// Created by 秋日的歌 on 2023/8/7.
//

#include "header/VOSerialization.h"
void saveVO(std::shared_ptr<VO> &vo,std::string path){
    {
        std::ofstream file(path, std::ios::binary);
        if (file.is_open()){
            cereal::BinaryOutputArchive archive(file);
            archive(vo);
        }else{
            std::cout << "Failed to open output file!" << std::endl;
        }
    }
}

void loadVO(std::shared_ptr<VO> &vo,std::string path){
    {
        std::ifstream file(path, std::ios::binary);
        if (file.is_open()){
            cereal::BinaryInputArchive archive(file);
            archive(vo);
        }else{
            std::cout << "Failed to open output file!" << std::endl;
        }
    }
}