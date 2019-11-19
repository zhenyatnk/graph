#pragma once

#include <graph/core/BaseExceptions.hpp>
#include <graph/core/export.hpp>

#include <list>
#include <array>
#include <memory>

namespace graph {
namespace core {
  
class Graph
{
public:
    struct Element
    {
        using weight_t = uint32_t;
       
        std::list<std::pair<weight_t, std::shared_ptr<Element>>> outgoing;
    };
    
    template<std::size_t count> using matrix_t = std::array<std::array<Element::weight_t,count>,count>;
    
public:
    
    template<std::size_t count>
    explicit Graph(const matrix_t<count>& matrix)
    {
        std::array<std::shared_ptr<Element>, count> elements;
        
        for(auto index = 0; index < count; ++index)
            elements[index] = std::make_shared<Element>();
        for(auto iElement = 0; iElement < count; ++iElement)
            for(auto index = 0; index < count; ++index)
                if(!!matrix[iElement][index])
                    elements[iElement]->outgoing.emplace_back(std::make_pair(matrix[iElement][index],elements[index]));
        if(!!count)
            m_begin = elements[0];
    }
    
    explicit Graph(std::shared_ptr<Element> begin)
    :m_begin(std::move(begin))
    {}
    
    std::shared_ptr<Element> GetBegin()
    {
        return m_begin;
    }
    
private:
    std::shared_ptr<Element> m_begin;
};

}
}
