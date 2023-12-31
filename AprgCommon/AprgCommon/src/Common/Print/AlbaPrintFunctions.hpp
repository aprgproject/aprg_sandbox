#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <optional>
#include <ostream>
#include <string>
#include <tuple>

namespace alba {

// printParameter declaration

void printParameter(std::ostream& outputStream, std::string const& parameter);
void printParameter(std::ostream& outputStream, char const* const parameter);

template <typename ParameterType>
void printParameter(std::ostream& outputStream, ParameterType const& parameter);
template <typename ParameterType>
void printParameter(std::ostream& outputStream, std::optional<ParameterType> const& parameter);
template <typename... UnderlyingTypes>
void printParameter(std::ostream& outputStream, std::pair<UnderlyingTypes...> const& parameter);
template <typename... UnderlyingTypes>
void printParameter(std::ostream& outputStream, std::tuple<UnderlyingTypes...> const& parameter);
template <typename ValueType, size_t SIZE, template <typename, size_t> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEnd<TemplateType<ValueType, SIZE>>(), void> printParameter(
    std::ostream& outputStream, TemplateType<ValueType, SIZE> const& parameter);
template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEndAndSize<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& outputStream, TemplateType<UnderlyingTypes...> const& parameter);
template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEndAndWithoutSize<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& outputStream, TemplateType<UnderlyingTypes...> const& parameter);
template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasContainerType<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& outputStream, TemplateType<UnderlyingTypes...> const& parameter);

// printParameterWithName declaration

template <typename ParameterType>
void printParameterWithName(std::ostream& outputStream, std::string_view parameterName, ParameterType const& parameter);
template <typename ParameterPointerType>
void printParameterWithName(
    std::ostream& outputStream, std::string_view parameterName, ParameterPointerType* parameterPointer);
template <>
void printParameterWithName(std::ostream& outputStream, std::string_view, char const* const parameter);
template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithDereference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(
    std::ostream& outputStream, std::string_view parameterName, TemplateType<UnderlyingTypes...> const& parameter);
template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithoutDereference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(
    std::ostream& outputStream, std::string_view parameterName, TemplateType<UnderlyingTypes...> const& parameter);

// Utilities

template <typename... ValueTypes>
void printTupleParameters(std::ostream& outputStream, std::tuple<ValueTypes...> const& parameter) {
    std::apply  // C++17, applies a function by unpacking a tuple to its tupleParameters
        (
            [&outputStream](ValueTypes const&... tupleParameters) {
                std::size_t tupleIndex{0};
                auto printTupleParameter = [&outputStream](auto&& tupleParameter, auto& tupleIndex) {
                    printParameter(outputStream, tupleParameter);
                    outputStream << (++tupleIndex != sizeof...(ValueTypes) ? ", " : "");
                };
                (printTupleParameter(tupleParameters, tupleIndex), ...);  // Folding expressions in C++17
            },
            parameter);
}

template <typename ContainerType>
void printParametersByForEachTraversal(std::ostream& outputStream, ContainerType const& container) {
    for (auto const& parameter : container) {
        printParameter(outputStream, parameter);
        outputStream << ", ";
    }
}

template <typename Adapter>
typename Adapter::container_type const& getUnderlyingContainerForPrinting(Adapter const& adapter) {
    // copied from parameter to lessen dependencies
    struct AdapterParent : Adapter {
        static typename Adapter::container_type const& get(Adapter const& adapterAsParameter) {
            return adapterAsParameter.*&AdapterParent::c;
        }
    };
    return AdapterParent::get(adapter);
}

// printParameter

template <typename ParameterType>
void printParameter(std::ostream& outputStream, ParameterType const& parameter) {
    outputStream << parameter;
}

template <typename ParameterType>
void printParameter(std::ostream& outputStream, std::optional<ParameterType> const& parameter) {
    if (parameter) {
        outputStream << parameter.value();
    } else {
        outputStream << "empty";
    }
}

template <typename... UnderlyingTypes>
void printParameter(std::ostream& outputStream, std::pair<UnderlyingTypes...> const& parameter) {
    outputStream << "(";
    printParameter(outputStream, parameter.first);
    outputStream << ", ";
    printParameter(outputStream, parameter.second);
    outputStream << ")";
}

template <typename... UnderlyingTypes>
void printParameter(std::ostream& outputStream, std::tuple<UnderlyingTypes...> const& parameter) {
    outputStream << "(";
    printTupleParameters<UnderlyingTypes...>(outputStream, parameter);
    outputStream << ")";
}

template <typename ValueType, size_t SIZE, template <typename, size_t> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEnd<TemplateType<ValueType, SIZE>>(), void> printParameter(
    std::ostream& outputStream, TemplateType<ValueType, SIZE> const& parameter) {
    outputStream << "{Constant size: " << SIZE << " | ";
    printParametersByForEachTraversal(outputStream, parameter);
    outputStream << "}";
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEndAndSize<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& outputStream, TemplateType<UnderlyingTypes...> const& parameter) {
    outputStream << "{size: " << parameter.size() << " | ";
    printParametersByForEachTraversal(outputStream, parameter);
    outputStream << "}";
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasBeginAndEndAndWithoutSize<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& outputStream, TemplateType<UnderlyingTypes...> const& parameter) {
    outputStream << "{";
    printParametersByForEachTraversal(outputStream, parameter);
    outputStream << "}";
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::hasContainerType<TemplateType<UnderlyingTypes...>>(), void> printParameter(
    std::ostream& outputStream, TemplateType<UnderlyingTypes...> const& parameter) {
    outputStream << "{adapter: ";
    printParameter(outputStream, getUnderlyingContainerForPrinting(parameter));
    outputStream << "}";
}

// printParameterWithName

template <typename ParameterType>
void printParameterWithName(
    std::ostream& outputStream, std::string_view parameterName, ParameterType const& parameter) {
    outputStream << parameterName << " : [";
    printParameter(outputStream, parameter);
    outputStream << "]";
}

template <typename ParameterPointerType>
void printParameterWithName(
    std::ostream& outputStream, std::string_view parameterName, ParameterPointerType* parameterPointer) {
    if (parameterPointer == nullptr) {
        outputStream << parameterName << " : [nullptr]";
    } else {
        outputStream << "*" << parameterName << " : [";
        printParameter(outputStream, *parameterPointer);
        outputStream << "]";
    }
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithDereference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(
    std::ostream& outputStream, std::string_view parameterName, TemplateType<UnderlyingTypes...> const& parameter) {
    printParameterWithName(outputStream, parameterName, parameter.get());
}

template <typename... UnderlyingTypes, template <typename...> class TemplateType>
std::enable_if_t<typeHelper::isRaiiPointerWithoutDereference<TemplateType<UnderlyingTypes...>>(), void>
printParameterWithName(
    std::ostream& outputStream, std::string_view parameterName, TemplateType<UnderlyingTypes...> const& parameter) {
    outputStream << parameterName << " has use count: [" << parameter.use_count() << "]";
}

}  // namespace alba
