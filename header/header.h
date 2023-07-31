//
// Created by 秋日的歌 on 2023/5/16.
//

#ifndef HCNNG_HEADER_H
#define HCNNG_HEADER_H


#include <random>
#include <iostream>
#include <string>
#include <filesystem>
#include <set>
#include <unordered_set>
#include <vector>
#include <stack>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <queue>
#include <limits>
#include <map>



typedef std::vector<int> int_array;
typedef std::vector<float> float_array;
typedef std::vector<std::shared_ptr<int_array>> neighbors;
typedef std::chrono::time_point<std::chrono::steady_clock> t;


extern t time_s;
extern t time_e;

const float INF = std::numeric_limits<float>::infinity();


#define MAX_DEGREE 3

#endif //HCNNG_HEADER_H