#import "../conf.typ" : conf
#show: conf.with(
  title: [Анализ КЧД],
  type: "referat",
  info: (
      author: (
        name: [Смирнова Егора],
        faculty: [КНиИТ],
        group: "251",
        sex: "male"
      ),
      inspector: (
        degree: "",
        name: ""
      )
  ),
  settings: (
    title_page: (
      enabled: true
    ),
    contents_page: (
      enabled: true
    )
  )
)

= Код программы
```cpp
enum NodeColor { Black, Red };

struct RBTree {
    NodeColor Color;
    int Value;
    RBTree *Right;
    RBTree *Left;
    RBTree *Parent;
};

// Создание корня (черный)
RBTree *Root(int x) { // O(1)
    RBTree *n = new RBTree;
    n->Parent = n->Left = n->Right = nullptr;
    n->Color = Black;
    n->Value = x;
    return n;
}

// Создание узла (красный)
RBTree *Node(RBTree *p, int x) { // O(1)
    RBTree *n = new RBTree;
    n->Parent = p;
    n->Left = n->Right = nullptr;
    n->Color = Red;
    n->Value = x;
    return n;
}

void LeftTurn(RBTree *&tr, RBTree *node) { // O(1)
    RBTree *rightChild = node->Right; // O(1)
    node->Right = rightChild->Left; // O(1)

    if (rightChild->Left != nullptr) { // O(1)
        rightChild->Left->Parent = node; // O(1)
    }
    // Родителем для rightChild становится родитель node
    rightChild->Parent = node->Parent; // O(1)

    if (node->Parent) {
        if (node == node->Parent->Left) { // O(1)
            node->Parent->Left = rightChild; // O(1)
        }
        else {
            node->Parent->Right = rightChild; // O(1)
        }
    }
    rightChild->Left = node; // O(1)
    node->Parent = rightChild; // O(1)
    if (!rightChild->Parent) {
        tr = rightChild; // O(1)
        tr->Color = Black; // O(1)
    }
}


// Правый поворот
void RightTurn(RBTree *&tr, RBTree *node) { // O(1)
    RBTree *leftChild = node->Left; // O(1)
    node->Left = leftChild->Right; // O(1)

    if (leftChild->Right != nullptr) { // O(1)
        leftChild->Right->Parent = node; // O(1)
    }
    // Родителем для leftChild становится родитель node
    leftChild->Parent = node->Parent; // O(1)

    if (node->Parent) { // O(1)
        if (node == node->Parent->Left) { // O(1)
            node->Parent->Left = leftChild; // O(1)
        }
        else {
            node->Parent->Right = leftChild; // O(1)
        }
    }
    leftChild->Right = node; // O(1)
    node->Parent = leftChild; // O(1)
    if (!leftChild->Parent) { // O(1)
        tr = leftChild; // O(1)
        tr->Color = Black; // O(1)
    }
}


// Найти деда
RBTree *GrandParent(RBTree *node) { // O(1)
    // Деда не будет у фиктивного листа (node == nullptr) и у корня
    if (node && node->Parent) { // O(1)
        // Возвращаем родителя родителя текущего узла
        return node->Parent->Parent; // O(1)
    }
    return nullptr;
}

// Найти дядю
RBTree *Uncle(RBTree *node) { // O(1)
    // Дед узла node
    RBTree *grandParent = GrandParent(node); // O(1)
    // Если нет деда
    if (!grandParent) { // O(1)
        return nullptr; // O(1)
    }
    // Если родитель node --- левый ребенок grandPar
    if (grandParent->Left == node->Parent) { // O(1)
        // Возвращаем правого ребенка grandPar
        return grandParent->Right; // O(1)
    }
    // Возвращаем левого ребенка grandPar
    return grandParent->Left; // O(1)
}
// Найти брата
RBTree *Sibling(RBTree *node) { // O(1)
    // Если существует node и его Parent
    if (node && node->Parent) { // O(1)
        // Если node левый ребенок
        if (node->Parent->Left == node) { // O(1)
            // Возвращаем правого ребенка
            return node->Parent->Right; // O(1)
        }
        // Возвращаем левого ребенка
        return node->Parent->Left; // O(1)
    }
    return nullptr; // O(1)
}

void InsertCase1(RBTree *&tr, RBTree *node);
void InsertCase2(RBTree *&tr, RBTree *node);
void InsertCase3(RBTree *&tr, RBTree *node);
void InsertCase4(RBTree *&tr, RBTree *node);
void InsertCase5(RBTree *&tr, RBTree *node);

void InsertCase1(RBTree *&tr, RBTree *node) { // O(log n)
    if (!node->Parent) { // O(1)
        node->Color = Black; // O(1)
    }
    else {
        InsertCase2(tr, node); // O(log n)
    }
}

void InsertCase2(RBTree *&tr, RBTree *node) {
    if (node->Parent->Color == Black) {
        return; // O(1)
    }
    InsertCase3(tr, node); // O(log n)
}

void InsertCase3(RBTree *&tr, RBTree *node) {
    RBTree *uncle = Uncle(node); // O(1)
    RBTree *grandParent = GrandParent(node); // O(1)
    if (uncle && uncle->Color == Red && node->Parent->Color == Red) {
        uncle->Color = Black; // O(1)
        node->Parent->Color = Black; // O(1)
        grandParent->Color = Red; // O(1)
        InsertCase1(tr, grandParent); // O(log n)
    }
    else {
        InsertCase4(tr, node); // O(1)
    }
}

void InsertCase4(RBTree *&tr, RBTree *node) {
    RBTree *grandParent = GrandParent(node); // O(1)
    if (node->Parent->Right == node && grandParent->Left == node->Parent) {
        LeftTurn(tr, node->Parent); // O(1)
        node = node->Left; // O(1)
    }
    else {
        if (node->Parent->Left == node && grandParent->Right == node->Parent) {
            RightTurn(tr, node->Parent); // O(1)
            node = node->Right; // O(1)
        }
    }
    InsertCase5(tr, node); // O(1)
}

void InsertCase5(RBTree *&tr, RBTree *node) {
    RBTree *grandParent = GrandParent(node); // O(1)
    grandParent->Color = Red; // O(1)
    node->Parent->Color = Black; // O(1)
    if (node == node->Parent->Left && grandParent->Left == node->Parent) {
        RightTurn(tr, grandParent); // O(1)
    }
    else {
        LeftTurn(tr, grandParent); // O(1)
    }
}

void Insert(RBTree *&tr, RBTree *prev, int node) { // O(log n)
    if (node < prev->Value && !prev->Left) {
        prev->Left = Node(prev, node);
        InsertCase1(tr, prev->Left); // O(log n)
        return;
    }
    if (node > prev->Value && !prev->Right) {
        prev->Right = Node(prev, node);
        InsertCase1(tr, prev->Right); // O(log n)
        return;
    }
    if (node < prev->Value && prev->Left) {
        Insert(tr, prev->Left, node); // O(log n)
    }
    if (node > prev->Value && prev->Right) {
        Insert(tr, prev->Right, node); // O(log n)
    }
}

void DeleteCase1(RBTree *&tr, RBTree *node);
void DeleteCase2(RBTree *&tr, RBTree *node);
void DeleteCase3(RBTree *&tr, RBTree *node);
void DeleteCase4(RBTree *&tr, RBTree *node);
void DeleteCase5(RBTree *&tr, RBTree *node);
void DeleteCase6(RBTree *&tr, RBTree *node);

void DeleteCase1(RBTree *&tr, RBTree *node) { // O(log n)
    if (!node->Parent) { // O(1)
        if (node->Left) { // O(1)
            tr = node->Left; // O(1)
        }
        else {
            tr = node->Right; // O(1)
        }
    }
    else {
        DeleteCase2(tr, node); // O(log n)
    }
}

void DeleteCase2(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node);
    if (sibling->Color == Red) { // O(1)
        node->Parent->Color = Red; // O(1)
        sibling->Color = Black; // O(1)
        if (node->Parent->Left == node) { // O(1)
            LeftTurn(tr, node->Parent); // O(1)
        }
        else {
            RightTurn(tr, node->Parent); // O(1)
        }
    }
    DeleteCase3(tr, node); // O(log n)
}

void DeleteCase3(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node); // O(1)
    if (sibling && node->Parent->Color == Black && sibling->Color == Black &&
        ((!sibling->Left) || sibling->Left->Color == Black) &&
        ((!sibling->Right) || sibling->Right->Color == Black)) {
        sibling->Color = Red;
        DeleteCase1(tr, node); // O(log n)
    }
    else {
        DeleteCase4(tr, node); // O(1)
    }
}

void DeleteCase4(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node); // O(1)

    if (sibling && node->Parent->Color == Red && sibling->Color == Black &&
        ((!sibling->Left) || sibling->Left->Color == Black) &&
        ((!sibling->Right) || sibling->Right->Color == Black)) { // O(1)
        sibling->Color = Red; // O(1)
        node->Parent->Color = Black; // O(1)
    }
    else { // O(1)
        DeleteCase5(tr, node); // O(1)
    }
}

void DeleteCase5(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node); // O(1)
    if (sibling && sibling->Color == Black) { // O(1)
        if (node->Parent->Left == node &&
            ((sibling->Left) && sibling->Left->Color == Red) &&
            ((!sibling->Right) || sibling->Right->Color == Black)) { // O(1)
            sibling->Color = Red; // O(1)
            sibling->Left->Color = Black; // O(1)
            RightTurn(tr, sibling); // O(1)
        }
        else { // O(1)
            if (node->Parent->Right == node &&
                ((sibling->Right) && sibling->Right->Color == Red) &&
                ((!sibling->Left) || sibling->Left->Color == Black)) { // O(1)
                sibling->Color = Red; // O(1)
                sibling->Right->Color = Black; // O(1)
                LeftTurn(tr, sibling); // O(1)
            }
        }
    }
    DeleteCase6(tr, node); // O(1)
}

void DeleteCase6(RBTree *&tr, RBTree *node) {
    RBTree *sibling = Sibling(node); // O(1)
    if (sibling) { // O(1)

        sibling->Color = node->Parent->Color; // O(1)

        node->Parent->Color = Black; // O(1)
        if (node->Parent->Left == node) { // O(1)
            sibling->Right->Color = Black; // O(1)
            LeftTurn(tr, node->Parent); // O(1)
        }
        else { // O(1)
            sibling->Left->Color = Black; // O(1)
            RightTurn(tr, node->Parent); // O(1)
        }
    }
}

void Replace(RBTree *&tr, RBTree *node) {
    if (node->Left != nullptr) {
        RBTree *child = node->Left; // O(1)

        // Родителем узла child становится родитель узла node
        child->Parent = node->Parent; // O(1)
        if (node->Parent != nullptr) { // O(1)
            if (node == node->Parent->Left) {
                node->Parent->Left = child; // O(1)
            }
            else {
                node->Parent->Right = child; // O(1)
            }
        }
    }
    else {
        RBTree *child = node->Right; // O(1)

        // Родителем узла child становится родитель узла node
        child->Parent = node->Parent; // O(1)
        if (node->Parent != nullptr) { // O(1)
            if (node == node->Parent->Left) {
                node->Parent->Left = child; // O(1)
            }
            else {
                node->Parent->Right = child; // O(1)
            }
        }
    }
}

void DeleteOne(RBTree *&tr, RBTree *node) {
    // 2 ребенка
    if (node->Left && node->Right) {
        RBTree *buf; // O(1)
        buf = node->Left; // O(1)
        while (buf->Right) { // O(log n)
            buf = buf->Right; // O(1)
        }
        std::swap(buf->Value, node->Value); // O(1)
        node = buf; // O(1)
    }
    // 1 ребенок
    if (node->Left || node->Right) {
        RBTree *child = nullptr; // O(1)
        if (node->Left && !node->Right) {
            child = node->Left; // O(1)
        }
        if (node->Right && !node->Left) {
            child = node->Right; // O(1)
        }
        Replace(tr, node); // child - ребёнок деда
        if (node->Color == Black) {
            // node - чёрный, ребёнок - красный
            if (child->Color == Red) {
                child->Color = Black; // O(1)
            }
            else {
                DeleteCase1(tr, node); // O(log n)
            }
        }
    }
    else // Нет детей
    {
        if (node->Color == Black) // Сложный случай
        {
            DeleteCase1(tr, node); // O(log n)
        }
        else // Вершина красная, просто удаляем
        { // O(1)
            if (node == node->Parent->Left) {
                node->Parent->Left = nullptr; // O(1)
            }
            else {
                node->Parent->Right = nullptr; // O(1)
            }
        }
    }
    if (!node->Left && !node->Right) {
        if (node == node->Parent->Left) {
            node->Parent->Left = nullptr; // O(1)
        }
        else if (node->Parent->Right == node) {
            node->Parent->Right = nullptr; // O(1)
        }
    }
    delete node; // O(1)
}

// Поиск
RBTree *Find(RBTree *tr, int value) { // O(log n)
    // Если КЧД кончился или нашли
    if (!tr || tr->Value == value) {
        return tr; // O(1)
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

```

