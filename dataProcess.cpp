//
// Created by 秋日的歌 on 2023/5/15.
//
#include <iostream>
#include <fstream>
#include "header/dataProcess.h"
void load_data(std::string filename, float *&data, int &num, int &dim){
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "open file error" << std::endl;
        exit(-1);
    }
    in.read((char *) &dim, 4);
    in.seekg(0, std::ios::end);
    std::ios::pos_type ss = in.tellg();
    auto f_size = (size_t) ss;
    num = (int) (f_size / (dim + 1) / 4);
    data = new float[num * dim];

    in.seekg(0, std::ios::beg);
    for (size_t i = 0; i < num; i++) {
        in.seekg(4, std::ios::cur);
        in.read((char *) (data + i * dim), dim * sizeof(float));
    }
    in.close();

}


void load_data(std::string &filename, float **&data, int &num, int &dim){

    std::ifstream inputFile(filename, std::ios::binary);

    if (!inputFile) {
        std::cerr << "无法打开文件：" << filename << std::endl;
        exit(0);
    }

    inputFile.read(reinterpret_cast<char*>(&dim), sizeof(int));
    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    auto f_size = (size_t) fileSize;

    num = (int) (f_size / (dim + 1) / 4);
//    dim++;
    data = new float*[num];

    auto *data_1d = new float [num * dim];
    for (int i = 0; i < num; ++i) {
        data[i] = &(data_1d[i * dim]);
    }

    inputFile.seekg(0, std::ios::beg);
//    inputFile.seekg(4, std::ios::cur);
    for (int i = 0; i < num; i++) {
        inputFile.seekg(4, std::ios::cur);
        inputFile.read(reinterpret_cast<char*>(&data_1d[i*dim]), static_cast<std::streamsize>(dim*sizeof(float)));
    }
    inputFile.close();
}

float distance(float **&data, int p1, int p2, int dim){
    float result=0,tmp;

    for(int i=0;i<dim;i++){
        tmp=data[p1][i]-data[p2][i];
        result += tmp*tmp;
    }
    return result;

}

float distance(float ** &data, int p, float_array &q, int dim){
    float result=0,tmp;

    for(int i=0;i<dim;i++){
        tmp=data[p][i]-q[i];
        result += tmp*tmp;
    }
    return result;
}


void get_range(std::shared_ptr<int_array> &index,int num){
    index->reserve(num);
    for(int i=0;i<num;i++){
        index->push_back(i);
    }
}

void get_random_range(std::shared_ptr<int_array> &index,int num,int start,int end){
    int length = end-start+1;
    int_array pool;
    pool.reserve(length);
    for(int i=start;i<end;i++){
        pool.push_back(i);
    }

    std::random_device rd;
    std::mt19937 rng(rd());
//    std::uniform_int_distribution<int> dist(start, end);
    std::shuffle(pool.begin(),pool.end(),rng);

    index->reserve(num);
    for (int i = 0; i < num; ++i) {
        index->push_back(pool[i]);
    }
    std::sort(index->begin(),index->end());
}

void show_vector(float **&data,int p,int dim){
    std::cout<<"{";
    for(int i=0;i<dim-1;i++){
        std::cout<<data[p][i]<<",";
    }
    std::cout<<data[p][dim-1]<<"}"<<std::endl;
}

void show_index(std::shared_ptr<int_array> index){
    auto size = index->size();
//    std::cout << "length:" << size << std::endl;
    if(size == 0){
        std::cout << "{ }" << std::endl;
        return;
    }
    std::cout<<"{ ";
    for(int i=0;i<size-1;i++){
        std::cout<<(*index)[i]<<",";
    }
    std::cout<<(*index)[size-1]<<" }"<<std::endl;
}


void print_v(float **&data,int p,int dim){
    std::cout<<"{";
    for(int i=0;i<dim-1;i++){
        std::cout<<data[p][i]<<",";
    }
    std::cout<<data[p][dim-1]<<"}"<<std::endl;
}



void print(int value)
{
std::cout << value << std::endl;
}
void print(float value)
{
    std::cout << value << std::endl;
}
void print(std::string value)
{
    std::cout << value << std::endl;
}

void get_two_rand(int &p1,int &p2,std::shared_ptr<int_array> &index){
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(index->size()-1));

    // 第一个随机索引
    int index1 = dist(rng);
    // 第二个随机索引，确保与第一个索引不同
    int index2;
    do {
        index2 = dist(rng);
    } while (index2 == index1);
    p1=index->at(index1);
    p2=index->at(index2);
}

std::ostream& operator<<(std::ostream& os, const neighbors & mySet){
    for(int i=0;i<mySet.size();i++){

        if(mySet.at(i)->empty()){
            os << i << ":{}"<<std::endl;
            continue;
        }

        os << i << ":{ ";
        for(auto j:*(mySet.at(i))){
            os << j << " ";
        }
        os << "}" <<std::endl;
    }
    return os;
}

void t_s(){
    time_s = std::chrono::steady_clock::now();
}

void t_e(const std::string& s){
    time_e = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time_e - time_s).count();
    auto minutes = (duration / 1000000 / 60);
    auto seconds = (duration / 1000000) % 60;
    std::cout << s << "runtime " << minutes << "m" << seconds << "s" << std::endl;
}

std::string stringToBits(const std::string& input_string) {
    std::string binary_string;
    for (char c : input_string) {
        std::bitset<8> bits(c); // 将字符转换为8位二进制位
        binary_string += bits.to_string();
    }
    return binary_string;
}