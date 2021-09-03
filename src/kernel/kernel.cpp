#include "./interfaces/BasicRenderer/BasicRenderer.h"

extern "C" void kernel_main()
{
    BasicRenderer Renderer = BasicRenderer();
    Renderer.Print(ToString((int64_t)-53));
    
}