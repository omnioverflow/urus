#pragma once

namespace urus
{
    class Scene;

    /**
    * Abstract renderer.
    */
    class Renderer
    {
    public:
        virtual void draw(const Scene& scene) = 0;
    }; // class Renderer
} // namespace urus