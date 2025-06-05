#import "../conf.typ" : conf
#show: conf.with(
  title: [Анализ двоичного дерева поиска],
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
// Binary Tree
struct Tree {
    int Value;
    Tree *Left;
    Tree *Right;
    Tree *Parent;
};

Tree *Node(int value) {
    // Create new node
    Tree *newNode = new Tree;
    newNode->Value = value;
    // Set null for parent and childern
    newNode->Parent = nullptr;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    return newNode;
}

void Insert(Tree *&tr, int value) {
    // Create new node
		// Создание O(1)
    Tree *newNode = Node(value);
    // If tree empty
		// O(1)
    if (!tr) {
        // Then new node is root
				// O(1)
        tr = newNode;
    }
    else {
        // Create temp pointer on tree
        Tree *temp = tr;// O(1)
				// В худшем случае O(n)
				// В лучшем и среднем O(log(n))
        while (temp) {
            // If new elem > temp elem
            if (newNode->Value > temp->Value) {
                // If temp have right child
                if (temp->Right) {
                    // Then move temp pointer to right child
                    temp = temp->Right;// O(1)
                }
                else {
                    // New elem is right child temp
                    newNode->Parent = temp;// O(1)
                    temp->Right = newNode;// O(1)
                    break;
                }
            }
            // Esle if new elem < temp elem
            else {
                // If temp have left child
                if (temp->Left) {
                    // Then move temp pointer to left child
                    temp = temp->Left;// O(1)
                }
                else {
                    // New elem is left child temp
                    newNode->Parent = temp;// O(1)
                    temp->Left = newNode;// O(1)
                    break;
                }
            }
        }
    }
}

Tree *Min(Tree *tr) { // O(log(n))
    // If not left child
    if (!tr->Left) {
        // Return tr
        return tr;
    }
    else {
        // Go to left branch to the end
        return Min(tr->Left);
    }
}

Tree *Next(Tree *tr, int value) { // O(log(n))
    Tree *node = Find(tr, value);
    // Have right child
    if (node->Right) { // O(log(n))
        // Min in right branch
        return Min(node->Right);
    }
    // Parent
    Tree *nodeParent = node->Parent;
    // While not root or node is right parent
    while (nodeParent && node == nodeParent->Right) {// O(log(n))
        // Go up the tree
        node = nodeParent;
        nodeParent = nodeParent->Parent;
    }
    return nodeParent;
}

// Т.к. сначала node надо найти, то прибавим еще O(log(n))
void Delete(Tree *&tr, Tree *node) {
    // Create delete node parent
    Tree *nodeParent = node->Parent;// O(1)
    // Tree have only one node
    if (!nodeParent) {
        tr = nullptr;// O(1)
    }
    // Node haven't children
    else if (!node->Left && !node->Right) {
        // Set nullptr pointer on node in parent
        if (nodeParent->Left == node) {
            nodeParent->Left = nullptr;// O(1)
        }
        if (nodeParent->Right == node) {
            nodeParent->Right = nullptr;// O(1)
        }
        delete node;
    }
    // If only one child
    else if (!node->Left || !node->Right) {
        // If delete root which have 1 child
        if (!nodeParent) {
            // If have right child
            if (!node->Left) {
                // His become root
                tr = node->Right;// O(1)
                node->Parent = nullptr;// O(1)
            }
            // If have left child
            else {
                // His become root
                tr = node->Left;// O(1)
                node->Parent = nullptr;// O(1)
            }
        }
        else {
            // If have right child
            if (!node->Left) {
                if (nodeParent->Left == node) {
                    // child of node become child of his "grandpa"
                    nodeParent->Left = node->Right;// O(1)
                }
                else {
                    // child of node become child of his "grandpa"
                    nodeParent->Right = node->Right;// O(1)
                }
                // "Grandpa" become parent of this child
                node->Right->Parent = nodeParent;// O(1)
            }
            else {
                if (nodeParent->Left == node) {
                    // child of node become child of his "grandpa"
                    nodeParent->Left = node->Left;// O(1)
                }
                else {
                    // child of node become child of his "grandpa"
                    nodeParent->Right = node->Left;// O(1)
                }
                // "Grandpa" become parent of this child
                node->Left->Parent = nodeParent;// O(1)
            }
            delete node;
        }
    }
    // Have 2 child
    else {
        // Next after deleting node
        Tree *succ = Next(tr, node->Value);// O(1)
        node->Value = succ->Value;// O(1)

        // succ is left child
        if (succ->Parent->Left == succ) {
            // His right child become left child of child's "grandpa"
            succ->Parent->Left = succ->Right;// O(1)
            // This child exist
            if (succ->Right) {
                // His "grandpa" become his parent
                succ->Right->Parent = succ->Parent;// O(1)
            }
        }
        else {
            // His right child become right child of child's "grandpa"
            succ->Parent->Right = succ->Right;// O(1)
            // This child exist
            if (succ->Right) {
                // His "grandpa" become his parent
                succ->Right->Parent = succ->Parent;// O(1)
            }
        }
        delete succ;
    }
}

