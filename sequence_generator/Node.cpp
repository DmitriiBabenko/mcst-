#include "Node.h"

Node::Node(std::vector<Node*> && inc, std::size_t id, Ops op):
    _inc(std::move(inc)),
    _visited(false),
    _id(id),
    _op(op) {
        for (auto & node : _inc) {
            node->addOut(this);
        }
    }

    void Node::addOut(Node* node) {
        _out.push_back(node);
    }

    const std::vector<Node*>& Node::getOut() const {
        return _out;
    }

    const std::vector<Node*>& Node::getInc() const {
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