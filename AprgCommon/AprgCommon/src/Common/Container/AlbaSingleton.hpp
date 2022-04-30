#pragma once

namespace alba
{

template <class ObjectType>
class AlbaSingleton
{
public:
    static ObjectType & getInstance();

protected:
    AlbaSingleton() {}

private:
    AlbaSingleton(AlbaSingleton const&) = delete;
    AlbaSingleton & operator = (AlbaSingleton const&) = delete;
};

template <class ObjectType>
ObjectType & AlbaSingleton<ObjectType>::getInstance()
{
    static ObjectType instance;
    return instance;
}

} // namespace alba
