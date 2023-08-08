//
// Created by 秋日的歌 on 2023/5/15.
//

#include "header/MST.h"


Edge::Edge():start(0),end(0),weight(0.0) {}
Edge::Edge(int start, int end, float weight):start(start),end(end),weight(weight){}

bool Edge::operator<(const Edge& other) const{
    if(weight < other.weight){
        return true;
    } else{
        return false;
    }
}

bool EdgeCompare::operator()(Edge e1, Edge e2) const{

    if (e1.start != e2.start) return e1.start < e2.start;
    if (e1.end != e2.end) return e1.end < e2.end;
    return e1.weight < e2.weight;
//    if(e1.start < e2.start){
//        return true;
//    } else if(e1.start > e2.start){
//        return false;
//    }
//
//    if(e1.end < e2.end){
//        return true;
//    } else if(e1.end > e2.end){
//        return false;
//    }
//
//    return e1.weight<e2.weight;
}

std::ostream& operator<<(std::ostream& os, const Edge& e){
    os << "<" << e.start <<","<< e.end << "," <<e.weight << ">";
    return os;
}
std::ostream& operator<<(std::ostream& os, const set_edge& mySet){
    if(mySet.empty()){
        os << std::endl << "______empty______" << std::endl;
        return os;
    }

    os << "______start______" << std::endl;
    for (auto it : mySet) {
        os << it << std::endl;
    }
    os << "_______end_______" << std::endl;
    return os;
}



std::ostream& operator<<(std::ostream& os, const MGraph& mySet){
    for(auto &i: mySet){
        for(auto j: i){
            os<< j << '\t';
        }
        os<<std::endl;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const guidedTuple & gt){
    for(const auto& leaf:gt){
       auto code = leaf.first;
       auto nb=leaf.second;
       os << code << ": { ";
       for(auto p:*nb){
           os<<p<<" ";
       }
       os << "}" <<std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const guidedTupleSet & gts){
    for(const auto& i:gts){
        os<< "point" << i.first << ":" << std::endl << *i.second <<std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const int_set &set){
    os<<"{ ";
    for(auto i:set){
        os<<i<<" ";
    }
    os<<"}"<<std::endl;
    return os;
}

std::size_t EdgeHash::operator()(const Edge& e) const{
    std::size_t startHash = std::hash<int>{}(e.start);
    std::size_t endHash = std::hash<int>{}(e.end);
    if (e.start<e.end){
        return startHash ^ endHash;
    }
    return endHash ^ startHash;
}

bool EdgeKeyEqual::operator()(const Edge& e1, const Edge& e2) const {
    // 自定义相等性比较函数的实现
    return
            (e1.start == e2.start && e1.end == e2.end)
            ||
            (e1.start == e2.end && e1.end == e2.start)
            ;
}



DisjointSet::DisjointSet(int_array index){

    for (int i : index) {
        parents[i] = i;
        degree[i] = 0;
//        rank[i] = 0;
    }
}

int DisjointSet::find(int p) {

    while (p != parents[p]) {
        p = parents[p];
    }
    return p;
}

void DisjointSet::merge(int p1, int p2) {
    int root1 = find(p1);
    int root2 = find(p2);
    parents[root1] = root2;
}

//void DisjointSet::merge(int p1, int p2) {
//    int root1 = find(p1);
//    int root2 = find(p2);
//    if (root1 != root2) {
//        if (rank[root1] < rank[root2]) {
//            rank[root1] = root2;
//        } else if (rank[root1] > rank[root2]) {
//            rank[root2] = root1;
//        } else {
//            rank[root1] = root2;
//            rank[root2]++;
//        }
//    }
//}

void fullGraph(std::shared_ptr<set_edge> &e,
               float **&data, std::shared_ptr<int_array> &index,
               int dim){

    int size_index = static_cast<int>(index->size());
    int i,j;
    int p1,p2;

    for(i=0;i<size_index;i++){
        for(j=0;j<i;j++){
            p1=index->at(i);
            p2=index->at(j);
            Edge edge(p1,p2,distance(data,p1,p2,dim));
            e->insert(
                    edge
                    );
        }
    }

}

void fullGraph(std::shared_ptr<MGraph> &e,
               float **&data, std::shared_ptr<int_array> &index,
               int dim){
    auto size_index = static_cast<int>(index->size());
    int i,j;
    int p1,p2;
    float d;

    e->resize(size_index);

    for(i=0;i<size_index;i++){
        e->at(i).resize(size_index);
        e->at(i).at(i)= INF;
        for(j=0;j<i;j++){
            p1=index->at(i);
            p2=index->at(j);
            d=distance(data,p1,p2,dim);
            e->at(i).at(j)= d;
            e->at(j).at(i)= d;
        }
    }
}




void kruskal(std::shared_ptr<set_edge> &mst,
             std::shared_ptr<set_edge> &graph,
             std::shared_ptr<int_array> &index){
    auto size_index = static_cast<int>(index->size());
    std::shared_ptr<DisjointSet> disjointSet(new DisjointSet(*index));
    int edgeCount = 0;
    int start,end;
    int parents_s,parents_e;
    auto it = graph->begin();
    auto it_end = graph->end();
    int loop = 1;

    for (; edgeCount < size_index - 1 && it != it_end; ++it,++loop){
        start=(*it).start;
        end = (*it).end;

        parents_s = disjointSet->find(start);
        parents_e = disjointSet->find(end);


        if(parents_s != parents_e
           && disjointSet->degree[start]<MAX_DEGREE && disjointSet->degree[end]<MAX_DEGREE
           ){
            mst->insert(*it);

            disjointSet->degree[start]+=1;
            disjointSet->degree[end]+=1;

            disjointSet->merge(parents_s,parents_e);
            edgeCount++;
        }
    }
}

void prim(std::shared_ptr<set_edge> &mst,
          std::shared_ptr<MGraph> &graph,
          std::shared_ptr<int_array> &index){
    auto size_index = static_cast<int>(index->size());
    std::vector<Closedge> closedge;
    closedge.resize(size_index);
    int i,j,k=0,pre;
    float tmp;
    for(j=0;j<size_index;j++){
        if(j!=k){
            closedge[j]={k,graph->at(k).at(j)};
        }
    }
    closedge[k].lowcost=0;
    for(i=1;i<size_index;i++){
        pre = k;
        k = minimum(closedge);
        mst->insert(Edge(index->at(pre),index->at(k),graph->at(pre).at(k)));
        closedge[k].lowcost=0;
        for(j=0;j<size_index;j++){
            tmp=graph->at(k).at(j);
            if(tmp<closedge[j].lowcost){
                closedge[j]={k,tmp};
            }
        }
    }

}

int minimum(std::vector<Closedge> &closedge){
    auto size = static_cast<int>(closedge.size());
    int min=-1;
    float mincost=INF;
    for(int i=0;i<size;i++){
        if(closedge[i].lowcost<mincost && closedge[i].lowcost>0){
            min = i;
            mincost = closedge[i].lowcost;
        }
    }
    return min;
}
