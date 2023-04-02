#pragma once

namespace alba
{

template <class ObjectType>
class AlbaSingleton
{
public:

    // rule of five or six
    ~AlbaSingleton() = default;
    AlbaSingleton(AlbaSingleton const&) = delete;
    AlbaSingleton & operator= (AlbaSingleton const&) = delete;
    AlbaSingleton(AlbaSingleton &&) = delete;
    AlbaSingleton & operator= (AlbaSingleton &&) = delete;

    static ObjectType & getInstance()
    {
        static ObjectType instance;
        return instance;
    }

protected:
    AlbaSingleton() = default;
};

} // namespace alba


// To use the singleton, you have to use CRTP (curiously recurring template pattern)
// Example:
// class ClassForSingleton : public AlbaSingleton<ClassForSingleton>
// {
//     // ...
// };