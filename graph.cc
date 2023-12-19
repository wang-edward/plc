#include <vector>
#include <algorithm>
#include "graph.h"

using namespace std;
// Graph:: Graph(int y): y{y}, head{new Head}, tail{new Tail}{}
Graph:: Graph(int y)
  : y{y}, head{make_shared<Node>(NodeType::Head, "HEAD", true)}, tail{make_shared<Node>(NodeType::Tail, "TAIL", true)}, 
  currA{head}, currB{tail}
{}

Graph:: ~Graph() {}

void Graph:: traverse(Move m, shared_ptr<Node> &current) {
  if (m.moveType == MoveType::Up) {
    // if (current->getParents().size() < m.index &&
    //     m.index >= 0) {
      current = current->getParents().at(m.index);
    // } else {
    // //   throw runtime_error{"invalid index: choose between 0 -> " + to_string(current->getParents().size())};
    // }
  } else {
    // if (current->getChildren().size() < m.index &&
    //     m.index >= 0) {
      current = current->getChildren().at(m.index);
    // } else {
    //   throw runtime_error{"invalid index: choose between 0 -> " + to_string(current->getParents().size())};
    // }
  }
}

// insert a node between A and B
void Graph:: insert(string label, bool status) {
  auto tmp = make_shared<Node>(NodeType::Contact, label, status);
  // link into chain
  tmp->getParents().push_back(currA);
  tmp->getChildren().push_back(currB);
  // add object onto chain
  currA->getChildren().push_back(tmp);
  currB->getParents().push_back(tmp);
  // erase old links
  auto itA = find(currA->getChildren().begin(), currA->getChildren().end(), currB);
  if (itA != currA->getChildren().end()) {
    currA->getChildren().erase(itA);
  }
  auto itB = find(currB->getParents().begin(), currB->getParents().end(), currA);
  if (itB != currB->getParents().end()) {
    currB->getParents().erase(itB);
  }
}

void Graph:: print() const {
  head->print();
}

void Graph:: printHelper(string prefix, shared_ptr<Node> current) const {
  cout << prefix;

  cout << "└──";

  if (current.get() == currA.get()) {
    cout << "\033[1;32m"; // green
  } else if (current.get() == currB.get()) {
    cout << "\033[1;31m"; // red
  }

  if (current->getStatus() == true) {
    cout << "[X] ";
  } else {
    cout << "[ ] ";
  }

  cout << current->getLabel() << endl;

  // reset colors
  cout << "\033[0m";

  for (int i = 0; i < current->getChildren().size(); i++) {
    if (current->getChildren().at(i) == nullptr) {
      continue;
    }
    // recurse
    printHelper(prefix + "    ", current->getChildren().at(i));
  }
}

bool Graph:: eval() const {
  shared_ptr<Node> current = tail;
  vector<shared_ptr<Node>> visited;
  return dfs(current, visited);
}

bool Graph:: dfs(shared_ptr<Node> current, vector<shared_ptr<Node>> visited) const {
  if (current->getType() == NodeType::Head) {
    return true;
  }
  if (current->getStatus() == false || find(visited.begin(), visited.end(), current) != visited.end()) {
    return false;
  }
  bool ans = false;
  visited.push_back(current);
  for (auto p : current->getParents()) {
    ans = ans || dfs(p, visited);
  }
  return ans;
}

std::shared_ptr<Node> &Graph:: getHead() {
  return head;
}

std::shared_ptr<Node> &Graph:: getTail() {
  return tail;
}

std::shared_ptr<Node> &Graph:: getA() {
  return currA;
}

std::shared_ptr<Node> &Graph:: getB() {
  return currB;
}
