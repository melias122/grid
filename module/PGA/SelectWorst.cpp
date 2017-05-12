#include "SelectWorst.h"

struct worstScore {
    inline bool operator()(const Chromosome &c1, const Chromosome &c2) const
    {
        return c1.score() < c2.score();
    }
};

Population SelectWorst::select(Population p)
{
    std::sort(std::begin(p), std::end(p), worstScore());
    p.resize(std::min<int>(p.size(), m_subpopulationSize));
    return p;
}
