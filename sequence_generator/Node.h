#ifndef NODE_H
#define NODE_H
#include <cstddef>
#include <vector>
#include <string>
#include <memory>
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
    Node(std::size_t id, std::size_t component_id, Ops op);
    void addOut(std::shared_ptr<Node> node);
    void addInc(std::shared_ptr<Node> node);
    const std::vector<std::shared_ptr<Node>>& getOut() const;
    const std::vector<std::shared_ptr<Node>>& getInc() const;
    void visit();
    void visit_off();
    bool visited() const;
    const std::size_t getId() const;
    const Ops getOp() const;
    void setValue(float value);
    const float getValue() const;
    const std::string getName() const;
private:
    std::vector<std::shared_ptr<Node>> _out;
    std::vector<std::shared_ptr<Node>> _inc;
    bool _visited;
    std::size_t _id;
    Ops _op;
    float _value;
    std::string _name;
};
#endif //NODE_H