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
#include <bitset>
#include <map>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/variant.hpp>
#include <fstream>
#include <utility>
#include <cstdio>
#include <iomanip>
#include <variant>
#include <any>

const std::string datasetPath = "../disk/data.bin";
const std::string graphPath = "../disk/graph.bin";
const std::string guideTuplePath = "../disk/gt.bin";
const std::string VOPath = "../disk/VO.bin";


typedef std::vector<int> int_array;
typedef std::vector<float> float_array;
typedef std::set<int> int_set;
typedef std::vector<std::shared_ptr<int_array>> neighbors;
typedef std::chrono::time_point<std::chrono::steady_clock> t;
typedef std::vector<std::shared_ptr<float_array>> DATA;

typedef std::map<std::string,std::shared_ptr<int_array>> guidedTuple;
typedef std::map<int,std::shared_ptr<guidedTuple>> guidedTupleSet;






extern t time_s;
extern t time_e;

const float INF = std::numeric_limits<float>::infinity();
#define MAX_DEGREE 3

#endif //HCNNG_HEADER_H