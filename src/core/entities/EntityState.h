#pragma once
namespace msge
{
//Idea sketch: have restricted "any" type. Access via get<Type> with implicit conversion  

enum class Type
{
    STRING, INT, FLOAT
};

template <typename T>
class Deduce
{
public:
    Type t;
};

template <typename T, Type = Deduce<T>::type>
class TagTypedData
{
    T data;
    Type type;

    T& operator()()
    {
        return data;
    }

    const T& operator()() const
    {
        return data;
    }
};

class EntityState
{
    //TODO: restrict key type length
    /*properties that cannot change during lifetime*/
    std::map<std::string, std::string> staticProperties;
        /*properties reflecting actual (dynamic) state*/
    std::map<std::string, std::string> dynamicProperties;

};

} // namespace msge
