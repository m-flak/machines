#pragma once

#include <functional>
#include <memory>

template<typename Dependency>
class DependencyProvider
{
public:
    DependencyProvider()
        : defaultProvided_(nullptr),
          dep_(DependencyProvider<Dependency>::getProvided())
    { }

    ~DependencyProvider() {}

    Dependency& get() const { return dep_.get(); }
    void set(Dependency& dependency) { dep_ = std::ref(dependency); }

protected:
    //To use with a singleton object, specialize template & declare this method.
    //The specialized method will be declared instead of the below method
    Dependency& getProvided()
    {
        defaultProvided_ = std::make_shared<Dependency>();
        return *defaultProvided_;
    }

private:
    std::shared_ptr<Dependency> defaultProvided_;
    std::reference_wrapper<Dependency> dep_;
};
