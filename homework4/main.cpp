#include <iomanip>
#include <iostream>


struct RBTree {
    RBTree *right;
    RBTree *left;
    RBTree *parent;
    int color;
    int val;
};

RBTree *root(int x) {
    RBTree *n = new RBTree;
    n->parent = n->left = n->right = NULL;
    n->color = 1;
    n->val = x;
    return n;
}

RBTree *node(RBTree *p, int x) {
    RBTree *n = new RBTree;
    n->parent = p;
    n->left = n->right = NULL;
    n->color = 0;
    n->val = x;
    return n;
}

void leftTurn(RBTree *&tr, RBTree *x) {
    RBTree *y = x->right;
    y->parent = x->parent;
    if (x->parent) {
        if (x->parent->left == x) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }
    if (y->left != NULL) {
        y->left->parent = x;
    }
    x->parent = y;
    y->left = x;
    if (!y->parent) {
        tr = y;
        tr->color = 1;
    }
}

void rightTurn(RBTree *&tr, RBTree *x) {
    RBTree *y = x->left;
    y->parent = x->parent;
    if (x->parent) {
        if (x->parent->left == x) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }
    x->left = y->right;
    if (y->right) {
        y->parent = x;
    }
    if (y->right != NULL) {
        y->right->parent = x;
    }
    x->parent = y;
    y->right = x;
    if (!y->parent) {
        tr = y;
        tr->color = 1;
    }
}

RBTree *grandparent(RBTree *x) {
    if (x && x->parent) {
        return x->parent->parent;
    }
    return NULL;
}

RBTree *uncle(RBTree *x) {
    RBTree *g = grandparent(x);
    if (!g) {
        return NULL;
    }
    if (g->left == x->parent) {
        return g->right;
    }
    return g->left;
}

RBTree *sibling(RBTree *x) {
    if (x && x->parent) {
        if (x->parent->left == x) {
            return x->parent->right;
        }
        return x->parent->left;
    }
    return NULL;
}

void insert_case1(RBTree *&tr, RBTree *x);
void insert_case2(RBTree *&tr, RBTree *x);
void insert_case3(RBTree *&tr, RBTree *x);
void insert_case4(RBTree *&tr, RBTree *x);
void insert_case5(RBTree *&tr, RBTree *x);

void insert_case1(RBTree *&tr, RBTree *x) {
    if (!x->parent) {
        x->color = 1;
    }
    else {
        insert_case2(tr, x);
    }
}

void insert_case2(RBTree *&tr, RBTree *x) {
    if (x->parent->color == 1) {
        return;
    }
    insert_case3(tr, x);
}

void insert_case3(RBTree *&tr, RBTree *x) {
    RBTree *u = uncle(x);
    RBTree *g = grandparent(x);
    if (u && u->color == 0 && x->parent->color == 0) {
        u->color = 1;
        x->parent->color = 1;
        g->color = 0;
        insert_case1(tr, g);
    }
    else {
        insert_case4(tr, x);
    }
}

void insert_case4(RBTree *&tr, RBTree *x) {
    RBTree *g = grandparent(x);
    if (x->parent->right == x && g->left == x->parent) {
        leftTurn(tr, x->parent);
        x = x->left;
    }
    else {
        if (x->parent->left == x && g->right == x->parent) {
            rightTurn(tr, x->parent);
            x = x->right;
        }
    }
    insert_case5(tr, x);
}

void insert_case5(RBTree *&tr, RBTree *x) {
    RBTree *g = grandparent(x);
    g->color = 0;
    x->parent->color = 1;
    if (x == x->parent->left && g->left == x->parent) {
        rightTurn(tr, g);
    }
    else {
        leftTurn(tr, g);
    }
}

void insert(RBTree *&tr, RBTree *prev, int x) {
    if (x < prev->val && !prev->left) {
        prev->left = node(prev, x);
        insert_case1(tr, prev->left);
        return;
    }
    if (x > prev->val && !prev->right) {
        prev->right = node(prev, x);
        insert_case1(tr, prev->right);
        return;
    }
    if (x < prev->val && prev->left) {
        insert(tr, prev->left, x);
    }
    if (x > prev->val && prev->right) {
        insert(tr, prev->right, x);
    }
}

void delete_case1(RBTree *&tr, RBTree *n);
void delete_case2(RBTree *&tr, RBTree *n);
void delete_case3(RBTree *&tr, RBTree *n);
void delete_case4(RBTree *&tr, RBTree *n);
void delete_case5(RBTree *&tr, RBTree *n);
void delete_case6(RBTree *&tr, RBTree *n);

void delete_case1(RBTree *&tr, RBTree *n) {
    if (!n->parent) {
        if (n->left) {
            tr = n->left;
        }
        else {
            tr = n->right;
        }
    }
    else {
        delete_case2(tr, n);
    }
}

void delete_case2(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (s && s->color == 0) {
        n->parent->color = 0;
        s->color = 1;
        if (n->parent->left == n) {
            leftTurn(tr, n->parent);
        }
        else {
            rightTurn(tr, n->parent);
        }
    }
    delete_case3(tr, n);
}

