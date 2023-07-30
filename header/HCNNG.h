//
// Created by 秋日的歌 on 2023/5/16.
//

#ifndef HCNNG_HCNNG_H
#define HCNNG_HCNNG_H


#include "header.h"
#include "MST.h"


void MST3(std::shared_ptr<set_edge> &mst,float ** &data,
          std::shared_ptr<int_array> &index,
          int dim);

std::shared_ptr<set_edge> HierarchicalClustering(float ** &data,
                                                 std::shared_ptr<int_array> &index,
                                                 int min_size_cluster, int dim);

std::shared_ptr<set_edge> CreateHCNNG(float ** &data,
                                      std::shared_ptr<int_array> &index,
                                      int dim,int min_size_cluster,
                                      int num_cluster);

#endif //HCNNG_HCNNG_H