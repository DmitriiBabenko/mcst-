#include "Node.h"

Node::Node(std::size_t id, std::size_t component_id, Ops op):
    _visited(false),
    _id(id),
    _op(op) {
        _name = std::to_string(component_id) + '_' + std::to_string(id);
    }

    void Node::addOut(std::shared_ptr<Node> node) {
        _out.push_back(node);
    }

    void Node::addInc(std::shared_ptr<Node> node) {
        _inc.push_back(node);
    }

    const std::vector<std::shared_ptr<Node>>& Node::getOut() const {
        return _out;
    }

    const std::vector<std::shared_ptr<Node>>& Node::getInc() const {
        return _inc;
    }

    void Node::visit() {
        _visited = true;
    }

    void Node::visit_off() {
        _visited = false;
    }

    bool Node::visited() const {
        return _visited;
    }

    const std::size_t Node::getId() const {
        return _id;
    }

    const Ops Node::getOp() const {
        return _op;
    }

    void Node::setValue(float value) {
        _value = value;
    }

    const float Node::getValue() const {
        return _value;
    }

    const std::string Node::getName() const {
        return _name;
    }