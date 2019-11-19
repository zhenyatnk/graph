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
    Graph e(std::make_shared<Graph::Element>());
}

TEST_F(graph_test, notempty)
{
    auto element = std::make_shared<Graph::Element>();
    element->outgoing.emplace_back(std::make_pair(1, std::make_shared<Graph::Element>()));
    Graph e(element);
}

TEST_F(graph_test, GetBegin)
{
    auto element = std::make_shared<Graph::Element>();
    element->outgoing.emplace_back(std::make_pair(1, std::make_shared<Graph::Element>()));
    Graph e(element);
    
    ASSERT_EQ(1, e.GetBegin()->outgoing.size());
    ASSERT_EQ(1, e.GetBegin()->outgoing.front().first);
}

TEST_F(graph_test, matrix)
{
    Graph::matrix_t<2> matrix{{{0,5},
                               {0,0}}};
    Graph e(matrix);
    
    ASSERT_EQ(1, e.GetBegin()->outgoing.size());
    ASSERT_EQ(5, e.GetBegin()->outgoing.front().first);
    ASSERT_EQ(0, e.GetBegin()->outgoing.front().second->outgoing.size());
}

TEST_F(graph_test, matrix_cycle)
{
    Graph::matrix_t<2> matrix{{{0,5},
                               {5,0}}};
    Graph e(matrix);
    
    ASSERT_EQ(1, e.GetBegin()->outgoing.size());
    ASSERT_EQ(5, e.GetBegin()->outgoing.front().first);
    ASSERT_EQ(1, e.GetBegin()->outgoing.front().second->outgoing.size());
    ASSERT_EQ(5, e.GetBegin()->outgoing.front().second->outgoing.front().first);
}