// Рекурсивный поиск узла в дереве
Tree *Find(Tree *tr, int value) { // O(log(n))
    // If find or tree end
		// Операция сравнения O(1)
    if (tr->Value == value || !tr) {
        return tr;
    }
    // If value > this elem
		// Операция сравнения O(1)
    if (tr->Value < value) {
        // Go to right child
        return Find(tr->Right, value);
    }
    else {
        // Go to left child
        return Find(tr->Left, value);
    }
}

void InOrder(Tree *tr) { // O(n)
    if (tr) {
        // Go to Left child
        InOrder(tr->Left);
        // Output elem
        std::cout << tr->Value << " ";
        // Go to Right child
        InOrder(tr->Right);
    }
}

void PreOrder(Tree *tr) { // O(n)
    if (tr) {
        // Output elem
        std::cout << tr->Value << " ";
        // Go to Left child
        PreOrder(tr->Left);
        // Go to Right child
        PreOrder(tr->Right);
    }
}

void PostOrder(Tree *tr) { // O(n)
    if (tr) {
        // Go to Left child
        PostOrder(tr->Left);
        // Go to Right child
        PostOrder(tr->Right);
        // Output elem
        std::cout << tr->Value << " ";
    }
}
```

= Анализ сложности
$n$ --- количество элементов в дереве, $h$ --- высота дерева
== Случаи бинарного дерева
=== Худший случай
Дерево является вырожденным. У каждого узла только правый или только левый потомок. Высота  дерева в этом случае будет равна $= n$
=== Лучший случай
Дерево  сбалансировано. Высота одного поддерева отличается от высоты другого не более чем на 1. Высота такого дерева равна $log n$
=== Средний случай
Любое дерево, не являющееся вырожденным и сбалансированным. Высота(h): $log n lt h lt n$

== Вставка элемента
Максимальное количество сравнений зависит от высоты дерева.
=== Худший случай
В худшем случае вставка произойдет за $O(n)$ сравнений, в крайний правый или левый узел.
=== Лучший случай
В лучшем случае вставка произойдет за $O(log n)$ сравнений.
=== Средний случай
В среднем случае вставка произойдет за $O(log n)$ сравнений.

== Поиск элемента
=== Лучший случай
Проходим через узлы один за другим. Если мы найдем элелемент на втором уровне, то мы сделаем 2 сравнения, если на третьем, то 3 и т. д. Таким образом, на поиск ключа мы затратим время равное высоте дерева, то есть $log n$, поэтому временная сложность поиска в лучшем случае составит $O(log n)$
=== Худший случай
В худшем случае будет поиск крайнего правого или левого узла, за $O(n)$ сравнений
=== Средний случай
Высота дерева равна $log n$. В среднем будет проведено $O(log n)$ сравнений, как и в лучшем случае.

== Обходы
Все обходы занимают $O(n)$, так как нужно пройитсь по всем элементам.

== Удаление
- Если в дереве только корень, то нужно перезаписать его на null $O(1)$
- Если нет детей, то мы заменяем указатели родителей удаляемого элемента на null $O(1)$
- Если только один ребенок, то переобозначаем связи и удаление займет $O(1)$
- Если есть оба ребенка, то находим следующий, вызывая функцию next. next выполняется за $O(log n)$. После переобозначаем связи и удаление объекта. Конечная сложность $O(1) + O(log n) = O(log n)$.

В коде имеется фиксированное количество операций сравнения. Удаление занимет $O(1)$, без учета на вызов функции поиска для нахождения узла, который нужно удалить
