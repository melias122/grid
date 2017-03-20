#ifndef SELELIT_H
#define SELELIT_H

#include "Select.h"


class SelectElitism : public Select
{
    public:
    SelectElitism():Select(){};

    SelectElitism(unsigned int subPopCnt):Select(subPopCnt){};
    
    std::vector<Chromosome *> select(std::vector<Chromosome *>& pop);

};

#endif 
