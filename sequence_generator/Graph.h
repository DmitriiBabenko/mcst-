#pragma once
#include <vector>
#include <random>
#include <string>
// множество {func}. INIT соответствует корню графа
// ADD/MUL/DIV/SUB - бинарные операции над операндами-вершинами
// COUNT - служебное значение, равное числу операций
enum class Ops {
    INIT,
    ADD,
    MUL,
    DIV,
    SUB,
    COUNT
    };

//pred: op - произвольное значение из Ops
//post: строковое представление операции, "?" для неизвестного значения
const std::string toStr(const Ops & op);

// Представление графа зависимостей G = (V, E) из модели на любом из этапов 1-5.
// Вершина V - это индекс idx в диапозоне [0, size()); хранимые для неё данные:
//  - ops()[idx]    - операция f(v) = func (этап 1)
//  - ways()[idx]   - deg+(v): исходящие рёбра (idx, dst), т.е. куда v идёт как операнд (этап 1)
//  - incWays()[idx]- deg-(v): входящие рёбра (src, idx), т.е. операнды v, в порядке операндов (этап 1)
//  - values()[idx] - значение, найденное Z3-солвером для v (этап 2, опционально: hasValues())
//  - regs()[idx]   - регистр rho(v), на которой отображена v (этап 4, опционально: hasRegs())
//  Порядок вершин 0...size()-1 всегда согласован с топологическим порядком sigma; до этапа 3 порядок совпадает
//  с порядком генерации в buildOps/buildWays, который уже топологический по построению 
class Graph {
public:
    //pred: gen - псевдослучайный генератор детерминированный от seed, size - число вершин |V|
    //post: граф зависимостей F=(V,E), детерминированный от seed, |V|=size
    //строит ops, ways, incWays; values и regs пусты 
    Graph(std::mt19937 & gen, const unsigned size);

    //pred: валидный граф(ops\ways заполнены)
    //post: строковое представление графа в формате DOT(для визуализации через graphviz);
    //  если hasValue()/hasRegs(), в местки вершин добавляются найденное значение и/или номер регистра
    const std::string toDot() const;

    //post: значения values[v], найденные Z3-солвером на этапе 2 для каждой вершины v (пусто, если solve ещё не выполнялся)
    const std::vector<float> & values() const { return _values;}

    //post: true, если для графа уже разрешена система ограничений на этапе 2
    bool hasValues() const { return !_values.empty();}

    //post:true, если вершинам назначены регистры (этап 4)
    bool hasRegs() const { return !_regs.empty();}

    //post: функция f: V -> {func} - операция, проиписанная каждой вершине (этап 1)
    const std::vector<Ops> & ops() const {return _ops;}

    //post: deg+(v) для каждой вершины v - список вершин, где v используются как операнд (исходящие рёбра E)
    const std::vector<std::vector<std::size_t>> & ways() const {return _ways;}

    //post: deg-(v) для каждой вершины v - список её операндов в порядке использования (входящие рёбра E)
    const std::vector<std::vector<std::size_t>> & incWays() const {return _incoming_ways;}

    //post: отображение rho: V -> {0, ..., reg-1}, назначенное этапом 4 (пусто, если ещё не назначено)
    const std::vector<std::size_t> & regs() const { return _regs;}

    //post: |V| - число вершин графа
    const std::size_t size() const;

    //pred: log - флаг вывода
    //post: если log истинен, песатает в stdout для каждой вершины её операцию, входящие/исходящие рёбра
    //      и (если назначены) номер регистра; иначе не делает ничего
    void print(const bool & log) const;

    //pred: ops/ways/incWays согласованы между собой (описывают один и тот же граф G=(V,E));
    //      vlues, если непусты, содержат по одному щначению на вершину; regs аналогично для rho
    //post: граф зависимостей с явно заданными данными на любом этапе конвейера (используется для
    //      передачи результата между этапами 2-5 и при загрузке/объединении графов)
    Graph(const std::vector<Ops> & ops,
        const std::vector<std::vector<std::size_t>> & ways,
        const std::vector<std::vector<std::size_t>> & incWays,
        const std::vector<float> & values,
        const std::vector<std::size_t> & regs);
private:
    std::vector<Ops> _ops;
    std::vector<std::vector<std::size_t>> _ways;
    std::vector<std::vector<std::size_t>> _incoming_ways;
    std::vector<float> _values;
    std::vector<std::size_t> _regs;
};

// pred: graphs - набор графов с уже разрешёнными values (этап 2 выполнен для каждого); regs у всех пусты
// post: один граф G=(V,E), являющийся объединением всех graphs (индексы вершин каждого
//       следующего компонента сдвинуты на суммарный размер предыдущих); используется после этапа 2,
//      чтобы объединить компоненты перед топологической сортировкой (этап 3)
const Graph uniteGraph(const std::vector<Graph> & graphs);

// pred: ways - deg+(v) для каждой вершины v (список исходящих рёбер E)
// post: deg-(v) для каждой вершины v - обращённые рёбра (кто ведёт в v); используется для получения
//      incWays графа (операнда каждой вершиы) по известным ways 
const std::vector<std::vector<std::size_t>> reverseWays(const std::vector<std::vector<std::size_t>> & ways);