#pragma once
#include <iomanip>
#include <iostream>

enum NodeColor { Black, Red };

struct RBTree {
    NodeColor Color;
    int Value;
    RBTree *Right;
    RBTree *Left;
    RBTree *Parent;
};

// Создание корня (черный)
RBTree *Root(int x);

// Создание узла (красный)
RBTree *Node(RBTree *p, int x);

// Левый поворот
void LeftTurn(RBTree *&tr, RBTree *node);

// Правый поворот
void RightTurn(RBTree *&tr, RBTree *node);

// Найти деда
RBTree *GrandParent(RBTree *node);

// Найти дядю
RBTree *Uncle(RBTree *node);
// Найти брата
RBTree *Sibling(RBTree *node);

void InsertCase1(RBTree *&tr, RBTree *node);
void InsertCase2(RBTree *&tr, RBTree *node);
void InsertCase3(RBTree *&tr, RBTree *node);
void InsertCase4(RBTree *&tr, RBTree *node);
void InsertCase5(RBTree *&tr, RBTree *node);

void Insert(RBTree *&tr, RBTree *prev, int node);

void DeleteCase1(RBTree *&tr, RBTree *node);
void DeleteCase2(RBTree *&tr, RBTree *node);
void DeleteCase3(RBTree *&tr, RBTree *node);
void DeleteCase4(RBTree *&tr, RBTree *node);
void DeleteCase5(RBTree *&tr, RBTree *node);
void DeleteCase6(RBTree *&tr, RBTree *node);

void Replace(RBTree *&tr, RBTree *node, RBTree *child);

void DeleteOne(RBTree *&tr, RBTree *node);

// Поиск
RBTree *Find(RBTree *tr, int value);

void MaxHeight(RBTree *x, short &max, short deepness = 1);

void PrintHelper(RBTree ***arr, RBTree *x, const short deepness = 0,
                 const short ind = 0);

void Print(RBTree *x);
