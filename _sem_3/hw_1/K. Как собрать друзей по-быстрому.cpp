#include <iostream>
#include <vector>
#include <string>

struct Node {
  int64_t key = 0;
  int64_t priority = 0;
  int64_t size = 0;
  int64_t result = 0;
  Node* left = nullptr;
  Node* right = nullptr;

  explicit Node(int64_t);
  int64_t Size(Node*);
  int64_t Result(Node*);
  void FixNode(Node*);
};

Node::Node(int64_t key) {
  this->key = key;
  this->result = key;
  this->priority = std::rand();
  this->size = 1;
};

int64_t Size(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

int64_t Result(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->result;
}

void FixNode(Node* node) {
  if (node != nullptr) {
    node->size = Size(node->left) + Size(node->right) + 1;
    node->result = Result(node->left) + Result(node->right) + node->key;
  }
}

class Treap {
  Node* root_ = nullptr;

 public:
  Treap();
  ~Treap();
  explicit Treap(Node*);
  Node* Merge(Node*, Node*);
  std::pair<Node*, Node*> Split(Node*, int64_t);
  Node* Exists(int64_t);
  Node* Delete(Node*, int64_t);
  Node* Kth(Node*, int64_t);
  Node* Insert(int64_t);
  void QueryInsert(int64_t);
  int64_t RSQ(int64_t, int64_t);
};

Node* Treap::Delete(Node* node, int64_t x) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->key < x) {
    node->right = Delete(node->right, x);
    FixNode(node);
    return node;
  }
  if (node->key > x) {
    node->left = Delete(node->left, x);
    FixNode(node);
    return node;
  }
  Node* temp_node = Merge(node->left, node->right);
  delete node;
  return temp_node;
}

Node* Treap::Kth(Node* node, int64_t x) {
  if (node == nullptr || x >= Size(node)) {
    return nullptr;
  }
  int64_t size = Size(node->left);
  if (size < x) {
    return Kth(node->right, x - static_cast<int64_t>(size) - 1);
  }
  if (Size(node->left) > x) {
    return Kth(node->left, x);
  }
  return node;
}

Treap::Treap() {
  root_ = nullptr;
}

Treap::~Treap() {
  while (root_ != nullptr) {
    root_ = Delete(root_, Kth(root_, 0)->key);
  }
}

Treap::Treap(Node* root) {
  root_ = root;
}

Node* Treap::Merge(Node* t1, Node* t2) {
  if (t1 == nullptr) {
    return t2;
  }
  if (t2 == nullptr) {
    return t1;
  }
  if (t2->priority < t1->priority) {
    t2->left = Merge(t1, t2->left);
    FixNode(t2);
    return t2;
  }
  t1->right = Merge(t1->right, t2);
  FixNode(t1);
  return t1;
}

std::pair<Node*, Node*> Treap::Split(Node* t, int64_t x) {
  if (t == nullptr) {
    return {nullptr, nullptr};
  }
  if (t->key < x) {
    std::pair<Node*, Node*> pair = Split(t->right, x);
    t->right = pair.first;
    FixNode(t);
    return {t, pair.second};
  }
  std::pair<Node*, Node*> pair = Split(t->left, x);
  t->left = pair.second;
  FixNode(t);
  return {pair.first, t};
}

Node* Treap::Exists(int64_t x) {
  if (root_ == nullptr) {
    return nullptr;
  }
  Node* node = root_;
  while (node != nullptr) {
    if (x == node->key) {
      return node;
    }
    if (x > node->key) {
      node = node->right;
    } else {
      node = node->left;
    }
  }
  return nullptr;
}

Node* Treap::Insert(int64_t x) {
  Node* node = new Node(x);
  if (root_ == nullptr) {
    return node;
  }
  std::pair<Node*, Node*> pair = Split(root_, node->key);
  return Merge(Merge(pair.first, node), pair.second);
}

void Treap::QueryInsert(int64_t x) {
  if (Exists(x) == nullptr) {
    root_ = Insert(x);
  }
}

int64_t Treap::RSQ(int64_t l, int64_t r) {
  std::pair<Node*, Node*> pair0 = Split(root_, l);
  std::pair<Node*, Node*> pair1 = Split(pair0.second, r);
  int64_t res = Result(pair1.first);
  root_ = Merge(Merge(pair0.first, pair1.first), pair1.second);
  return res;
}

int main() {
  int64_t n = 0;
  int64_t x = 0;
  int64_t l = 0;
  int64_t r = 0;
  std::cin >> n;
  char com = ' ';
  Treap treap = Treap();
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> com;
    if (com == '+') {
      std::cin >> x;
      treap.QueryInsert(x);
    } else if (com == '?') {
      std::cin >> l >> r;
      std::cout << treap.RSQ(l, r + 1) << '\n';
    }
  }
  treap.~Treap();
  return 0;
}