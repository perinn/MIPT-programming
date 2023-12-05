#include <iostream>
#include <random>

struct Node {
  int32_t size;
  int32_t prior;
  int32_t val;
  int32_t diff;
  bool rev;
  Node* left;
  Node* right;

  Node(int32_t, int32_t);
  void Delete(Node*);
  int32_t Size(Node*);
};

Node::Node(int32_t prior, int32_t val) {
  this->size = 1;
  this->prior = prior;
  this->val = val;
  this->diff = val;
  this->rev = false;
  this->left = nullptr;
  this->right = nullptr;
}

void Delete(Node* node) {
  if (node == nullptr) {
    return;
  }
  Delete(node->left);
  Delete(node->right);
  delete node;
}

int32_t Size(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

class Treap {
  Node* root_;
  std::mt19937 gen_;
  std::uniform_int_distribution<int32_t> distribution_;
  const int32_t k_max_ = 1e9 + 10;

 public:
  Treap();
  bool Empty();
  void Update(Node*);
  void Erase(int32_t);
  void Insert(int32_t, int32_t);
  void SetValue(int32_t, int32_t);
  void Reverse(int32_t, int32_t);
  void Push(Node*);
  void GoToBegin(int32_t, int32_t);
  int32_t TreapSize();
  int32_t Difference(Node*);
  int32_t RMQ(int32_t, int32_t);
  int32_t& operator[](int32_t);
  Node* Merge(Node*, Node*);
  std::pair<Node*, Node*> Find(Node*, Node*, int32_t);
  std::pair<Node*, Node*> Split(Node*, int32_t);
  ~Treap();
};

Treap::Treap() {
  root_ = nullptr;
}

bool Treap::Empty() {
  return Size(root_) == 0;
}

void Treap::Update(Node* node) {
  if (node == nullptr) {
    return;
  }
  node->diff = std::min(Difference(node->left), std::min(Difference(node->right), node->val));
  node->size = 1 + Size(node->left) + Size(node->right);
}

void Treap::Erase(int32_t idx) {
  std::pair<Node*, Node*> split_0 = Split(root_, idx);
  Node* left = split_0.first;
  Node* right_idx = split_0.second;
  std::pair<Node*, Node*> split_1 = Split(right_idx, 1);
  Node* idx_tree = split_1.first;
  Node* right = split_1.second;
  root_ = Merge(left, right);
  delete idx_tree;
}

void Treap::Insert(int32_t idx, int32_t val) {
  int32_t prior = distribution_(gen_);
  Node* node = new Node(prior, val);
  std::pair<Node*, Node*> split_0 = Split(root_, idx);
  Node* first = split_0.first;
  Node* second = split_0.second;
  root_ = Merge(Merge(first, node), second);
}

void Treap::SetValue(int32_t idx, int32_t val) {
  std::pair<Node*, Node*> split_0 = Split(root_, idx);
  Node* left = split_0.first;
  Node* right_idx = split_0.second;
  std::pair<Node*, Node*> split_1 = Split(right_idx, 1);
  Node* idx_tree = split_1.first;
  Node* right = split_1.second;
  idx_tree->val = val;
  idx_tree->diff = val;
  root_ = Merge(left, Merge(idx_tree, right));
}

void Treap::Reverse(int32_t l, int32_t r) {
  std::pair<Node*, Node*> split_0 = Split(root_, l);
  Node* left = split_0.first;
  Node* right_treap = split_0.second;
  std::pair<Node*, Node*> split_1 = Split(right_treap, r - l + 1);
  Node* treap = split_1.first;
  Node* right = split_1.second;
  treap->rev = treap->rev ^ true;
  root_ = Merge(left, Merge(treap, right));
}

void Treap::Push(Node* node) {
  if (node == nullptr) {
    return;
  }
  if (!node->rev) {
    return;
  }
  if (node->left != nullptr) {
    node->left->rev = node->left->rev ^ true;
  }
  if (node->right != nullptr) {
    node->right->rev = node->right->rev ^ true;
  }
  std::swap(node->left, node->right);
  node->rev = false;
}

void Treap::GoToBegin(int32_t l, int32_t r) {
  std::pair<Node*, Node*> split_0 = Split(root_, r + 1);
  Node* current = split_0.first;
  Node* last = split_0.second;
  std::pair<Node*, Node*> split_1 = Split(current, l);
  Node* second = split_1.first;
  Node* first = split_1.second;
  root_ = Merge(Merge(first, second), last);
}

int32_t Treap::TreapSize() {
  return Size(root_);
}

int32_t Treap::Difference(Node* node) {
  if (node == nullptr) {
    return k_max_;
  }
  return node->diff;
}

int32_t Treap::RMQ(int32_t l, int32_t r) {
  std::pair<Node*, Node*> split_0 = Split(root_, l);
  Node* left = split_0.first;
  Node* right_treap = split_0.second;
  std::pair<Node*, Node*> split_1 = Split(right_treap, r - l + 1);
  Node* treap = split_1.first;
  Node* right = split_1.second;
  int32_t min_value = Difference(treap);
  root_ = Merge(left, Merge(treap, right));
  return min_value;
}

int32_t& Treap::operator[](int32_t idx) {
  std::pair<Node*, Node*> find = Find(nullptr, root_, idx);
  Node* idx_node = find.second;
  return idx_node->val;
}

Node* Treap::Merge(Node* first, Node* second) {
  Push(first);
  Push(second);
  if (first == nullptr) {
    return second;
  }
  if (second == nullptr) {
    return first;
  }
  if (first->prior > second->prior) {
    first->right = Merge(first->right, second);
    Update(first->right);
    Update(first);
    return first;
  }
  second->left = Merge(first, second->left);
  Update(first->left);
  Update(second);
  return second;
}

std::pair<Node*, Node*> Treap::Find(Node* parent, Node* node, int32_t idx) {
  if (node == nullptr) {
    return {parent, node};
  }
  int32_t left_size = Size(node->left);
  if (idx == left_size) {
    return {parent, node};
  }
  if (idx < left_size) {
    return Find(node, node->left, idx);
  }
  return Find(node, node->right, idx - left_size - 1);
}

std::pair<Node*, Node*> Treap::Split(Node* node, int32_t idx) {
  Push(node);
  if (node == nullptr) {
    return {nullptr, nullptr};
  }
  int32_t left_size = Size(node->left);
  if (idx <= left_size) {
    std::pair<Node*, Node*> split_0 = Split(node->left, idx);
    Node* left = split_0.first;
    Node* right = split_0.second;
    node->left = right;
    Update(right);
    Update(node);
    return {left, node};
  }
  std::pair<Node*, Node*> split_1 = Split(node->right, idx - left_size - 1);
  Node* left = split_1.first;
  Node* right = split_1.second;
  node->right = left;
  Update(left);
  Update(node);
  return {node, right};
}

Treap::~Treap() {
  Delete(root_);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  int32_t m = 0;
  int32_t l = 0;
  int32_t r = 0;
  std::cin >> n >> m;
  Treap treap = Treap();
  for (int32_t i = 0; i < n; ++i) {
    treap.Insert(i, i + 1);
  }
  for (int32_t i = 0; i < m; ++i) {
    std::cin >> l >> r;
    treap.GoToBegin(l - 1, r - 1);
  }
  for (int32_t i = 0; i < n; ++i) {
    std::cout << treap[i] << ' ';
  }
  return 0;
}