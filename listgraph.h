// Copyright 2018 Vlad-Gabriel Dobrete (dobrete.vlad@yahoo.com)

#ifndef LISTGRAPH_H_
#define LISTGRAPH_H_
#include <iostream>
#include <vector>
#include <queue>
#include <list>

struct Node {
    std::vector<int> neighbors;
};

class ListGraph {
 private:
    std::vector<Node> nodes;
    int size;

 public:
    // Constructor
    explicit ListGraph(int size) {
        this->size = size;
        nodes.resize(size);
    }

    // Functie prin care adaug drum intre 2 intersectii
    void addEdge(int src, int dst) {
        nodes[src].neighbors.push_back(dst);
    }
    // Functie prin care sterg drumul dintre 2 intersectii
    // Pentru a cauta in urmatoarele functii, voi folosi un interator
    // Ce pinteaza catre o anumita valoare care trebuie
    // Sa indeplineasca criterii
    void removeEdge(int src, int dst) {
        for (std::vector<int>::iterator it = nodes[src].neighbors.begin();
            it != nodes[src].neighbors.end(); it++)
            if (*it == dst) {
                nodes[src].neighbors.erase(it);
                break;
            }
    }
    // Functie prin care vad daca exista drum intre 2 intersectii
    bool hasEdge(int src, int dst) {
        for (std::vector<int>::iterator it = nodes[src].neighbors.begin();
            it != nodes[src].neighbors.end(); it++)
            if (*it == dst) {
                return true;
            }
        return false;
    }
    // Functie de cautare in latime sau de aflare a distantei
    // Intre 2 puncte
    // Notez fiecare nod vizitat si aflu distanta ceruta
    // Fiecare muchie are valoarea 1
    int BFS(int src, int dst) {
        bool* visited = new bool[size];
        int* distance = new int[size];
        for (int i = 0; i < size; i++) {
            visited[i] = false;
            distance[i] = -1;
        }
        std::queue<int> queue;
        visited[src] = true;
        distance[src] = 0;
        queue.push(src);
        while (!queue.empty()) {
            src = queue.front();
            queue.pop();
            for (auto i = nodes[src].neighbors.begin();
                i != nodes[src].neighbors.end(); i++) {
                if (visited[*i] == false) {
                    visited[*i] = true;
                    queue.push(*i);
                    distance[*i] = distance[src] + 1;
                }
            }
        }
        // eliberez vectorii
        delete[] visited;
        int a = distance[dst];
        delete[] distance;
        return a;
    }
};

#endif  // LISTGRAPH_H_