void delete_case3(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (s && n->parent->color == 1 && s->color == 1 &&
        (!s->left || s->left->color == 1) &&
        (!s->right || s->right->color == 1)) {
        s->color = 0;
        delete_case1(tr, n->parent); // just n
    }
    else {
        delete_case4(tr, n);
    }
}

void delete_case4(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (n->parent->color == 0 && s && s->color == 1 &&
        (!s->left || s->left->color == 1) &&
        (!s->right || s->right->color == 1)) {
        s->color = 0;
        n->parent->color = 1;
    }
    else {
        delete_case5(tr, n);
    }
}

void delete_case5(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    if (s->color == 1) {
        if (s && n->parent->left == n && (!s->left || s->left->color == 0) &&
            (!s->right || s->right->color == 1)) {
            s->color = 0;
            s->left->color = 1;
            rightTurn(tr, s);
        }
        else {
            if (s && n->parent->right == n &&
                (!s->right || s->right->color == 0) &&
                (!s->left || s->left->color == 1)) {
                s->color = 0;
                s->right->color = 1;
                leftTurn(tr, s);
            }
        }
    }
    delete_case6(tr, n);
}

void delete_case6(RBTree *&tr, RBTree *n) {
    RBTree *s = sibling(n);
    s->color = n->parent->color;
    n->parent->color = 1;
    if (n->parent->left == n) {
        s->right->color = 1;
        leftTurn(tr, n->parent);
    }
    else {
        s->left->color = 1;
        rightTurn(tr, n->parent);
    }
}

void replace(RBTree *&tr, RBTree *v,
             RBTree *ch) { // Делаем ребёнка вершины v ребёнком деда
    ch->parent = v->parent;
    if (v->parent) {
        if (v == v->parent->left) {
            v->parent->left = ch;
        }
        else {
            v->parent->right = ch;
        }
    }
    else {
        tr = ch;
    }
}

void delete_one(RBTree *&tr, RBTree *n) {
    if (n->left && n->right) {
        RBTree *u = n->left;
        while (u->right) {
            u = u->right;
        }
		std::swap(u->val, n->val);
        n = u;
    }
    // Всегда 1 или 0 детей
    if (n->left || n->right) {
        RBTree *ch;
        if (n->left) {
            ch = n->left;
        }
        else {
            ch = n->right;
        }
        replace(tr, n, ch); // child - ребёнок деда
        if (n->color == 1) {
            // Всегда n - чёрный, ребёнок - красный
            if (ch->color == 0) {
                ch->color = 1;
            }
        }
    }
    else // Нет детей
    {
        if (n->color == 1) // Сложный случай
        {
            delete_case1(tr, n);
        }
        else // Вершина красная, просто удаляем
        {
            if (n == n->parent->left) {
                n->parent->left = NULL;
            }
            else {
                n->parent->right = NULL;
            }
        }
    }
    if (n->parent != NULL) {
        RBTree *buf = n;
        while (buf->parent) {
            buf = buf->parent;
        }
        tr = buf;
        if (n == n->parent->left) {
            n->parent->left = NULL;
        }
        else if (n->parent->right == n) {
            n->parent->right = NULL;
        }
    }
    delete n;
}

RBTree *find(RBTree *pr, int val) {
    if (!pr || pr->val == val) {
        return pr;
    }
    if (pr->val > val) {
        return find(pr->left, val);
    }
    return find(pr->right, val);
}

void max_height(RBTree *x, short &max, short deepness = 1) {
    if (deepness > max) {
        max = deepness;
    }
    if (x->left) {
        max_height(x->left, max, deepness + 1);
    }
    if (x->right) {
        max_height(x->right, max, deepness + 1);
    }
}

void print_helper(RBTree ***arr, RBTree *x, const short deepness = 0,
                  const short ind = 0) {
    arr[deepness][ind] = x;
    if (x->left) {
        print_helper(arr, x->left, deepness + 1, 2 * ind);
    }
    if (x->right) {
        print_helper(arr, x->right, deepness + 1, 2 * ind + 1);
    }
}
void print(RBTree *x) {
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
            arr[i][0] ? std::cout << arr[i][0]->val : std::cout << ' ';
            for (short j = 1; j < width; ++j) {
                std::cout << std::setw(offset);
                arr[i][j] ? std::cout << arr[i][j]->val : std::cout << ' ';
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
    std::cout << "Number of elements = ";
    std::cin >> n;
    RBTree *tr = NULL;
    std::cout << "Enter " << n << " elems: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        if (i == 0) {
            tr = root(x);
        }
        else {
            insert(tr, tr, x);
        }
    }
    RBTree *RBTree_root = tr;
    print(RBTree_root);
    while (RBTree_root) {
        std::cout << "Let's delete n" << std::endl;
        std::cout << "x = ";
        std::cin >> x;
        RBTree *n = find(RBTree_root, x);
        if (n) {
            delete_one(RBTree_root, n);
            if (!RBTree_root) {
                std::cout << "No elems in RBTree" << std::endl;
            }
            else {
                print(RBTree_root);
            }
        }
        else {
            std::cout << x << " not in RBTree" << std::endl;
        }
    }
}
