#import "../conf.typ" : conf
#show: conf.with(
  title: [Анализ АВЛ дерева],
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
class AVLNode {
  public:
    int Value;
    AVLNode *Left;
    AVLNode *Right;
    int Height;

    AVLNode(int k) : Value(k), Left(nullptr), Right(nullptr), Height(1) {
    }
};

class AVLTree {
  private:
    AVLNode *root;

    int Height(AVLNode *node);
    int BalanceFactor(AVLNode *node);
    AVLNode *RightRotate(AVLNode *y);
    AVLNode *LeftRotate(AVLNode *x);
    AVLNode *Insert(AVLNode *node, int key);
    AVLNode *MinValueNode(AVLNode *node);
    AVLNode *DeleteNode(AVLNode *node, int key);
    void PrintHelper(AVLNode *root, std::string indent, bool last);

  public:
    AVLTree() : root(nullptr) {
    }

    void Insert(int key);
    void Remove(int key);
    void Print();
};

int AVLTree::Height(AVLNode *node) { // O(1)
    if (node == nullptr) {
				return 0;
		}
    return node->Height;
}

// Разница между высотами дерева левого и правого ребенка
int AVLTree::BalanceFactor(AVLNode *node) { // O(1)
    if (node == nullptr) {
				return 0;
		}
    return Height(node->Left) - Height(node->Right);
}

AVLNode *AVLTree::RightRotate(AVLNode *node) {
    AVLNode *leftNode = node->Left; // O(1)
    AVLNode *T2 = leftNode->Right; // O(1)

    leftNode->Right = node; // O(1)
    node->Left = T2; // O(1)

    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1; // O(1)
    leftNode->Height =
        std::max(Height(leftNode->Left), Height(leftNode->Right)) + 1; // O(1)

    return leftNode; // O(1)
}

AVLNode *AVLTree::LeftRotate(AVLNode *node) {
    AVLNode *rightChild = node->Right; // O(1)
    AVLNode *T2 = rightChild->Left; // O(1)

    rightChild->Left = node; // O(1)
    node->Right = T2; // O(1)

    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1; // O(1)
    rightChild->Height =
        std::max(Height(rightChild->Left), Height(rightChild->Right)) + 1; // O(1)

    return rightChild; // O(1)
}

AVLNode *AVLTree::Insert(AVLNode *node, int key) {
    if (node == nullptr) {
        return new AVLNode(key); // O(1)
    }
    if (key < node->Value) {
        node->Left = Insert(node->Left, key);
    }
    else if (key > node->Value) {
        node->Right = Insert(node->Right, key);
    }
    else {
        return node;
    }

		// Обновляем высоту узла
    node->Height = 1 + std::max(Height(node->Left), Height(node->Right));

		// Получаем BalanceFactor узла
    int balance = BalanceFactor(node);
  
		// Левый левый случай
    if (balance > 1 && key < node->Left->Value) {
        return RightRotate(node);
    }

		// Левый правый случай
    if (balance < -1 && key > node->Right->Value) {
        return LeftRotate(node);
    }

		// Правый правый случай
    if (balance > 1 && key > node->Left->Value) {
        node->Left = LeftRotate(node->Left);
        return RightRotate(node);
    }

		// Правый левый случай
    if (balance < -1 && key < node->Right->Value) {
        node->Right = RightRotate(node->Right);
        return LeftRotate(node);
    }
    return node;
}

void AVLTree::PrintHelper(AVLNode *root, std::string indent, bool last) {
    if (root != nullptr) {

        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        }
        else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->Value << "(" << root->Height << ")" << std::endl;
        PrintHelper(root->Left, indent, false);
        PrintHelper(root->Right, indent, true);
    }
}

void AVLTree::Print() {
    if (root == nullptr) {
        std::cout << "Дерево пустое." << std::endl;
    }
    else {
        std::cout << "AVL дерево:" << std::endl;
        PrintHelper(root, "", true);
    }
}

AVLNode *AVLTree::MinValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current->Left != nullptr) {
				current = current->Left;
		}
    return current;
}

AVLNode *AVLTree::DeleteNode(AVLNode *root, int key) {
    if (node == nullptr) {
				return node;
		}

    if (key < node->Value) {
				node->Left = DeleteNode(node->Left, key);
		}
    else if (key > node->Value) {
				node->Right = DeleteNode(node->Right, key);
		}
    else {
				// Узел с одним ребенком или без детей
        if ((node->Left == nullptr) || (node->Right == nullptr)) {
            AVLNode *temp = node->Left ? node->Left : node->Right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
								*node = *temp;
						}
            delete temp;
        }
        else {
            AVLNode *temp = MinValueNode(node->Right);
            node->Value = temp->Value;
            node->Right = DeleteNode(node->Right, temp->Value);
        }
    }

    if (node == nullptr){
        return node;
		}

		// Обновляем высоту узла
    node->Height = 1 + std::max(Height(node->Left), Height(node->Right));

		// Получаем BalanceFactor узла
    int balance = BalanceFactor(node);

		// Если узел небалансированный, тогда есть 4 случая

		// Левый левый случай
    if (balance > 1 && BalanceFactor(node->Left) >= 0) {
				return RightRotate(node);
		}

		// Левый правый случай
    if (balance > 1 && BalanceFactor(node->Left) < 0) {
        node->Left = LeftRotate(node->Left);
        return RightRotate(node);
    }

		// Правый правый случай
    if (balance < -1 && BalanceFactor(node->Right) <= 0)
        return LeftRotate(node);

		// Правый левый случай
    if (balance < -1 && BalanceFactor(node->Right) > 0) {
        node->Right = RightRotate(node->Right);
        return LeftRotate(node);
    }
    return node;
}

void AVLTree::Insert(int key) {
    root = Insert(root, key);
}

void AVLTree::Remove(int key) {
    root = DeleteNode(root, key);
}
```

= Анализ сложности
$N$ --- количество элементов в дереве
== Случаи АВЛ дерева
AVL дерево является идеально балансированным деревом, что означает, что для него всегда выполняется лучший случай.
== Высота узла
Функция возвращает высоту узла в дереве из поля height, что занимает $O(1)$.

== BalanceFactor
Если узел равен null, то возвращается 0. Если узел нет, то вычислит разницу между высотами дерева левого и правого ребенка за $O(1) + O(1) = O(1)$

== Повороты и балансировка
Любой поворот перопределяет указатели и высоты узлов в дереве. Все операции займут $O(1)$. В худшем случае требуется не более двух поворотов для восстановления баланса за $O(1)$ дерева. Временная сложность составит $O(log n)$

== Вставка
- Сначала ищем узел за $O(log N)$, так как дерево идельно балансированное.
- После этого идет балансировка --- $O(O(log N))$.

Общая сложность вставки $O(log N) + O(log N) = O(log N)$

== Удаление
- Сначала ищем узел за $O(log N)$, так как дерево идельно балансированное.
- Удаление узла, занимает от $O(1)$ (если нет детей у узла) до $O(log N)$ (при наличи двух детей), как в бинарном дереве, так как надо заменить на минимальный из его правого поддерва. Поиск минимума займет $O(log N)$
- После этого идет балансировка --- $O(O(log N))$.

== Затраты по памяти
Расход памяти за дерево составляет $O(N)$, тк в максимальное количество элементов в памяти равно количеству узлов в дереве.
