#pragma once
#include <entities/DynamicCompoundEntity.h>
#include <serializers/SpatialJsonSerializer.h>
namespace msge
{

//IDEA:
/**
 * Entities based on the BaseEntity hierarchy are organized in a scene.
 * Based on their class type and entity-type the scene can derive the set of SimulationEntities which are the elements that are processed by a simulation. 
 * The simulation uses the Task/Scheduler interface to do so. 
 * 
 * Scene
 ** loaded from disk 
 ** traverse by visitor initially to build a set of simulationEntities
 *** for each entity consult a factory that delivers "tasks" based on the entity class type and "type" (and maybe consider the id, too)
 *** the factory/registry 
 ** the scene has callbacks for CRUD operations
 *** tasks can be added/removed etc based on changes in the scene and tasks can change the scene
 ** how to delegate serialization or serialize the aspects from the simulation entities?
 * The base entity hierarchy represents the spatial and properties state 
 ** Spatial is covered by BaseEntityVisitor
 ** Properties should be represented by say "EntityState"
 *** We need a another visitor to cover specialized properties in terms of serialization
 */

/**
 * 
 TODO:

load BaseEntity serialization
based on type create XYZEntity A
add A to scene
visit scene and derive SimulationEntities
 */


class SimulationEntity 
{
public:
    
    virtual void frame(const msge::FrameStamp& fs) = 0;
    

    std::shared_ptr<DynamicCompoundEntity> compoundEntity;
    
};

} // namespace msge