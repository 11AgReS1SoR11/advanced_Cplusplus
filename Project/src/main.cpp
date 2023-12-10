#include <iostream>
#include "Wrapper.hpp"
#include "Engine.hpp"

/*Example from lecture*/

struct Subject
{
    int f3(int a, int b) { return a + b; }
};

int main()
{
    Subject subj;

    Wrapper<Subject, int, int> wrapper(&subj, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});

    Engine engine;

    engine.register_command("command1", &wrapper);

    std::cout << engine.execute("command1", {{"arg1", 4}, {"arg2", 5}}) << std::endl;

    return 0;
}
