#include <vector>
#include <iostream>
#include <memory>
#include <ncurses.h>

#include "graph.h"

using namespace std;

int main() {
  Graph g(1);
  string command;
  while (cin >> command) {
    if (command == "insert") {
      // insert label status
      string label; bool status;
      cin >> label >> status;
      g.insert(label, status);
    } else if (command == "move") {
      // move A up 0
      string handle; string direction; int index;
      MoveType moveType;
      cin >> handle >> direction >> index;
      if (direction == "up") moveType = MoveType::Up;
      if (direction == "down") moveType = MoveType::Down;
      Move move {moveType, index};
      if (handle == "A") g.traverse(move, g.getA());
      else if (handle == "B") g.traverse(move, g.getB());
    } else if (command == "set") {
      string handle; bool status;
      cin >> handle >> status;
      if (handle == "A") g.getA()->setStatus(status);
      else if (handle == "B") g.getB()->setStatus(status);
    }
    g.print();
    if (g.eval()) {
      cout << "THERE IS A PATH!" << endl;
    } else {
      cout << "there is not a path :(" << endl;
    }
 }
  return 0;
}
