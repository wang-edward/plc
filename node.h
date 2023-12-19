#pragma once

#include <memory> 
#include <vector> 
#include <iostream> 

enum class NodeType {Head, Contact, Tail};

class Node {
  NodeType type;
  bool status = false;
  std::string label;
  std::vector<std::shared_ptr<Node>> parents;
  std::vector<std::shared_ptr<Node>> children;

  void printHelper(std::string p, bool isLeft) const;
  void destroyHelper(Node *n);
public:
  Node();
  Node(NodeType type, std::string label = "", bool status = false);
  Node(const Node &other);
  Node &operator=(const Node &other);
  Node(Node &&other);
  Node &operator=(Node &&other);
  ~Node();

  NodeType getType() const;
  bool getStatus() const;
  void setStatus(bool newStatus);
  std::string getLabel() const;
  void print() const;
  std::vector<std::shared_ptr<Node>> &getParents();
  std::vector<std::shared_ptr<Node>> &getChildren();
};
