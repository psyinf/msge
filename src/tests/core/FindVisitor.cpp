#include <entities/DynamicCompoundEntity.h>
#include <entities/StaticEntity.h>
#include <gtest/gtest.h>
#include <visitors/FindEntityVisitor.h>

auto makeStaticEntity(std::string_view name)
{
    auto e = std::make_shared<msge::StaticEntity>(name, "s1");
    return e;
}

auto makeGroup(std::string_view name)
{
    return std::make_shared<msge::DynamicCompoundEntity>(name, "t1");
}

auto makeScene1()
{
    auto g = makeGroup("g");

    auto a1 = makeGroup("a1");
    auto a2 = makeGroup("a2");
    auto b1 = makeGroup("b1");
    auto b2 = makeGroup("b2");
    auto b3 = makeGroup("b3");

    g->addChildren(a1, a2);
    b2->addChildren(makeStaticEntity("c1"));

    a1->addChildren(b1, b2);
    a2->addChildren(b3);
    b3->addChildren(makeStaticEntity("c2"));
    b3->addChildren(makeStaticEntity("c3"));
    return g;
}

TEST(FindVisitor, finds)
{
    auto                    g = makeScene1();
    msge::FindEntityVisitor f;
    f.reset("g.a2.b3");
    g->accept(f);

    auto result = f.getResult();

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->get().id, std::string("b3"));


    f.reset("g.a2.b3.c3");
    g->accept(f);
    auto result2 = f.getResult();

    ASSERT_TRUE(result2.has_value());
    ASSERT_EQ(result2->get().id, std::string("c3"));
}

TEST(FindVisitor, notFound)
{
    auto                    g = makeScene1();
    msge::FindEntityVisitor f;
    f.reset("g1.a2.b3");
    g->accept(f);
    auto result = f.getResult();
    ASSERT_FALSE(result.has_value());

    // reset works
    f.reset("g.a2.b3.c3");
    g->accept(f);
    auto result3 = f.getResult();

    ASSERT_TRUE(result3.has_value());
    ASSERT_EQ(result3->get().id, std::string("c3"));

    f.reset("g1.a2.b3.c1");
    g->accept(f);
    auto result2 = f.getResult();

    ASSERT_FALSE(result2.has_value());
    
}

TEST(FindVisitor, empty)
{
    auto                    g = makeScene1();
    msge::FindEntityVisitor f;
    f.reset("");
    g->accept(f);
    auto                    result = f.getResult();
    ASSERT_FALSE(result.has_value());

    f.reset("g.a2.b3.c1");
    std::make_shared<msge::DynamicCompoundEntity>()->accept(f);
    
    auto result2 = f.getResult();
    ASSERT_FALSE(result2.has_value());
}

//TODO untrimmed name