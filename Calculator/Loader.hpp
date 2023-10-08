#pragma once

#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <unordered_set>
#include <string>
#include <iostream>

class Loader 
{
public:
    Loader() : libraryHandle{nullptr} {}

    ~Loader() 
    {
        if (libraryHandle) 
        {
            dlclose(libraryHandle);
        }
    }

    template <typename FuncType>
    std::function<FuncType> loadFunction(std::string_view libraryPath, std::string_view functionName)
    {
        libraryHandle = dlopen(libraryPath.data(), RTLD_LAZY);
        if (!libraryHandle) 
        {
            const char* error = dlerror();
            throw std::runtime_error("Error loading library: " + std::string(error));
        }

        void* symbol = dlsym(libraryHandle, functionName.data());
        if (!symbol) 
        {
            const char* error = dlerror();
            throw std::runtime_error("Error loading symbol: " + std::string(error));
        }

        return std::function<FuncType>(reinterpret_cast<FuncType*>(symbol));
    }

private:
    void* libraryHandle;
};