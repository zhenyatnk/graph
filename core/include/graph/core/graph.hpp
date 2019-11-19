#pragma once

#include <graph/core/BaseExceptions.hpp>
#include <graph/core/export.hpp>

#include <list>

namespace graph {
namespace core {
  
class Graph
{
public:
    struct Element
    {
        using weight_t = uint32_t;
        
        Element(const Element&) = delete;
        Element& operator = (const Element&) = delete;
        
        Element(Element&&) = default;
        
        std::list<std::pair<weight_t, Element>> outgoing;
    };
public:
    explicit Graph(Element&& begin)
    :m_begin(std::move(begin))
    {}
    
    Element& GetBegin()
    {
        return m_begin;
    }
    
private:
    Element m_begin;
};


}
}
