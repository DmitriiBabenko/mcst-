#ifndef GENERATE_COMPONENT_H
#define GENERATE_COMPONENT_H
#include <vector>
#include "Instruction.h" 
class AbstractOp {
public:
    AbstractOp(Ops kind, std::size_t id, std::size_t src1, std::size_t src2): 
        _kind(kind),
        _local_id(id),
        _src1(src1),
        _src2(src2){}
    const Ops operation() const {
        return _kind;
    }
    const char* kind() const {
        switch (_kind) {
            case Ops::ADD:
                return "ADD";
            case Ops::DIV:
                return "DIV";
            case Ops::INIT:
                return "INIT";
            case Ops::SUB:
                return "SUB";
            case Ops::MUL:
                return "MUL";
            default:
                return "?";
        }
    }
    std::size_t id() const {
        return _local_id;
    }
    std::size_t fst_source() const {
        return _src1;
    }
    std::size_t snd_source() const {
        return _src2;
    }
private:
    Ops _kind;
    std::size_t _local_id;
    std::size_t _src1;
    std::size_t _src2;
};
std::vector<std::vector<AbstractOp>> gen_component(const unsigned size, const unsigned seed, const unsigned comps);
#endif //GENERATE_COMPONENT_H