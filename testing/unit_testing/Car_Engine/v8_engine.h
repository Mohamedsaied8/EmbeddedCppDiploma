#include "i_engine.h"
#include <memory>

class V8Engine : public IEngine
{
    public:
    void Start() override ;
    void Stop() override ;
    static std::unique_ptr<IEngine> MakeV8Engine();
};

