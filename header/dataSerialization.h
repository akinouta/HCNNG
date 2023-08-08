//
// Created by 秋日的歌 on 2023/8/5.
//

#ifndef HCNNG_SERIALIZATION_H
#define HCNNG_SERIALIZATION_H
#include "header.h"
#include "MST.h"

void saveData(std::shared_ptr<int_array> &a,std::string path);
void saveEdge(std::shared_ptr<set_edge> &graph,std::string path);
void saveGuidedTuple(std::shared_ptr<guidedTupleSet> &gts,std::string path);

void loadData(std::shared_ptr<int_array> &a,std::string path);
void loadEdge(std::shared_ptr<set_edge> &graph,std::string path);
void loadGuidedTuple(std::shared_ptr<guidedTupleSet> &gts,std::string path);







#endif //HCNNG_SERIALIZATION_H
