#pragma once

#include <scenes/BaseScene.h>
#include <entities/StaticEntity.h>
#include <math/Spatial.h>
#include <memory>
#include <string>
#include "entities.h"

auto makeMover(std::string_view name, common::math::Dynamic&& s)
{
    auto e     = std::make_shared<Mover>(name, "cone");
    e->spatial = std::move(s);
    return e;
}
auto makeCompoundMover(std::string_view name, common::math::Dynamic&& s)
{
    auto e     = std::make_shared<CompoundMover>(name, "cone");
    e->spatial = std::move(s);
    return e;
}

auto makeStaticEntity(std::string_view name, std::string_view type, const common::math::Spatial& s)
{
    auto e     = std::make_shared<msge::StaticEntity>(name, type);
    e->spatial = s;
    return e;
}

auto makeGroup(std::string_view name, std::string_view type)
{
    return std::make_shared<msge::DynamicCompoundEntity>(name, type);
}
void setupScene(msge::BaseScene& scene)
{
    const auto cube = "cube";
    // static entities as scene markers
    scene.addEntity(makeStaticEntity("a111", cube, common::math::Spatial{gmtl::Point3d{-10, -10, -10}}));
    scene.addEntity(makeStaticEntity("a110", cube, common::math::Spatial{gmtl::Point3d{-10, -10, 10}}));
    scene.addEntity(makeStaticEntity("a101", cube, common::math::Spatial{gmtl::Point3d{-10, 10, -10}}));
    scene.addEntity(makeStaticEntity("a100", cube, common::math::Spatial{gmtl::Point3d{-10, 10, 10}}));
    scene.addEntity(makeStaticEntity("a011", cube, common::math::Spatial{gmtl::Point3d{10, -10, -10}}));
    scene.addEntity(makeStaticEntity("a010", cube, common::math::Spatial{gmtl::Point3d{10, -10, 10}}));
    scene.addEntity(makeStaticEntity("a001", cube, common::math::Spatial{gmtl::Point3d{10, 10, -10}}));
    scene.addEntity(makeStaticEntity("a000", cube, common::math::Spatial{gmtl::Point3d{10, 10, 10}}));

    auto g               = makeGroup("g1", "");
    auto g2              = makeGroup("g2", "");
    g->spatial.position  = {0, -1, 0};
    g2->spatial.position = {0, 3, 0};
    scene.addEntity(g);
    g->addChildren(g2);
    g->addChildren(makeStaticEntity("sge1", "sphere", common::math::Spatial{}));
    g2->addChildren(makeStaticEntity("sge2", "sphere", common::math::Spatial{}));
    g2->addChildren(makeMover("m1", common::math::Dynamic{.velocity{0, 0, 1}}));
    auto m2 = makeCompoundMover("m2", common::math::Dynamic{.velocity{0, 0, -1}});
    m2->addChildren(makeStaticEntity("p1", cube, common::math::Spatial{gmtl::Point3d{-0.75, -0.75, -1}}));
    m2->addChildren(makeStaticEntity("p2", cube, common::math::Spatial{gmtl::Point3d{0.75, -0.75, -1}}));
    m2->addChildren(makeStaticEntity("p3", cube, common::math::Spatial{gmtl::Point3d{-0.75, 0.75, -1}}));
    m2->addChildren(makeStaticEntity("p4", cube, common::math::Spatial{gmtl::Point3d{0.75, 0.75, -1}}));

    g2->addChildren(m2);


}
