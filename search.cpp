//
// Created by 秋日的歌 on 2023/5/25.
//
#include "header/search.h"

bool Compare::operator()(std::pair<int,float> a, std::pair<int,float> b) const {
    // 自定义的比较规则
    return a.second > b.second; // 降序排列
}
bool Compare2::operator()(std::pair<int,float> a, std::pair<int,float> b) const {
    // 自定义的比较规则
    return a.second < b.second; // 降序排列
}

std::ostream& operator<<(std::ostream& os, const max_queue &queue){
    auto queue2(queue);
    os << "{" << std::endl;
    while (!queue2.empty()){
        auto q=queue2.top();
        queue2.pop();
        os << "\t" << q.first << ":" << q.second <<std::endl;
    }
    os << "}" << std::endl;
    return os;
}

void search(std::shared_ptr<max_queue> &nn,
            int k,
            float **&data,
            const std::shared_ptr<SPTs>& spts,
            int start,
            int query,
            int dim){
    min_queue candidate;
    std::set<int> visited;
    auto start_dist=distance(data,start,query,dim);
    candidate.emplace(start,start_dist);
    visited.insert(start);
    while(!candidate.empty()){
        auto now= candidate.top();
        auto now_idx = candidate.top().first;
        auto now_dist= candidate.top().second;
        candidate.pop();

        if(nn->size() == k && nn->top().second < now_dist){
            break;
        } else {
            nn->push(now);
        }

        if(nn->size()>k){
            nn->pop();
        }

        std::shared_ptr<int_array> nb(new int_array);
        search_neighbor(nb,spts->at(now_idx),data,now_idx,query,0);
        for(auto p:*nb){
            if(!visited.contains(p)){
                visited.insert(p);
                auto dist= distance(data,p,query,dim);
                candidate.emplace(p,dist);
            }
        }
    }
}

void search(std::shared_ptr<max_queue> &nn,
            int k,
            float **&data,
            std::shared_ptr<SPTs> &spts,
            int start,
            float_array query,
            int dim){
    min_queue candidate;
    std::set<int> visited;
    auto start_dist=distance(data,start,query,dim);
    candidate.emplace(start,start_dist);
    visited.insert(start);
    while(!candidate.empty()){
        auto now= candidate.top();
        auto now_idx = candidate.top().first;
        auto now_dist= candidate.top().second;
        candidate.pop();

        if(nn->size() == k && nn->top().second < now_dist){
            break;
        } else {
            nn->push(now);
        }

        if(nn->size()>k){
            nn->pop();
        }

        std::shared_ptr<int_array> nb(new int_array);
        search_neighbor(nb,spts->at(now_idx),data,now_idx,query,0);
        for(auto p:*nb){
            if(!visited.contains(p)){
                visited.insert(p);
                auto dist= distance(data,p,query,dim);
                candidate.emplace(p,dist);
            }
        }
    }
}

void search(std::shared_ptr<max_queue> &nn,
            int k,
            float **&data,
            std::shared_ptr<guidedTupleSet> &gts,
            int start,
            int query,
            int dim){
    min_queue candidate;
    std::set<int> visited;
    auto start_dist=distance(data,start,query,dim);
    candidate.emplace(start,start_dist);
    visited.insert(start);
    while(!candidate.empty()){
        auto now= candidate.top();
        auto now_idx = candidate.top().first;
        auto now_dist= candidate.top().second;
        candidate.pop();

        if(nn->size() == k && nn->top().second < now_dist){
            break;
        } else {
            nn->push(now);
        }

        if(nn->size()>k){
            nn->pop();
        }

        std::shared_ptr<int_array> nb(new int_array);
        search_neighbor(nb,gts->at(now_idx),data,now_idx,query,0);
        for(auto p:*nb){
            if(!visited.contains(p)){
                visited.insert(p);
                auto dist= distance(data,p,query,dim);
                candidate.emplace(p,dist);
            }
        }
    }
}

void search(std::shared_ptr<max_queue> &nn,
            int k,
            float **&data,
            std::shared_ptr<guidedTupleSet> &gts,
            int start,
            float_array query,
            int dim){
    min_queue candidate;
    std::set<int> visited;
    auto start_dist=distance(data,start,query,dim);
    candidate.emplace(start,start_dist);
    visited.insert(start);
    while(!candidate.empty()){
        auto now= candidate.top();
        auto now_idx = candidate.top().first;
        auto now_dist= candidate.top().second;
        candidate.pop();

        if(nn->size() == k && nn->top().second < now_dist){
            break;
        } else {
            nn->push(now);
        }

        if(nn->size()>k){
            nn->pop();
        }

        std::shared_ptr<int_array> nb(new int_array);
        search_neighbor(nb,gts->at(now_idx),data,now_idx,query,0);
        for(auto p:*nb){
            if(!visited.contains(p)){
                visited.insert(p);
                auto dist= distance(data,p,query,dim);
                candidate.emplace(p,dist);
            }
        }
    }
}