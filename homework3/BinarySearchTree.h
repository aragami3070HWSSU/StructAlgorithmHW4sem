#pragma once

// Binary Tree
struct Tree {
    int Value;
    Tree *Left;
    Tree *Right;
    Tree *Parent;
};

// Create new node
Tree *Node(int value);

// Insert node with value
void Insert(Tree *&tr, int value);

// Find node by value
Tree *Find(Tree *tr, int value);

// Find min node
Tree* Min(Tree *tr);

// Find next node
Tree* Next(Tree *tr, int x);

// Delete node
void Delete(Tree *&tr, Tree *node);

// Symmetric
void InOrder(Tree *tr);

// Straight
void PreOrder(Tree *tr);

// Reverse
void PostOrder(Tree *tr);
