#pragma once

#include <graph/core/BaseExceptions.hpp>
#include <graph/core/export.hpp>

#include <string>
#include <vector>
#include <array>
#include <memory>

namespace graph {
namespace core {

using weight_t = uint32_t;
using ident_t = uint32_t;
template<std::size_t count> using matrix_t = std::array<std::array<weight_t,count>,count>;

template<typename TData>
class GraphEx
{
public:
    struct Element
    {
        std::vector<std::pair<weight_t, std::weak_ptr<Element>>> inner;
        std::vector<std::pair<weight_t, std::shared_ptr<Element>>> outgoing;
        TData data;
        ident_t ident;
    };
    
public:
    template<std::size_t count>
    explicit GraphEx(const matrix_t<count>& matrix)
    {
        std::array<std::shared_ptr<Element>, count> elements;
        
        for(auto index = 0; index < count; ++index)
        {
            auto element = std::make_shared<Element>();
            element->ident = index;
            elements[index] = element;
        }

        for(auto iElement = 0; iElement < count; ++iElement)
            for(auto index = 0; index < count; ++index)
                if(!!matrix[iElement][index])
                {
                    elements[index]->inner.emplace_back(std::make_pair(matrix[iElement][index],std::weak_ptr<Element>(elements[iElement])));
                    elements[iElement]->outgoing.emplace_back(std::make_pair(matrix[iElement][index],elements[index]));
                }
        if(!!count)
            m_begin = elements[0];
    }
    
    explicit GraphEx(std::shared_ptr<Element> begin)
    :m_begin(std::move(begin))
    {}
    
    std::shared_ptr<Element> GetBegin()
    {
        return m_begin;
    }
    const Element& GetBegin()const
    {
        return *m_begin;
    }
    
private:
    std::shared_ptr<Element> m_begin;
};

using Graph = GraphEx<void*>;

template<typename Type, typename Function>
void for_each(const Type& begin, const Function& caller)
{
    auto isParent = begin.inner.size() == 0;
    if(!isParent)
       caller(begin);
    for(const auto& element: begin.outgoing)
    {
        if(isParent)
           caller(begin);
        for_each(*element.second, caller);
    }

}

template<typename TData>
std::string ToIdentsString(const GraphEx<TData>& graph)
{
    std::string text;
    for_each(graph.GetBegin(), [&text](const typename GraphEx<TData>::Element& element){ text += std::to_string(element.ident);});
    return text;
}

template<std::size_t count>
std::vector<ident_t> GetMinPath(const matrix_t<count>& matrix)
{
    struct Data
    {
        std::shared_ptr<typename GraphEx<Data>::Element> previuos;
        weight_t minWidth;
    };
    
    GraphEx<Data> graph(matrix);
    return {};
}

}
}
