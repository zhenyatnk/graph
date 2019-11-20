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
    matrix_t<2> matrix{{
        {0,5},
        {0,0}
    }};
    Graph e(matrix);
    
    ASSERT_EQ(1, e.GetBegin()->outgoing.size());
    ASSERT_EQ(5, e.GetBegin()->outgoing.front().first);
    ASSERT_EQ(0, e.GetBegin()->outgoing.front().second->outgoing.size());
}

TEST_F(graph_test, matrix_cycle)
{
    matrix_t<2> matrix{{
        {0,5},
        {5,0}
    }};
    Graph e(matrix);
    
    ASSERT_EQ(1, e.GetBegin()->outgoing.size());
    ASSERT_EQ(5, e.GetBegin()->outgoing.front().first);
    ASSERT_EQ(1, e.GetBegin()->outgoing.front().second->outgoing.size());
    ASSERT_EQ(5, e.GetBegin()->outgoing.front().second->outgoing.front().first);
}

TEST_F(graph_test, matrix_real)
{
    matrix_t<3> matrix {{
        {0,2,3},
        {0,0,4},
        {0,0,0}
    }};
    Graph e(matrix);
    
    ASSERT_EQ(0, e.GetBegin()->ident);
    ASSERT_EQ(0, e.GetBegin()->inner.size());
    ASSERT_EQ(2, e.GetBegin()->outgoing.size());
    
    ASSERT_EQ(1, e.GetBegin()->outgoing[0].second->ident);
    ASSERT_EQ(1, e.GetBegin()->outgoing[0].second->inner.size());
    ASSERT_EQ(1, e.GetBegin()->outgoing[0].second->outgoing.size());

    ASSERT_EQ(2, e.GetBegin()->outgoing[1].second->ident);
    ASSERT_EQ(2, e.GetBegin()->outgoing[1].second->inner.size());
    ASSERT_EQ(0, e.GetBegin()->outgoing[1].second->outgoing.size());
}
/*
TEST_F(graph_test, to_string_1)
{
    matrix_t<3> matrix {{
        {0,2,3},
        {0,0,4},
        {0,0,0}
    }};
    Graph e(matrix);
    
    auto text = ToIdentsString(e);

    ASSERT_STREQ("", text.c_str());
}

TEST_F(graph_test, to_string_2)
{
    matrix_t<4> matrix {{
        {0,1,3,0},
        {0,0,1,5},
        {0,0,0,3},
        {0,0,0,0}
    }};
    Graph e(matrix);
    
    auto text = ToIdentsString(e);

    ASSERT_STREQ("", text.c_str());
}*/

class dijkstra_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(dijkstra_test, empty)
{
    auto path = GetMinPath(matrix_t<0>{});
    ASSERT_EQ(0, path.size());
}
/*
TEST_F(dijkstra_test, one)
{
    auto path = GetMinPath(matrix_t<1>{{{1}}});
    ASSERT_EQ(1, path.size());
}

TEST_F(dijkstra_test, simple)
{
    matrix_t<4> matrix {{
        {0,1,3,0},
        {0,0,1,5},
        {0,0,0,3},
        {0,0,0,0}
    }};
    auto path = GetMinPath(matrix);
    ASSERT_EQ(4, path.size());
}*/ 
