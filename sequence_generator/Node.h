#ifndef NODE_H
#define NODE_H
#include <cstddef>
#include <vector>
class Node {
public:
    Node(std::vector<Node*> && inc, std::size_t id);
    void addOut(Node* node);
    const std::vector<Node*>& getOut() const;
    const std::vector<Node*>& getInc() const;
    void visit();
    void visit_off();
    bool visited() const;
    const std::size_t getId() const;
private:
    std::vector<Node*> _inc;
    std::vector<Node*> _out;
    bool _visited;
    std::size_t _id;
};
#endif //NODE_H