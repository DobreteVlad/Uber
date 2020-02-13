// Copyright 2019 SD_Homework_Team
// Copyright 2018 Vlad-Gabriel Dobrete (dobrete.vlad@yahoo.com)
#include <fstream>
#include <climits>
#include <string>
#ifndef SOLVER_H_
#define SOLVER_H_
#include "./listgraph.h"
#include "./hashtable.h"

Hashtable<std::string, int> h(1000);
ListGraph a(1000);

class solver {
 public:
    void task1_solver(std::ifstream& fin, std::ofstream& fout) {
        int N, M, i, p;
        fin >> N >> M;
        std::string x, y;
        // Citesc fiecare intersectie si o bag in hashtable
        for (i = 0; i < N; i++) {
            fin >> x;
            h.put(x, i);
        }
        // Citesc perechile de intersectii si fac drum intre ele
        for (i = 0; i < M; i++) {
            fin >> x >> y;
            a.addEdge(h.get(x), h.get(y));
        }
        fin >> N;
        // Afisez cu functia Bfs daca exista drum intre 2 puncte
        // Initializarea din BFS este -1 daca nu exista drum
        for (i = 0; i < N; i++) {
            fin >> x >> y;
            p = a.BFS(h.get(x), h.get(y));
            if (p == -1) {
                fout << "n";
            } else {
                fout << "y";
            }
            fout << '\n';
        }
    }

    void task2_solver(std::ifstream& fin, std::ofstream& fout) {
        int n;
        std::string X, Y;
        fin >> n;
        for (int i = 0; i < n; i++) {
            fin >> X >> Y;
            // Aflu distanta dintre 2 drumuri cu functia Bfs
            fout << a.BFS(h.get(X), h.get(Y)) << '\n';
        }
    }

    void task3_solver(std::ifstream& fin, std::ofstream& fout) {
        char r;
        std::string x, y;
        int k, n;
        fin >> n;
        for (int i = 0; i < n; i++) {
            fin >> r;
            // Caut dupa fiecare criteriu din enunt
            if (r == 'c') {
                fin >> x >> y;
                fin >> k;
                // In functie de valoarea lui k:
                if (k == 0) {
                	// Adaug drum
                    a.addEdge(h.get(x), h.get(y));
                }
                if (k == 1) {
                	// Blochez drumurile intre 2 intersectii directe
                    if (a.hasEdge(h.get(x), h.get(y)) == true) {
                        a.removeEdge(h.get(x), h.get(y));
                    }
                    if (a.hasEdge(h.get(y), h.get(x)) == true) {
                        a.removeEdge(h.get(y), h.get(x));
                    }
                }
                // Drumul dintre 2 intersectii devine bidirectional
                // Daca nu exista drum direct, le adaug pe ambele
                if (k == 2) {
                    if (a.hasEdge(h.get(x), h.get(y)) == true &&
                    	a.hasEdge(h.get(y), h.get(x)) == false) {
                        a.addEdge(h.get(y), h.get(x));
                    } else if (a.hasEdge(h.get(y), h.get(x)) == true &&
                    	a.hasEdge(h.get(x), h.get(y)) == false) {
                        a.addEdge(h.get(x), h.get(y));
                    } else if (a.hasEdge(h.get(y), h.get(x)) == false &&
                    	a.hasEdge(h.get(x), h.get(y)) == false) {
                        a.addEdge(h.get(y), h.get(x));
                        a.addEdge(h.get(x), h.get(y));
                    }
                }
                // Inversez drumurile dintre 2 intersectii
                if (k == 3) {
                    if (a.hasEdge(h.get(x), h.get(y)) == true &&
                    	a.hasEdge(h.get(y), h.get(x)) == false) {
                        a.removeEdge(h.get(x), h.get(y));
                        a.addEdge(h.get(y), h.get(x));
                    } else if (a.hasEdge(h.get(x), h.get(y)) == false &&
                    	a.hasEdge(h.get(y), h.get(x)) == true) {
                        a.removeEdge(h.get(y), h.get(x));
                        a.addEdge(h.get(x), h.get(y));
                    }
                }
            }
            // Query pentru a afla daca exista drum intre 2 intersectii
            if (r == 'q') {
                fin >> x >> y;
                fin >> k;
                if (k == 0) {
                    int p = a.BFS(h.get(x), h.get(y));
                    if (p == -1) {
                        fout << "n";
                    } else {
                        fout << "y";
                    }
                    fout << '\n';
                }
                // Query pentru a afla distanta
                if (k == 1) {
                    fout << a.BFS(h.get(x), h.get(y)) << '\n';
                }
                // Query pentru a afla lungimea drumului dintr 2 intersectii
                // trecand printr-o alta intersectie
                // Afisez -1, daca un drum din cele 2 nu exista.
                if (k == 2) {
                    std::string z;
                    fin >> z;
                    if (a.BFS(h.get(x), h.get(z)) == -1 ||
                    	a.BFS(h.get(z), h.get(y)) == -1) {
                        fout << -1 << '\n';
                    } else {
                        fout << a.BFS(h.get(x), h.get(z)) +
                        a.BFS(h.get(z), h.get(y)) << '\n';
                    }
                }
            }
        }
    }
    void task4_solver(std::ifstream& fin, std::ofstream& fout) {}

    void task5_solver(std::ifstream& fin, std::ofstream& fout) {}
};
#endif  // SOLVER_H_
