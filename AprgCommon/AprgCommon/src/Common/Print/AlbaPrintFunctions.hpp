#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <ostream>
#include <string>
#include <tuple>

namespace alba
{

// printParameter declaration

void printParameter(std::ostream & outputStream, std::string const& parameter);

template <typename ParameterType>
void printParameter(std::ostream & outputStream, ParameterType const& parameter);
template <typename... UnderlyingTypes>
void printParameter(std::ostream & outputStream, std::pair<UnderlyingTypes...> const& parameter);
template <typename... UnderlyingTypes>
void printParameter(std::ostream & outputStream, std::tuple<UnderlyingTypes...> const& parameter);
template <typename ValueType, size_t SIZE, template<typename, size_t> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEnd<TemplateType<ValueType, SIZE>>(), void>
printParameter(std::ostream & outputStream, TemplateType<ValueType, SIZE> const& parameter);
template <typename... UnderlyingTypes, template<typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEnd<TemplateType<UnderlyingTypes...>>(), void>
printParameter(std::ostream & outputStream, TemplateType<UnderlyingTypes...> const& parameter);
template <typename... UnderlyingTypes, template<typename...> class TemplateType>
std::enable_if_t<typeHelper::hasUnderlyingContainer<TemplateType<UnderlyingTypes...>>(), void>
printParameter(std::ostream & outputStream, TemplateType<UnderlyingTypes...> const& parameter);



// printParameterWithName declaration

template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, ParameterType const& parameter);
template <typename ParameterPointerType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, ParameterPointerType * parameterPointer);
template <>
void printParameterWithName(std::ostream & outputStream, std::string const&, char const*const parameter);
template <typename... UnderlyingTypes, template<typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithDeference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(std::ostream & outputStream, std::string const& parameterName, TemplateType<UnderlyingTypes...> const& parameter);
template <typename... UnderlyingTypes, template<typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithoutDeference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(std::ostream & outputStream, std::string const& parameterName, TemplateType<UnderlyingTypes...> const& parameter);



// Utilities

template<unsigned int index, typename... ValueTypes>
typename std::enable_if<index == sizeof...(ValueTypes), void>::type
printTupleParametersRecusively(std::ostream &, std::tuple<ValueTypes...> const&)
{}

template<unsigned int index, typename... ValueTypes>
typename std::enable_if<index != sizeof...(ValueTypes), void>::type
printTupleParametersRecusively(std::ostream & outputStream, std::tuple<ValueTypes...> const& parameter)
{
    printParameter(outputStream, std::get<index>(parameter));
    outputStream << ", ";
    printTupleParametersRecusively<index+1, ValueTypes...>(outputStream, parameter);
}

template <typename Adapter>
typename Adapter::container_type const& getUnderlyingContainerForPrinting(Adapter const& adapter) // copied from parameter to lessen dependencies
{
    struct AdapterParent : Adapter
    {
        static typename Adapter::container_type const& get(Adapter const& adapterAsParameter)
        {
            return adapterAsParameter.*&AdapterParent::c;
        }
    };
    return AdapterParent::get(adapter);
}



// printParameter

template <typename ParameterType>
void printParameter(std::ostream & outputStream, ParameterType const& parameter)
{
    outputStream << parameter;
}

template <typename... UnderlyingTypes>
void printParameter(std::ostream & outputStream, std::pair<UnderlyingTypes...> const& parameter)
{
    outputStream << "(";
    printParameter(outputStream, parameter.first);
    outputStream << ", ";
    printParameter(outputStream, parameter.second);
    outputStream << ")";
}

template <typename... UnderlyingTypes>
void printParameter(std::ostream & outputStream, std::tuple<UnderlyingTypes...> const& parameter)
{
    outputStream << "(";
    printTupleParametersRecusively<0U, UnderlyingTypes...>(outputStream, parameter);
    outputStream << ")";
}

template <typename ValueType, size_t SIZE, template<typename, size_t> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEnd<TemplateType<ValueType, SIZE>>(), void>
printParameter(std::ostream & outputStream, TemplateType<ValueType, SIZE> const& parameter)
{
    outputStream << "{Constant size: " << SIZE << " | ";
    for(auto const& content : parameter)
    {
        printParameter(outputStream, content);
        outputStream << ", ";
    }
    outputStream << "}";
}

template <typename... UnderlyingTypes, template<typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEnd<TemplateType<UnderlyingTypes...>>(), void>
printParameter(std::ostream & outputStream, TemplateType<UnderlyingTypes...> const& parameter)
{
    outputStream << "{size: " << parameter.size() << " | ";
    for(auto const& content : parameter)
    {
        printParameter(outputStream, content);
        outputStream << ", ";
    }
    outputStream << "}";
}

template <typename... UnderlyingTypes, template<typename...> class TemplateType>
std::enable_if_t<typeHelper::hasUnderlyingContainer<TemplateType<UnderlyingTypes...>>(), void>
printParameter(std::ostream & outputStream, TemplateType<UnderlyingTypes...> const& parameter)
{
    outputStream << "{adapter: ";
    printParameter(outputStream, getUnderlyingContainerForPrinting(parameter));
    outputStream << "}";
}



// printParameterWithName

template <typename ParameterType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, ParameterType const& parameter)
{
    outputStream << parameterName << " : [";
    printParameter(outputStream, parameter);
    outputStream<< "]";
}

template <typename ParameterPointerType>
void printParameterWithName(std::ostream & outputStream, std::string const& parameterName, ParameterPointerType * parameterPointer)
{
    if(parameterPointer == nullptr)
    {
        outputStream << parameterName << " : [nullptr]";
    }
    else
    {
        outputStream << "*" << parameterName << " : [";
        printParameter(outputStream, *parameterPointer);
        outputStream<< "]";
    }
}

template <>
void printParameterWithName(std::ostream & outputStream, std::string const& , char const*const parameter);

template <typename... UnderlyingTypes, template<typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithDeference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(std::ostream & outputStream, std::string const& parameterName, TemplateType<UnderlyingTypes...> const& parameter)
{
    printParameterWithName(outputStream, parameterName, parameter.get());
}

template <typename... UnderlyingTypes, template<typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithoutDeference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(std::ostream & outputStream, std::string const& parameterName, TemplateType<UnderlyingTypes...> const& parameter)
{
    outputStream << parameterName << " has use count: [" << parameter.use_count() << "]";
}

}//namespace alba
