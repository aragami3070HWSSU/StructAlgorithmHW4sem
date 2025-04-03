#include <iomanip>
#include <iostream>


struct RBTree {
    int Color;
    int Value;
    RBTree *Right;
    RBTree *Left;
    RBTree *Parent;
};

RBTree *root(int x) {
    RBTree *n = new RBTree;
    n->Parent = n->Left = n->Right = NULL;
    n->Color = 1;
    n->Value = x;
    return n;
}

RBTree *node(RBTree *p, int x) {
    RBTree *n = new RBTree;
    n->Parent = p;
    n->Left = n->Right = NULL;
    n->Color = 0;
    n->Value = x;
    return n;
}

void LeftTurn(RBTree *&tr, RBTree *x) {
    RBTree *y = x->Right;
    y->Parent = x->Parent;
    if (x->Parent) {
        if (x->Parent->Left == x) {
            x->Parent->Left = y;
        }
        else {
            x->Parent->Right = y;
        }
    }
    x->Right = y->Left;
    if (y->Left) {
        y->Left->Parent = x;
    }
    if (y->Left != NULL) {
        y->Left->Parent = x;
    }
    x->Parent = y;
    y->Left = x;
    if (!y->Parent) {
        tr = y;
        tr->Color = 1;
    }
}

void RightTurn(RBTree *&tr, RBTree *x) {
    RBTree *y = x->Left;
    y->Parent = x->Parent;
    if (x->Parent) {
        if (x->Parent->Left == x) {
            x->Parent->Left = y;
        }
        else {
            x->Parent->Right = y;
        }
    }
    x->Left = y->Right;
    if (y->Right) {
        y->Parent = x;
    }
    if (y->Right != NULL) {
        y->Right->Parent = x;
    }
    x->Parent = y;
    y->Right = x;
    if (!y->Parent) {
        tr = y;
        tr->Color = 1;
    }
}

RBTree *grandParent(RBTree *x) {
    if (x && x->Parent) {
        return x->Parent->Parent;
    }
    return NULL;
}

RBTree *uncle(RBTree *x) {
    RBTree *g = grandParent(x);
    if (!g) {
        return NULL;
    }
    if (g->Left == x->Parent) {
        return g->Right;
    }
    return g->Left;
}

RBTree *sibling(RBTree *x) {
    if (x && x->Parent) {
        if (x->Parent->Left == x) {
            return x->Parent->Right;
        }
        return x->Parent->Left;
    }
    return NULL;
}

void insert_case1(RBTree *&tr, RBTree *x);
void insert_case2(RBTree *&tr, RBTree *x);
void insert_case3(RBTree *&tr, RBTree *x);
void insert_case4(RBTree *&tr, RBTree *x);
void insert_case5(RBTree *&tr, RBTree *x);

void insert_case1(RBTree *&tr, RBTree *x) {
    if (!x->Parent) {
        x->Color = 1;
    }
    else {
        insert_case2(tr, x);
    }
}

void insert_case2(RBTree *&tr, RBTree *x) {
    if (x->Parent->Color == 1) {
        return;
    }
    insert_case3(tr, x);
}

void insert_case3(RBTree *&tr, RBTree *x) {
    RBTree *u = uncle(x);
    RBTree *g = grandParent(x);
    if (u && u->Color == 0 && x->Parent->Color == 0) {
        u->Color = 1;
        x->Parent->Color = 1;
        g->Color = 0;
        insert_case1(tr, g);
    }
    else {
        insert_case4(tr, x);
    }
}

void insert_case4(RBTree *&tr, RBTree *x) {
    RBTree *g = grandParent(x);
    if (x->Parent->Right == x && g->Left == x->Parent) {
        LeftTurn(tr, x->Parent);
        x = x->Left;
    }
    else {
        if (x->Parent->Left == x && g->Right == x->Parent) {
            RightTurn(tr, x->Parent);
            x = x->Right;
        }
    }
    insert_case5(tr, x);
}

void insert_case5(RBTree *&tr, RBTree *x) {
    RBTree *g = grandParent(x);
    g->Color = 0;
    x->Parent->Color = 1;
    if (x == x->Parent->Left && g->Left == x->Parent) {
        RightTurn(tr, g);
    }
    else {
        LeftTurn(tr, g);
    }
}

void insert(RBTree *&tr, RBTree *prev, int x) {
    if (x < prev->Value && !prev->Left) {
        prev->Left = node(prev, x);
        insert_case1(tr, prev->Left);
        return;
    }
    if (x > prev->Value && !prev->Right) {
        prev->Right = node(prev, x);
        insert_case1(tr, prev->Right);
        return;
    }
    if (x < prev->Value && prev->Left) {
        insert(tr, prev->Left, x);
    }
    if (x > prev->Value && prev->Right) {
        insert(tr, prev->Right, x);
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
    if (s && s->Color == 0) {
        n->Parent->Color = 0;
        s->Color = 1;
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
    if (s && n->Parent->Color == 1 && s->Color == 1 &&
        (!s->Left || s->Left->Color == 1) &&
        (!s->Right || s->Right->Color == 1)) {
        s->Color = 0;
        delete_case1(tr, n->Parent); // just n
    }
    else {
        delete_case4(tr, n);
    }
}

void delete_case4(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (n->Parent->Color == 0 && s && s->Color == 1 &&
        (!s->Left || s->Left->Color == 1) &&
        (!s->Right || s->Right->Color == 1)) {
        s->Color = 0;
        n->Parent->Color = 1;
    }
    else {
        delete_case5(tr, n);
    }
}

void delete_case5(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (s->Color == 1) {
        if (s && n->Parent->Left == n && (!s->Left || s->Left->Color == 0) &&
            (!s->Right || s->Right->Color == 1)) {
            s->Color = 0;
            s->Left->Color = 1;
            RightTurn(tr, s);
        }
        else {
            if (s && n->Parent->Right == n &&
                (!s->Right || s->Right->Color == 0) &&
                (!s->Left || s->Left->Color == 1)) {
                s->Color = 0;
                s->Right->Color = 1;
                LeftTurn(tr, s);
            }
        }
    }
    delete_case6(tr, n);
}

void delete_case6(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    s->Color = n->Parent->Color;
    n->Parent->Color = 1;
    if (n->Parent->Left == n) {
        s->Right->Color = 1;
        LeftTurn(tr, n->Parent);
    }
    else {
        s->Left->Color = 1;
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
        if (n->Color == 1) {
            // Всегда n - чёрный, ребёнок - красный
            if (ch->Color == 0) {
                ch->Color = 1;
            }
        }
    }
    else // Нет детей
    {
        if (n->Color == 1) // Сложный случай
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
