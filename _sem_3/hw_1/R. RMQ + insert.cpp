#include <iostream>
#include <random>

struct Node {
  int64_t size;
  int64_t prior;
  int64_t val;
  int64_t diff;
  Node* left;
  Node* right;

  Node(int64_t, int64_t);
  void Delete(Node*);
  int64_t Size(Node*);
};

Node::Node(int64_t prior, int64_t val) {
  this->size = 1;
  this->prior = prior;
  this->val = val;
  this->diff = val;
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

int64_t Size(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

class Treap {
  Node* root_;
  std::mt19937 gen_;
  std::uniform_int_distribution<int64_t> distribution_;
  const int64_t k_max_ = 1e9 + 10;

 public:
  Treap();
  bool Empty();
  void Update(Node*);
  void Erase(int64_t);
  void Insert(int64_t, int64_t);
  void SetValue(int64_t, int64_t);
  int64_t TreapSize();
  int64_t Difference(Node*);
  int64_t RMQ(int64_t, int64_t);
  int64_t& operator[](int64_t);
  Node* Merge(Node*, Node*);
  std::pair<Node*, Node*> Find(Node*, Node*, int64_t);
  std::pair<Node*, Node*> Split(Node*, int64_t);
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

void Treap::Erase(int64_t idx) {
  std::pair<Node*, Node*> split_0 = Split(root_, idx);
  Node* left = split_0.first;
  Node* right_idx = split_0.second;
  std::pair<Node*, Node*> split_1 = Split(right_idx, 1);
  Node* idx_tree = split_1.first;
  Node* right = split_1.second;
  root_ = Merge(left, right);
  delete idx_tree;
}

void Treap::Insert(int64_t idx, int64_t val) {
  int64_t prior = distribution_(gen_);
  Node* node = new Node(prior, val);
  std::pair<Node*, Node*> split_0 = Split(root_, idx);
  Node* first = split_0.first;
  Node* second = split_0.second;
  root_ = Merge(Merge(first, node), second);
}

void Treap::SetValue(int64_t idx, int64_t val) {
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

int64_t Treap::TreapSize() {
  return Size(root_);
}

int64_t Treap::Difference(Node* node) {
  if (node == nullptr) {
    return k_max_;
  }
  return node->diff;
}

int64_t Treap::RMQ(int64_t l, int64_t r) {
  std::pair<Node*, Node*> split_0 = Split(root_, l);
  Node* left = split_0.first;
  Node* right_treap = split_0.second;
  std::pair<Node*, Node*> split_1 = Split(right_treap, r - l + 1);
  Node* treap = split_1.first;
  Node* right = split_1.second;
  int64_t min_value = Difference(treap);
  root_ = Merge(left, Merge(treap, right));
  return min_value;
}

int64_t& Treap::operator[](int64_t idx) {
  std::pair<Node*, Node*> find = Find(nullptr, root_, idx);
  Node* idx_node = find.second;
  return idx_node->val;
}

Node* Treap::Merge(Node* first, Node* second) {
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

std::pair<Node*, Node*> Treap::Find(Node* parent, Node* node, int64_t idx) {
  if (node == nullptr) {
    return {parent, node};
  }
  int64_t left_size = Size(node->left);
  if (idx == left_size) {
    return {parent, node};
  }
  if (idx < left_size) {
    return Find(node, node->left, idx);
  }
  return Find(node, node->right, idx - left_size - 1);
}

std::pair<Node*, Node*> Treap::Split(Node* node, int64_t idx) {
  if (node == nullptr) {
    return {nullptr, nullptr};
  }
  int64_t left_size = Size(node->left);
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
  int64_t n = 0;
  int64_t idx = 0;
  int64_t val = 0;
  int64_t l = 0;
  int64_t r = 0;
  char com = ' ';
  Treap treap = Treap();
  std::cin >> n;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> com;
    if (com == '+') {
      std::cin >> idx >> val;
      treap.Insert(idx, val);
    } else if (com == '?') {
      std::cin >> l >> r;
      std::cout << treap.RMQ(l - 1, r - 1) << "\n";
    }
  }
  return 0;
}