//
// Created by 秋日的歌 on 2023/5/15.
//

#ifndef HCNNG_EDGE_H
#define HCNNG_EDGE_H



#include "header.h"
#include "spt.h"


class Edge{
public:
    int start;
    int end;
    float weight;
    Edge();
    Edge(int start, int end, float weight);
    bool operator<(const Edge& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Edge& e);

};

class EdgeCompare{
public:
    bool operator()(Edge e1, Edge e2) const;
};

class EdgeHash{
public:
    std::size_t operator()(const Edge& e) const;
};

class EdgeKeyEqual{
public:
    bool operator()(const Edge& e1, const Edge& e2) const;
};

typedef std::set<Edge,EdgeCompare> set_edge;
typedef std::vector<std::vector<float>> MGraph;
typedef std::unordered_map<int,int> uo_map;

class DisjointSet {
public:
    uo_map parents;
    uo_map degree;
//    uo_map rank;
    explicit DisjointSet(int_array index);
    int find(int p);
    void merge(int p1, int p2);
};

class Closedge{
public:
    int adjvex;
    float lowcost;
};




//typedef std::unordered_set<Edge,EdgeHash,EdgeKeyEqual> set_edge_uo;
std::ostream& operator<<(std::ostream& os, const Edge& e);
std::ostream& operator<<(std::ostream& os, const set_edge& mySet);
std::ostream& operator<<(std::ostream& os, const MGraph& mySet);
std::ostream& operator<<(std::ostream& os, const guidedTuple & gt);
std::ostream& operator<<(std::ostream& os, const guidedTupleSet & gts);

void fullGraph(std::shared_ptr<set_edge> &full,
               float **&data, std::shared_ptr<int_array> &index,
               int dim);

void fullGraph(std::shared_ptr<MGraph> &full,
               float **&data, std::shared_ptr<int_array> &index,
               int dim);

void kruskal(std::shared_ptr<set_edge> &mst,
             std::shared_ptr<set_edge> &graph,
             std::shared_ptr<int_array> &index);

void prim(std::shared_ptr<set_edge> &mst,
          std::shared_ptr<MGraph> &graph,
          std::shared_ptr<int_array> &index);

int minimum(std::vector<Closedge> &closedge);

#endif //HCNNG_EDGE_H