#include <iomanip>
#include <iostream>

enum NodeColor{
	Black,
	Red
};

struct RBTree {
    NodeColor Color;
    int Value;
    RBTree *Right;
    RBTree *Left;
    RBTree *Parent;
};

// Создание корня (черный)
RBTree *Root(int x) {
    RBTree *n = new RBTree;
    n->Parent = n->Left = n->Right = NULL;
    n->Color = Black;
    n->Value = x;
    return n;
}

// Создание узла (красный)
RBTree *Node(RBTree *p, int x) {
    RBTree *n = new RBTree;
    n->Parent = p;
    n->Left = n->Right = NULL;
    n->Color = Red;
    n->Value = x;
    return n;
}

// Левый поворот
void LeftTurn(RBTree *&tr, RBTree *node) {
    RBTree *rightChild = node->Right;
    rightChild->Parent = node->Parent;
    if (node->Parent) {
        if (node->Parent->Left == node) {
            node->Parent->Left = rightChild;
        }
        else {
            node->Parent->Right = rightChild;
        }
    }
    node->Right = rightChild->Left;
    if (rightChild->Left) {
        rightChild->Left->Parent = node;
    }
    if (rightChild->Left != NULL) {
        rightChild->Left->Parent = node;
    }
    node->Parent = rightChild;
    rightChild->Left = node;
    if (!rightChild->Parent) {
        tr = rightChild;
        tr->Color = Black;
    }
}

// Правый поворот
void RightTurn(RBTree *&tr, RBTree *node) {
    RBTree *leftChild = node->Left;
    leftChild->Parent = node->Parent;
    if (node->Parent) {
        if (node->Parent->Left == node) {
            node->Parent->Left = leftChild;
        }
        else {
            node->Parent->Right = leftChild;
        }
    }
    node->Left = leftChild->Right;
    if (leftChild->Right) {
        leftChild->Parent = node;
    }
    if (leftChild->Right != NULL) {
        leftChild->Right->Parent = node;
    }
    node->Parent = leftChild;
    leftChild->Right = node;
    if (!leftChild->Parent) {
        tr = leftChild;
        tr->Color = Black;
    }
}

// Найти деда
RBTree *GrandParent(RBTree *node) {
	// Деда не будет у фиктивного листа (node == null) и у корня (node->Parent == null)
    if (node && node->Parent) {
		// Возвращаем родителя родителя текущего узла
        return node->Parent->Parent;
    }
    return NULL;
}

// Найти дядю
RBTree *Uncle(RBTree *node) {
	// Дед узла node
    RBTree *grandParent = GrandParent(node);
	// Если нет деда
    if (!grandParent) {
        return NULL;
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
    return NULL;
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
    RBTree *s = Sibling(node);
    if (s && s->Color == Red) {
        node->Parent->Color = Red;
        s->Color = Black;
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
        (!sibling->Left || sibling->Left->Color == Black) &&
        (!sibling->Right || sibling->Right->Color == Black)) {
        sibling->Color = Red;
        DeleteCase1(tr, node->Parent);
    }
    else {
        DeleteCase4(tr, node);
    }
}

void DeleteCase4(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node);
    if (node->Parent->Color == Red && sibling && sibling->Color == Black &&
        (!sibling->Left || sibling->Left->Color == Black) &&
        (!sibling->Right || sibling->Right->Color == Black)) {
        sibling->Color = Red;
        node->Parent->Color = Black;
    }
    else {
        DeleteCase5(tr, node);
    }
}

