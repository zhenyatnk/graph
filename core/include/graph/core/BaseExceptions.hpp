#pragma once

#include <graph/core/export.hpp>
#include <stdexcept>

namespace graph {
namespace core {
namespace exceptions_base {

class GRAPH_CORE_EXPORT graph_error_base
    :public std::runtime_error
{
public:
    graph_error_base(const std::string &aMessage, const int &aErrorCode)
        :runtime_error(aMessage), m_ErrorCode(aErrorCode)
    {}

    int GetErrorCode() const
    {
        return m_ErrorCode;
    }

private:
    int m_ErrorCode;
};

}
}
}