= Анализ сложности

== Повороты
LeftTurn и RightTurn работают за константное время.

== Поиск
Любое красно-черное дерево с $n$ узлами имеет высоту $h = log(n)$, так как оно сбалансированное.

// Для доказательства этого факта рассмотрим дерево с высотой $h$. Так как у красной вершины черные дети, то количество красных вершин не больше $h/2$. Тогда черных вершин не меньше $h/2 - 1$. Число внутренних вершин $n$ не меньше $2^(h/2 - 1)$. Прологарифмируем неравенство: $log(n + 1) gt.eq h/2 space => space 2 log(n + 1) gt.eq h space => space h lt.eq 2 log(n + 1)$

== Обходы
Все обходы занимают $O(n)$, так как нужно пройитсь по всем элементам.

== Вставка
Вставка в непустое дерево состоит из трех этапов:
+ Обычная вставка в дерево поиска: так как кчд является сбалансированным, то вставка занимает $O(log n)$.
+ Окраска нового узла: происходит за константное время.
+ Восстановление свойств: так как востановление свойств в худшем случае состоит из не более чем 2 поворотов, каждый из которых занимает $O(1)$. В случчае, если требуется перекрасить другие узлы дерева, то перекраска будет идти до корня (его цвет в любом случае черный). Высота дерева состовляет $log(n)$, соответственно в худшем случае перекраска будет занимать $O(log(n))$.

Так как операция вставки и востановления выполняются последовательно, то по правилу суммы общая временная сложность вставки нового элемента в дерево будет занимать $O(log(n))$

== Удаление
- Нахождение узла для удаления занимает $O(log n)$, така как дерево сбалансированное.
- Затем производится востановление свойств дерева, которое в худшем случае требует 3 поворота, которые занимают $O(1)$.
- Перекраска для сохранения свойств выполняется аналогично случаю со вставкой.

Общая временная сложность удаления будет занимать $O(log n)$.

// == Расход по памяти
// Каждый узел кчд имее фиксированный размер и не требует выделения дополнительной памяти. Данные о цвете узла занимают $O(1)$. Таким образом, сложность по памяти для дерева из $n$ узлов составит $O(log(n))$
//
// == Лучший случай
// Если никакие свойства дерева не нарушены не были или произошло перекрашивание за константное время, то сложность алгоритма $O(log n)$
// == Худший случай
// Балансировка дерева происходит по высоте дерева $O(log n)$, но обычно тербуется не более 2 поворотов за константное время, то временная сложность алгоритма $O(log n)$
// == Средний случай
// Временная сложность также составляет $O(log n)$.
