#pragma once

#include <stdexcept>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <cassert>

template<typename ClassType, typename... Args>
class Wrapper
{
public:
    using MethodType = int(ClassType::*)(Args...);

    Wrapper(ClassType* instance_, MethodType method_, const std::initializer_list<std::pair<std::string, int>>& arguments_)
        : instance(instance_), method(method_)
    {
        for(auto const& node : arguments_)
        {
            argNames.push_back(node.first);
        }
    }

    int Invoke(const std::unordered_map<std::string, int>& arguments_)
    {
        std::vector<int> values;
        for (auto const& name : argNames)
        {
            if (arguments_.find(name) == arguments_.end()) 
            {
                throw std::runtime_error("No such argument: " + name);
            }

            values.push_back(arguments_.at(name));
        }
        return Invoke(values, std::make_index_sequence<sizeof...(Args)>());
    }

private:
    ClassType* instance;
    MethodType method;
    std::vector<std::string> argNames;

    template <std::size_t... S>
    int Invoke(const std::vector<int>& vec, std::index_sequence<S...>)
    {
        assert(instance && method);
        return (instance->*method)(vec[S]...);
    }
};
