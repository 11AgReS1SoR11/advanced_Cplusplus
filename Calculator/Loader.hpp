#pragma once

#include <dlfcn.h>
#include <functional>
#include <string>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

class Loader {
public:
    Loader() : handle{nullptr} {}
    ~Loader() 
    {
        if (handle)
            dlclose(handle);
    }

    void* tryLoadFunc(std::string_view libraryPath, std::string_view functionName) 
    {
        handle = dlopen(libraryPath.data(), RTLD_LAZY);
        if (handle) 
        {
            void* symbol = dlsym(handle, functionName.data());
            if (symbol) 
            {
                return symbol;
            }
        }

        return nullptr;
    }

    template <typename FuncType>
    std::function<FuncType> loadFunction(std::string_view functionName) 
    {
        for (const auto& dirEntry : fs::recursive_directory_iterator(fs::current_path())) 
        {
            if (dirEntry.is_regular_file()) 
            {
                if (dirEntry.path().extension() == ".so")
                {
                    auto path = dirEntry.path().string();
                    auto symbol = tryLoadFunc(path, functionName);
                    if (symbol)
                    {
                        return std::function<FuncType>(reinterpret_cast<FuncType*>(symbol));
                    }
                }
            }
        }

        throw std::runtime_error("Error: function '" + std::string(functionName) + "' not found in any loaded librarys.");
    }

private:
    void* handle;
};