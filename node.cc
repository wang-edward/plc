#include "node.h" 

using namespace std;

Node:: Node() {}

Node:: Node(NodeType type, string label, bool status): type{type}, label{label}, status{status} {}

Node:: Node(const Node &other): type{other.type}, status{other.status}, label{other.label} {
  for (const auto &child : other.children) {
    children.push_back(child);
  }
  for (const auto &parent : other.parents) {
    children.push_back(parent);
  }
}

Node &Node:: operator=(const Node &other) {
  Node temp{other};
  std::swap(this->status, temp.status);
  std::swap(this->children, temp.children);
  std::swap(this->parents, temp.parents);
  return *this;
}

Node:: Node(Node &&other): type{other.type}, status{other.status}, label{other.label} {
  parents = std::move(other.parents);
  children = std::move(other.children);
}

Node &Node:: operator=(Node &&other) {
  Node temp{std::move(other)};
  std::swap(this->status, temp.status);
  std::swap(this->children, temp.children);
  std::swap(this->parents, temp.parents);
  return *this;
}

NodeType Node:: getType() const {
  return type;
}

bool Node:: getStatus() const {
  return status;
}

void Node:: setStatus(bool newStatus) {
  status = newStatus;
}

string Node:: getLabel() const {
  return label;
}

void Node:: print() const {
  // if (status == true) {
  //   cout << "[X] " << label << endl;
  // } else {
  //   cout << "[ ] " << label << endl;
  // }
  // for (auto p : children) {
  //   p->print();
  // }
  printHelper("", false);
}

void Node:: printHelper(string prefix, bool isLeft) const {
  cout << prefix;

  if (isLeft) {
    cout << "├──";
  } else {
    cout << "└──";
  }

  if (getStatus() == true) {
    cout << "\033[1;32m"; // green
    cout << "[X]" << label << endl;
  } else {
    cout << "\033[1;31m"; // red
    cout << "[ ]" << label << endl;
  }


  // for (const auto &n : children) {
  for (int i = 0; i < children.size(); i++) {
    if (children[i] == nullptr) {
      continue;
    }
    // reset color
    if (i == 0 && children.size() != 1) {
      children[i]->printHelper(prefix + (isLeft ? "|   " : "    "), true);
    } else {
      children[i]->printHelper(prefix + (isLeft ? "|   " : "    "), false);
    }
    // for (auto x : children[i]->getChildren()) {
    //   x->print();
    // }
  }
  cout << "\033[0m";
}

void Node:: destroyHelper(Node *n) {
  if (n == nullptr) {
    return;
  }
}

Node:: ~Node() {
  destroyHelper(this);
}

vector<shared_ptr<Node>> &Node:: getParents() {
  return parents;
}

vector<shared_ptr<Node>> &Node:: getChildren() {
  return children;
}
