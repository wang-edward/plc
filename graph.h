#include <memory>
#include "node.h"

enum class MoveType {Up, Down};

struct Move {
  MoveType moveType;
  int index;
};

class Graph {
  std::shared_ptr<Node> head;
  std::shared_ptr<Node> tail;
  std::shared_ptr<Node> currA;
  std::shared_ptr<Node> currB;
  int y;
  bool dfs(std::shared_ptr<Node> current, std::vector<std::shared_ptr<Node>> visited) const;
public:
  Graph(int y);
  ~Graph();
  std::shared_ptr<Node> &getHead();
  std::shared_ptr<Node> &getTail();
  std::shared_ptr<Node> &getA();
  std::shared_ptr<Node> &getB();
  NodeType getType() const;

  void draw();
  void print() const;
  void printHelper(std::string prefix, std::shared_ptr<Node> current) const;
  void insert(std::string label, bool status);
  bool eval() const;
  void traverse(Move m, std::shared_ptr<Node> &current);
};
