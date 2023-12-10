#pragma once

#include "Wrapper.hpp"

class Engine 
{
public:
    using MethodType = std::function<int(const std::unordered_map<std::string, int>&)>;

    template<typename ClassType, typename... Args>
    void register_command(const std::string& command_, Wrapper<ClassType, Args...>* wrapper) 
    {
        if (!wrapper)
        {
            throw std::runtime_error("Given nullptr instead wrapper");
        }

        commands[command_] = [wrapper](const std::unordered_map<std::string, int>& arguments_) 
        {
            return wrapper->Invoke(arguments_);
        };
    }

    int execute(const std::string& command_, const std::unordered_map<std::string, int>& arguments_) const
    {
        auto it = commands.find(command_);
        if (it != commands.end())
        {
            return it->second(arguments_);
        } 
        else 
        {
            throw std::runtime_error("No such command: " + command_);
        }
    }

private:
    std::unordered_map<std::string, MethodType> commands;
};

