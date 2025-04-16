#include "RBTree.h"
#include <iostream>

// Создание корня (черный)
RBTree *Root(int x) {
    RBTree *n = new RBTree;
    n->Parent = n->Left = n->Right = nullptr;
    n->Color = Black;
    n->Value = x;
    return n;
}

// Создание узла (красный)
RBTree *Node(RBTree *p, int x) {
    RBTree *n = new RBTree;
    n->Parent = p;
    n->Left = n->Right = nullptr;
    n->Color = Red;
    n->Value = x;
    return n;
}

void LeftTurn(RBTree *&tr, RBTree *node) {
    RBTree *rightChild = node->Right;
    node->Right = rightChild->Left;

    if (rightChild->Left != nullptr) {
        rightChild->Left->Parent = node;
    }
    // Родителем для rightChild становится родитель node
    rightChild->Parent = node->Parent;

    if (node->Parent) {
        if (node == node->Parent->Left) {
            node->Parent->Left = rightChild;
        }
        else {
            node->Parent->Right = rightChild;
        }
    }
    // Вот эта дрисня правильная
    rightChild->Left = node;
    node->Parent = rightChild;
    if (!rightChild->Parent) {
        tr = rightChild;
        tr->Color = Black;
    }
}

// Левый поворот
// void LeftTurn(RBTree *&tr, RBTree *node) {
//     RBTree *rightChild = node->Right;
//     rightChild->Parent = node->Parent;
//     if (node->Parent) {
//         if (node->Parent->Left == node) {
//             node->Parent->Left = rightChild;
//         }
//         else {
//             node->Parent->Right = rightChild;
//         }
//     }
//     node->Right = rightChild->Left;
//     if (rightChild->Left) {
//         rightChild->Left->Parent = node;
//     }
//     if (rightChild->Left != nullptr) {
//         rightChild->Left->Parent = node;
//     }
//     node->Parent = rightChild;
//     rightChild->Left = node;
//     if (!rightChild->Parent) {
//         tr = rightChild;
//         tr->Color = Black;
//     }
// }

// Правый поворот
void RightTurn(RBTree *&tr, RBTree *node) {
    RBTree *leftChild = node->Left;
    node->Left = leftChild->Right;

    if (leftChild->Right != nullptr) {

        leftChild->Right->Parent = node;
    }
    // Родителем для leftChild становится родитель node
    leftChild->Parent = node->Parent;

    if (node->Parent) {
        if (node == node->Parent->Left) {
            node->Parent->Left = leftChild;
        }
        else {
            node->Parent->Right = leftChild;
        }
    }
    leftChild->Right = node;
    node->Parent = leftChild;
    if (!leftChild->Parent) {
        tr = leftChild;
        tr->Color = Black;
    }
}

// Код Ангелины
// // Правый поворот
// void RightTurn(RBTree *&tr, RBTree *node) {
//     RBTree *leftChild = node->Left;
//     leftChild->Parent = node->Parent;
//     if (node->Parent) {
//         if (node->Parent->Left == node) {
//             node->Parent->Left = leftChild;
//         }
//         else {
//             node->Parent->Right = leftChild;
//         }
//     }
//     node->Left = leftChild->Right;
//     if (leftChild->Right) {
//         leftChild->Parent = node;
//     }
//     if (leftChild->Right != nullptr) {
//         leftChild->Right->Parent = node;
//     }
//     node->Parent = leftChild;
//     leftChild->Right = node;
//     if (!leftChild->Parent) {
//         tr = leftChild;
//         tr->Color = Black;
//     }
// }

// Найти деда
RBTree *GrandParent(RBTree *node) {
    // Деда не будет у фиктивного листа (node == nullptr) и у корня
    // (node->Parent == nullptr)
    if (node && node->Parent) {
        // Возвращаем родителя родителя текущего узла
        return node->Parent->Parent;
    }
    return nullptr;
}

// Найти дядю
RBTree *Uncle(RBTree *node) {
    // Дед узла node
    RBTree *grandParent = GrandParent(node);
    // Если нет деда
    if (!grandParent) {
        return nullptr;
    }
    // Если родитель node --- левый ребенок grandPar
    if (grandParent->Left == node->Parent) {
        // Возвращаем правого ребенка grandPar
        return grandParent->Right;
    }
    // Возвращаем левого ребенка grandPar
    return grandParent->Left;
}
// Найти брата
RBTree *Sibling(RBTree *node) {
    // Если существует node и его Parent
    if (node && node->Parent) {
        // Если node левый ребенок
        if (node->Parent->Left == node) {
            // Возвращаем правого ребенка
            return node->Parent->Right;
        }
        // Возвращаем левого ребенка
        return node->Parent->Left;
    }
    return nullptr;
}

void InsertCase1(RBTree *&tr, RBTree *node);
void InsertCase2(RBTree *&tr, RBTree *node);
void InsertCase3(RBTree *&tr, RBTree *node);
void InsertCase4(RBTree *&tr, RBTree *node);
void InsertCase5(RBTree *&tr, RBTree *node);

