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
RBTree *root(int x) {
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
RBTree *grandParent(RBTree *node) {
	// Деда не будет у фиктивного листа (node == null) и у корня (node->Parent == null)
    if (node && node->Parent) {
		// Возвращаем родителя родителя текущего узла
        return node->Parent->Parent;
    }
    return NULL;
}

// Найти дядю
RBTree *uncle(RBTree *node) {
	// Дед узла node
    RBTree *grandPar = grandParent(node);
	// Если нет деда
    if (!grandPar) {
        return NULL;
    }
	// Если родитель node --- левый ребенок grandPar
    if (grandPar->Left == node->Parent) {
		// Возвращаем правого ребенка grandPar
        return grandPar->Right;
    }
	// Возвращаем левого ребенка grandPar
    return grandPar->Left;
}
// Найти брата
RBTree *sibling(RBTree *node) {
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

void insert_case1(RBTree *&tr, RBTree *node);
void insert_case2(RBTree *&tr, RBTree *node);
void insert_case3(RBTree *&tr, RBTree *node);
void insert_case4(RBTree *&tr, RBTree *node);
void insert_case5(RBTree *&tr, RBTree *node);

void insert_case1(RBTree *&tr, RBTree *node) {
    if (!node->Parent) {
        node->Color = Black;
    }
    else {
        insert_case2(tr, node);
    }
}

void insert_case2(RBTree *&tr, RBTree *node) {
    if (node->Parent->Color == Black) {
        return;
    }
    insert_case3(tr, node);
}

void insert_case3(RBTree *&tr, RBTree *node) {
    RBTree *u = uncle(node);
    RBTree *g = grandParent(node);
    if (u && u->Color == Red && node->Parent->Color == Red) {
        u->Color = Black;
        node->Parent->Color = Black;
        g->Color = Red;
        insert_case1(tr, g);
    }
    else {
        insert_case4(tr, node);
    }
}

void insert_case4(RBTree *&tr, RBTree *node) {
    RBTree *g = grandParent(node);
    if (node->Parent->Right == node && g->Left == node->Parent) {
        LeftTurn(tr, node->Parent);
        node = node->Left;
    }
    else {
        if (node->Parent->Left == node && g->Right == node->Parent) {
            RightTurn(tr, node->Parent);
            node = node->Right;
        }
    }
    insert_case5(tr, node);
}

void insert_case5(RBTree *&tr, RBTree *node) {
    RBTree *g = grandParent(node);
    g->Color = Red;
    node->Parent->Color = Black;
    if (node == node->Parent->Left && g->Left == node->Parent) {
        RightTurn(tr, g);
    }
    else {
        LeftTurn(tr, g);
    }
}

void insert(RBTree *&tr, RBTree *prev, int node) {
    if (node < prev->Value && !prev->Left) {
        prev->Left = Node(prev, node);
        insert_case1(tr, prev->Left);
        return;
    }
    if (node > prev->Value && !prev->Right) {
        prev->Right = Node(prev, node);
        insert_case1(tr, prev->Right);
        return;
    }
    if (node < prev->Value && prev->Left) {
        insert(tr, prev->Left, node);
    }
    if (node > prev->Value && prev->Right) {
        insert(tr, prev->Right, node);
    }
}

void delete_case1(RBTree *&tr, RBTree *n);
void delete_case2(RBTree *&tr, RBTree *n);
void delete_case3(RBTree *&tr, RBTree *n);
void delete_case4(RBTree *&tr, RBTree *n);
void delete_case5(RBTree *&tr, RBTree *n);
void delete_case6(RBTree *&tr, RBTree *n);

void delete_case1(RBTree *&tr, RBTree *n) {
    if (!n->Parent) {
        if (n->Left) {
            tr = n->Left;
        }
        else {
            tr = n->Right;
        }
    }
    else {
        delete_case2(tr, n);
    }
}

void delete_case2(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (s && s->Color == Red) {
        n->Parent->Color = Red;
        s->Color = Black;
        if (n->Parent->Left == n) {
            LeftTurn(tr, n->Parent);
        }
        else {
            RightTurn(tr, n->Parent);
        }
    }
    delete_case3(tr, n);
}

void delete_case3(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (s && n->Parent->Color == Black && s->Color == Black &&
        (!s->Left || s->Left->Color == Black) &&
        (!s->Right || s->Right->Color == Black)) {
        s->Color = Red;
        delete_case1(tr, n->Parent); // just n
    }
    else {
        delete_case4(tr, n);
    }
}

void delete_case4(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (n->Parent->Color == Red && s && s->Color == Black &&
        (!s->Left || s->Left->Color == Black) &&
        (!s->Right || s->Right->Color == Black)) {
        s->Color = Red;
        n->Parent->Color = Black;
    }
    else {
        delete_case5(tr, n);
    }
}

void delete_case5(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (s->Color == Black) {
        if (s && n->Parent->Left == n && (!s->Left || s->Left->Color == Red) &&
            (!s->Right || s->Right->Color == Black)) {
            s->Color = Red;
            s->Left->Color = Black;
            RightTurn(tr, s);
        }
        else {
            if (s && n->Parent->Right == n &&
                (!s->Right || s->Right->Color == Red) &&
                (!s->Left || s->Left->Color == Black)) {
                s->Color = Red;
                s->Right->Color = Black;
                LeftTurn(tr, s);
            }
        }
    }
    delete_case6(tr, n);
}

void delete_case6(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    s->Color = n->Parent->Color;
    n->Parent->Color = Black;
    if (n->Parent->Left == n) {
        s->Right->Color = Black;
        LeftTurn(tr, n->Parent);
    }
    else {
        s->Left->Color = Black;
        RightTurn(tr, n->Parent);
    }
}

void replace(RBTree *&tr, RBTree *v,
             RBTree *ch) { // Делаем ребёнка вершины v ребёнком деда
    ch->Parent = v->Parent;
    if (v->Parent) {
        if (v == v->Parent->Left) {
            v->Parent->Left = ch;
        }
        else {
            v->Parent->Right = ch;
        }
    }
    else {
        tr = ch;
    }
}

void DeleteOne(RBTree *&tr, RBTree *n) {
    if (n->Left && n->Right) {
        RBTree *u = n->Left;
        while (u->Right) {
            u = u->Right;
        }
		std::swap(u->Value, n->Value);
        n = u;
    }
    // Всегда 1 или 0 детей
    if (n->Left || n->Right) {
        RBTree *ch;
        if (n->Left) {
            ch = n->Left;
        }
        else {
            ch = n->Right;
        }
        replace(tr, n, ch); // child - ребёнок деда
        if (n->Color == Black) {
            // Всегда n - чёрный, ребёнок - красный
            if (ch->Color == Red) {
                ch->Color = Black;
            }
        }
    }
    else // Нет детей
    {
        if (n->Color == Black) // Сложный случай
        {
            delete_case1(tr, n);
        }
        else // Вершина красная, просто удаляем
        {
            if (n == n->Parent->Left) {
                n->Parent->Left = NULL;
            }
            else {
                n->Parent->Right = NULL;
            }
        }
    }
    if (n->Parent != NULL) {
        RBTree *buf = n;
        while (buf->Parent) {
            buf = buf->Parent;
        }
        tr = buf;
        if (n == n->Parent->Left) {
            n->Parent->Left = NULL;
        }
        else if (n->Parent->Right == n) {
            n->Parent->Right = NULL;
        }
    }
    delete n;
}

// Поиск
RBTree *Find(RBTree *tr, int Value) {
	// Если КЧД кончился или нашли
    if (!tr || tr->Value == Value) {
        return tr;
    }
    // Если Value > этого элемента
    if (tr->Value < Value) {
		// Идем к правому ребенку
        return Find(tr->Right, Value);
    }
    else {
		// Идем к левому ребенку
        return Find(tr->Left, Value);
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
            tr = root(x);
        }
		// Если есть корень
        else {
			// То создаем узел
            insert(tr, tr, x);
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
