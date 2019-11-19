#include <graph/core/BaseExceptions.hpp>
#include <graph/core/graph.hpp>
#include <gtest/gtest.h>

//--------------------------------------------------
using namespace graph::core;

class graph_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(graph_test, empty)
{
    Graph e(Graph::Element{});
}

TEST_F(graph_test, notempty)
{
    Graph::Element element{};
    element.outgoing.emplace_back(std::make_pair(1, Graph::Element{}));
    Graph e(std::move(element));
}

TEST_F(graph_test, GetBegin)
{
    Graph::Element element{};
    element.outgoing.emplace_back(std::make_pair(1, Graph::Element{}));
    Graph e(std::move(element));
    
    ASSERT_EQ(1, e.GetBegin().outgoing.size());
    ASSERT_EQ(1, e.GetBegin().outgoing.front().first);
}
