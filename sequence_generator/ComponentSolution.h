#ifndef COMPONENTSOLUTION_H
#define COMPONENTSOLUTION_H
#include <unordered_map>
#include <string>
#include <memory>
#include "z3++.h"
struct ComponentSolution {
    bool is_satisfiable = false;
    std::unordered_map<std::string, float> variable_values;
    std::unordered_map<std::string, z3::expr> local_vars;

    std::unique_ptr<z3::context> ctx_ptr;
    std::unique_ptr<z3::model> model_ptr;
    std::unique_ptr<z3::solver> solver_ptr;

    ComponentSolution() :
        ctx_ptr(std::make_unique<z3::context>()),
        model_ptr(nullptr),
        solver_ptr(nullptr){}
    void setModel(z3::model && model) {
        model_ptr = std::make_unique<z3::model>(std::move(model));
    }
    void setSolver(z3::solver && solver) {
        solver_ptr = std::make_unique<z3::solver>(std::move(solver));
    }
    z3::solver & getSolver() const {
        return *solver_ptr;
    }
    z3::context & getContext() const {
        return *ctx_ptr;
    }
    z3::model & getModel() const {
        return *model_ptr;
    }
};

#endif //COMPONENTSOLUTION_H