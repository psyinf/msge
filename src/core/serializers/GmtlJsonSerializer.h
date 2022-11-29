#pragma once
#include <gmtl/gmtl.h>

#include <nlohmann/json.hpp>

// serializers
namespace gmtl 
{
template<class DATA_TYPE, size_t S>
inline void to_json(nlohmann::json& j, const VecBase<DATA_TYPE, S> & p)
{
    j = nlohmann::json::array({p.mData});
}
template <class DATA_TYPE, size_t S>
inline void from_json(const nlohmann::json& j, VecBase<DATA_TYPE, S>& p)
{
    j.get_to(p.mData);
}


inline void to_json(nlohmann::json& j, const Quatd& q)
{
    j = nlohmann::json::array({q.mData});
}

inline void from_json(const nlohmann::json& j, Quatd& q)
{
    j.get_to(q.mData);
}

}