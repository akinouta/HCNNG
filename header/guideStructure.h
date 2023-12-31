//
// Created by 秋日的歌 on 2023/5/18.
//

#ifndef HCNNG_GUIDESTRUCTURE_H
#define HCNNG_GUIDESTRUCTURE_H

#include "dataProcess.h"
#include "MST.h"
#include "spt.h"

void get_all_neighbors(std::shared_ptr<neighbors> &neighbors,
                       std::shared_ptr<set_edge> &graph,
                       int num);

std::shared_ptr<SPT> get_spt(float **&data,
                             int p,
                             std::shared_ptr<int_array> &neighbor,
                             int dim_now);

void get_gt(std::shared_ptr<guidedTuple> gt,
            float **&data,
            int p,
            std::shared_ptr<int_array> &neighbor,
            std::string id,
            int dim_now);

void get_all_spt(std::shared_ptr<SPTs> &spts,
                 float **&data,
                 std::shared_ptr<set_edge> &graph,
                 int num);

void get_gts(std::shared_ptr<guidedTupleSet> &gts,
                 float **&data,
                 std::shared_ptr<set_edge> &graph,
                 int num);
// spts is a pointer.
// spt ,the contents of spts, is also a pointer.

void search_neighbor(std::shared_ptr<int_array> &neighbor,
                     std::shared_ptr<SPT> &spt,
                     float **&data,
                     int now,
                     int query,
                     int dim_now);

void search_neighbor(std::shared_ptr<int_array> &neighbor,
                     std::shared_ptr<SPT> &spt,
                     float **&data,
                     int now,
                     float_array query,
                     int dim_now);

void search_neighbor(std::shared_ptr<int_array> &neighbor,
                     std::shared_ptr<guidedTuple> &gt,
                     float **&data,
                     int now,
                     int query,
                     int dim);

void search_neighbor(std::shared_ptr<int_array> &neighbor,
                     std::shared_ptr<guidedTuple> &gt,
                     float **&data,
                     int now,
                     float_array query,
                     int dim);
#endif //HCNNG_GUIDESTRUCTURE_H