void InsertCase1(RBTree *&tr, RBTree *node) {
    if (!node->Parent) {
        node->Color = Black;
    }
    else {
        InsertCase2(tr, node);
    }
}

void InsertCase2(RBTree *&tr, RBTree *node) {
    if (node->Parent->Color == Black) {
        return;
    }
    InsertCase3(tr, node);
}

void InsertCase3(RBTree *&tr, RBTree *node) {
    RBTree *uncle = Uncle(node);
    RBTree *grandParent = GrandParent(node);
    if (uncle && uncle->Color == Red && node->Parent->Color == Red) {
        uncle->Color = Black;
        node->Parent->Color = Black;
        grandParent->Color = Red;
        InsertCase1(tr, grandParent);
    }
    else {
        InsertCase4(tr, node);
    }
}

void InsertCase4(RBTree *&tr, RBTree *node) {
    RBTree *grandParent = GrandParent(node);
    if (node->Parent->Right == node && grandParent->Left == node->Parent) {
        LeftTurn(tr, node->Parent);
        node = node->Left;
    }
    else {
        if (node->Parent->Left == node && grandParent->Right == node->Parent) {
            RightTurn(tr, node->Parent);
            node = node->Right;
        }
    }
    InsertCase5(tr, node);
}

void InsertCase5(RBTree *&tr, RBTree *node) {
    RBTree *grandParent = GrandParent(node);
    grandParent->Color = Red;
    node->Parent->Color = Black;
    if (node == node->Parent->Left && grandParent->Left == node->Parent) {
        RightTurn(tr, grandParent);
    }
    else {
        LeftTurn(tr, grandParent);
    }
}

void Insert(RBTree *&tr, RBTree *prev, int node) {
    if (node < prev->Value && !prev->Left) {
        prev->Left = Node(prev, node);
        InsertCase1(tr, prev->Left);
        return;
    }
    if (node > prev->Value && !prev->Right) {
        prev->Right = Node(prev, node);
        InsertCase1(tr, prev->Right);
        return;
    }
    if (node < prev->Value && prev->Left) {
        Insert(tr, prev->Left, node);
    }
    if (node > prev->Value && prev->Right) {
        Insert(tr, prev->Right, node);
    }
}

void DeleteCase1(RBTree *&tr, RBTree *node);
void DeleteCase2(RBTree *&tr, RBTree *node);
void DeleteCase3(RBTree *&tr, RBTree *node);
void DeleteCase4(RBTree *&tr, RBTree *node);
void DeleteCase5(RBTree *&tr, RBTree *node);
void DeleteCase6(RBTree *&tr, RBTree *node);

void DeleteCase1(RBTree *&tr, RBTree *node) {
    if (!node->Parent) {
        if (node->Left) {
            tr = node->Left;
        }
        else {
            tr = node->Right;
        }
    }
    else {
        DeleteCase2(tr, node);
    }
}

void DeleteCase2(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node);
    if (sibling->Color == Red) {
        node->Parent->Color = Red;
        sibling->Color = Black;
        if (node->Parent->Left == node) {
            LeftTurn(tr, node->Parent);
        }
        else {
            RightTurn(tr, node->Parent);
        }
    }
    DeleteCase3(tr, node);
}

void DeleteCase3(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node);
    if (sibling && node->Parent->Color == Black && sibling->Color == Black &&
        ((!sibling->Left) || sibling->Left->Color == Black) &&
        ((!sibling->Right) || sibling->Right->Color == Black)) {
        sibling->Color = Red;
        DeleteCase1(tr, node);
    }
    else {
        DeleteCase4(tr, node);
    }
}

void DeleteCase4(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node);

    if (sibling && node->Parent->Color == Red && sibling->Color == Black &&
        ((!sibling->Left) || sibling->Left->Color == Black) &&
        ((!sibling->Right) || sibling->Right->Color == Black)) {
        sibling->Color = Red;
        node->Parent->Color = Black;
    }
    else {
        DeleteCase5(tr, node);
    }
}

void DeleteCase5(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node);
    if (sibling && sibling->Color == Black) {
        if (node->Parent->Left == node &&
            ((sibling->Left) && sibling->Left->Color == Red) &&
            ((!sibling->Right) || sibling->Right->Color == Black)) {
            sibling->Color = Red;
            sibling->Left->Color = Black;
            RightTurn(tr, sibling);
        }
        else {
            if (node->Parent->Right == node &&
                ((sibling->Right) && sibling->Right->Color == Red) &&
                ((!sibling->Left) || sibling->Left->Color == Black)) {
                sibling->Color = Red;
                sibling->Right->Color = Black;
                LeftTurn(tr, sibling);
            }
        }
    }
    DeleteCase6(tr, node);
}

