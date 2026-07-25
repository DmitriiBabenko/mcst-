#ifndef NODE_H
#define NODE_H
#include <cstddef>
#include <vector>
#include <string>
enum class Ops {
        ADD,
        SUB,
        MUL,
        DIV,
        INIT,
        COUNT
    };
class Node {
public:
    Node(std::vector<Node*> && inc, std::size_t id, Ops op);
    void addOut(Node* node);
    const std::vector<Node*>& getOut() const;
    const std::vector<Node*>& getInc() const;
    void visit();
    void visit_off();
    bool visited() const;
    const std::size_t getId() const;
    const Ops getOp() const;
    void setValue(float value);
    const float getValue() const;
private:
    std::vector<Node*> _inc;
    std::vector<Node*> _out;
    bool _visited;
    std::size_t _id;
    Ops _op;
    float _value;
};
#endif //NODE_H