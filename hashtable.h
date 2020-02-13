// Copyright 2018 Vlad-Gabriel Dobrete (dobrete.vlad@yahoo.com)

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <iostream>
#define TRESHOLD 0.75
// Structura pentru fiecare element
// in care stochez o valoare(string) si o cheie(int)
template <typename Tkey, typename Tvalue>
struct elem_info {
    Tkey key;
    Tvalue value;
};
// Clasa generica hashtable
template <typename Tkey, typename Tvalue>
class Hashtable {
 private:
    std::list<struct elem_info<Tkey, Tvalue> >* H;
    // pointer catre bucket-uri
    int capacity;
    unsigned int size;
    // numarul de elemente

 public:
    // Constructor
    explicit Hashtable(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        H = new std::list<struct elem_info<Tkey, Tvalue> >[capacity];
    }
    // Destructor
    ~Hashtable()
    {
        for (int i = 0; i < capacity; ++i) {
            H[i].clear();
        }
        // Eliberez H
        delete[] H;
    }
    // Functie prin care retin intersectiile si le atribui o valoare unica
    void put(Tkey key, Tvalue value)
    {
        int index = hash(key);
        int ok = 0;
        typename std::list<elem_info<Tkey, Tvalue> >::iterator it;
        for (it = H[index].begin(); it != H[index].end(); it++) {
            if (it->key == key) {
                it->value = value;
                ok = 1;
                break;
            }
        }
        if (ok == 0) {
            elem_info<Tkey, Tvalue>* nod = new elem_info<Tkey, Tvalue>;
            nod->key = key;
            nod->value = value;
            H[index].push_back(*nod);
            delete nod;
            ++size;
        }
    }

    // functie pentru a scoate nodul corespunzator unei intersectii
    Tvalue get(Tkey key)
    {
        typename std::list<elem_info<Tkey, Tvalue> >::iterator it;
        int index = hash(key);
        for (it = H[index].begin(); it != H[index].end(); it++) {
            if (it->key == key)
                return it->value;
        }
    }
    // functie de hash a unei intersectii
    // Aceasta atribuie o valoare unica fiecarei intersectii
    Tvalue hash(std::string key)
    {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum = sum + (int)(key[i]);
        return sum % capacity;
    }
};

#endif  // HASHTABLE_H_