void DeleteCase6(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node);
    if (sibling) {

        sibling->Color = node->Parent->Color;

        node->Parent->Color = Black;
        if (node->Parent->Left == node) {
            sibling->Right->Color = Black;
            LeftTurn(tr, node->Parent);
        }
        else {
            sibling->Left->Color = Black;
            RightTurn(tr, node->Parent);
        }
    }
}

void Replace(RBTree *&tr, RBTree *node) {
    if (node->Left != nullptr) {
        RBTree *child = node->Left;

        // Родителем узла child становится родитель узла node
        child->Parent = node->Parent;
        if (node->Parent != nullptr) {
            if (node == node->Parent->Left) {
                node->Parent->Left = child;
            }
            else {
                node->Parent->Right = child;
            }
        }
    }
    else {
        RBTree *child = node->Right;

        // Родителем узла child становится родитель узла node
        child->Parent = node->Parent;
        if (node->Parent != nullptr) {
            if (node == node->Parent->Left) {
                node->Parent->Left = child;
            }
            else {
                node->Parent->Right = child;
            }
        }
    }
}

void DeleteOne(RBTree *&tr, RBTree *node) {
    // 2 ребенка
    if (node->Left && node->Right) {
        RBTree *buf;
        if (node->Value <= tr->Value) {
            buf = node->Left;
            while (buf->Right) {
                buf = buf->Right;
            }
        }
        else {
            buf = node->Right;
            while (buf->Left) {
                buf = buf->Left;
            }
        }
        std::swap(buf->Value, node->Value);
        node = buf;
    }
    // 1 ребенок
    if (node->Left || node->Right) {
        RBTree *child = nullptr;
        if (node->Left && !node->Right) {
            child = node->Left;
        }
        if (node->Right && !node->Left) {
            child = node->Right;
        }
        Replace(tr, node); // child - ребёнок деда
        if (node->Color == Black) {
            // Всегда node - чёрный, ребёнок - красный
            if (child->Color == Red) {
                child->Color = Black;
            }
            else {
                DeleteCase1(tr, node);
            }
        }
    }
    else // Нет детей
    {
        if (node->Color == Black) // Сложный случай
        {
            DeleteCase1(tr, node);
        }
        else // Вершина красная, просто удаляем
        {
            if (node == node->Parent->Left) {
                node->Parent->Left = nullptr;
            }
            else {
                node->Parent->Right = nullptr;
            }
        }
    }
    if (!node->Left && !node->Right) {
        if (node == node->Parent->Left) {
            node->Parent->Left = nullptr;
        }
        else if (node->Parent->Right == node) {
            node->Parent->Right = nullptr;
        }
    }
    delete node;
}

// Поиск
RBTree *Find(RBTree *tr, int value) {
    // Если КЧД кончился или нашли
    if (!tr || tr->Value == value) {
        return tr;
    }
    // Если Value > этого элемента
    if (tr->Value < value) {
        // Идем к правому ребенку
        return Find(tr->Right, value);
    }
    else {
        // Идем к левому ребенку
        return Find(tr->Left, value);
    }
}

void MaxHeight(RBTree *x, short &max, short deepness) {
    if (deepness > max) {
        max = deepness;
    }
    if (x) {
        if (x->Left) {
            MaxHeight(x->Left, max, deepness + 1);
        }
        if (x->Right) {
            MaxHeight(x->Right, max, deepness + 1);
        }
    }
}

std::string FormatNode(RBTree *node) {
    if (!node)
        return "     ";
    std::string val = std::to_string(node->Value);
    if (node->Color == Red)
        return "R" + val + std::string(4 - val.size(), ' ');
    else
        return "B" + val + std::string(4 - val.size(), ' ');
}

void PrintHelper(RBTree ***arr, RBTree *x, const short deepness,
                 const short ind) {
    arr[deepness][ind] = x;
    if (x->Left) {
        PrintHelper(arr, x->Left, deepness + 1, 2 * ind);
    }
    if (x->Right) {
        PrintHelper(arr, x->Right, deepness + 1, 2 * ind + 1);
    }
}

void Print(RBTree *x) {
    if (x) {
        short max = 1, offset = 1, width = 1;
        MaxHeight(x, max);
        RBTree ***arr = new RBTree **[max];
        for (short i = 0; i < max; ++i) {
            arr[i] = new RBTree *[offset];
            for (short j = 0; j < offset; ++j) {
                arr[i][j] = nullptr;
            }
            offset <<= 1;
        }
        offset <<= 1;
        PrintHelper(arr, x);
        for (short i = 0; i < max; ++i) {
            std::cout << std::setw((offset >> 1) + 1);
            std::cout << FormatNode(arr[i][0]);
            // arr[i][0] ? std::cout << arr[i][0]->Value : std::cout << ' ';
            for (short j = 1; j < width; ++j) {
                std::cout << std::setw(offset);
                std::cout << FormatNode(arr[i][j]);
                // arr[i][j] ? std::cout << arr[i][j]->Value : std::cout << ' ';
            }
            offset >>= 1;
            width <<= 1;
            std::cout << std::endl;
        }
        for (short i = 0; i < max; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
    }
}
