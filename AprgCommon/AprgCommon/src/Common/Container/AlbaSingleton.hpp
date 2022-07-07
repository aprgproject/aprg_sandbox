#pragma once

namespace alba
{

template <class ObjectType>
class AlbaSingleton
{
public:
    static ObjectType & getInstance()
    {
        static ObjectType instance;
        return instance;
    }

protected:
    AlbaSingleton()
    {}

private:
    AlbaSingleton(AlbaSingleton const&) = delete;
    AlbaSingleton & operator= (AlbaSingleton const&) = delete;
};

} // namespace alba
