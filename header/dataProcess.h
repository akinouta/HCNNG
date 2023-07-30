//
// Created by 秋日的歌 on 2023/5/15.
//

#ifndef HCNNG_DATAPROCESS_H
#define HCNNG_DATAPROCESS_H

#include "header.h"



void load_data(std::string &filename, float ** &data, int &num, int &dim);
float distance(float ** &data, int p1, int p2, int dim);
void get_two_rand(int &p1,int &p2,std::shared_ptr<int_array> &index);
void get_range(std::shared_ptr<int_array> &index,int num);
void get_random_range(std::shared_ptr<int_array> &index,int num,int start,int end);

void show_vector(float **&data,int p,int dim);
void show_index(std::shared_ptr<int_array> index);
void print_v(float **&data,int p,int dim);
void print(int value);
void print(std::string value);
void print(float value);

void t_s();
void t_e(const std::string& s="");

std::ostream& operator<<(std::ostream& os, const neighbors & mySet);


#endif //HCNNG_DATAPROCESS_H