void DeleteCase5(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node);
    if (sibling->Color == Black) {
        if (sibling && node->Parent->Left == node && (!sibling->Left || sibling->Left->Color == Red) &&
            (!sibling->Right || sibling->Right->Color == Black)) {
            sibling->Color = Red;
            sibling->Left->Color = Black;
            RightTurn(tr, sibling);
        }
        else {
            if (sibling && node->Parent->Right == node &&
                (!sibling->Right || sibling->Right->Color == Red) &&
                (!sibling->Left || sibling->Left->Color == Black)) {
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

void replace(RBTree *&tr, RBTree *node,
             RBTree *child) {
	// Делаем ребёнка вершины node ребёнком деда
    child->Parent = node->Parent;
    if (node->Parent) {
        if (node == node->Parent->Left) {
            node->Parent->Left = child;
        }
        else {
            node->Parent->Right = child;
        }
    }
    else {
        tr = child;
    }
}

void DeleteOne(RBTree *&tr, RBTree *node) {
    if (node->Left && node->Right) {
        RBTree *buf = node->Left;
        while (buf->Right) {
            buf = buf->Right;
        }
		std::swap(buf->Value, node->Value);
        node = buf;
    }
    // Всегда 1 или 0 детей
    if (node->Left || node->Right) {
        RBTree *child;
        if (node->Left) {
            child = node->Left;
        }
        else {
            child = node->Right;
        }
        replace(tr, node, child); // child - ребёнок деда
        if (node->Color == Black) {
            // Всегда n - чёрный, ребёнок - красный
            if (child->Color == Red) {
                child->Color = Black;
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
                node->Parent->Left = NULL;
            }
            else {
                node->Parent->Right = NULL;
            }
        }
    }
    if (node->Parent != NULL) {
        RBTree *buf = node;
        while (buf->Parent) {
            buf = buf->Parent;
        }
        tr = buf;
        if (node == node->Parent->Left) {
            node->Parent->Left = NULL;
        }
        else if (node->Parent->Right == node) {
            node->Parent->Right = NULL;
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

void max_height(RBTree *x, short &max, short deepness = 1) {
    if (deepness > max) {
        max = deepness;
    }
    if (x->Left) {
        max_height(x->Left, max, deepness + 1);
    }
    if (x->Right) {
        max_height(x->Right, max, deepness + 1);
    }
}

void print_helper(RBTree ***arr, RBTree *x, const short deepness = 0,
                  const short ind = 0) {
    arr[deepness][ind] = x;
    if (x->Left) {
        print_helper(arr, x->Left, deepness + 1, 2 * ind);
    }
    if (x->Right) {
        print_helper(arr, x->Right, deepness + 1, 2 * ind + 1);
    }
}

void Print(RBTree *x) {
    if (x) {
        short max = 1, offset = 1, width = 1;
        max_height(x, max);
        RBTree ***arr = new RBTree **[max];
        for (short i = 0; i < max; ++i) {
            arr[i] = new RBTree *[offset];
            for (short j = 0; j < offset; ++j) {
                arr[i][j] = nullptr;
            }
            offset <<= 1;
        }
        offset <<= 1;
        print_helper(arr, x);
        for (short i = 0; i < max; ++i) {
            std::cout << std::setw((offset >> 1) + 1);
            arr[i][0] ? std::cout << arr[i][0]->Value : std::cout << ' ';
            for (short j = 1; j < width; ++j) {
                std::cout << std::setw(offset);
                arr[i][j] ? std::cout << arr[i][j]->Value : std::cout << ' ';
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

int main() {
    int n, x;
	// Вводим количество элементов
    std::cout << "Number of elements = ";
    std::cin >> n;
    RBTree *tr = NULL;
    std::cout << "Enter " << n << " elements: ";
	// Заполнение КЧД
    for (int i = 0; i < n; ++i) {
		// Вводим значение
        std::cin >> x;
		// Если нет корня
        if (i == 0) {
			// То создаем корень
            tr = Root(x);
        }
		// Если есть корень
        else {
			// То создаем узел
            Insert(tr, tr, x);
        }
    }

    RBTree *RBTree_root = tr;
	// Выводим созданное КЧД
    Print(RBTree_root);

	// Удаление всех узлов по введенному значению
    while (RBTree_root) {
		// Вводим значение узла
        std::cout << "Delete n" << std::endl;
        std::cout << "n = ";
        std::cin >> n;
		// Поиск узла по значению
        RBTree *node = Find(RBTree_root, n);
		// Если нашли узел
        if (node) {
			// Удаляем узел
            DeleteOne(RBTree_root, node);
			// Если это был последний узел
            if (!RBTree_root) {
                std::cout << "No elements in RBTree" << std::endl;
            }
            else {
				// Выводим КЧД
                Print(RBTree_root);
            }
        }
		// Не нашли узел
        else {
            std::cout << n << " not in RBTree" << std::endl;
        }
    }
}
