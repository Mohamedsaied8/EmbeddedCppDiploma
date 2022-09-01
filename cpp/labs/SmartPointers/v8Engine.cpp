#include "IEngine.h"

class V8Engine : public IEngine
{
    void Start() override { /* start the engine */ }
    void Stop() override { /* stop the engine */ }
};

std::unique_ptr<IEngine> MakeV8Engine()
{
    return std::make_unique<V8Engine>();
}