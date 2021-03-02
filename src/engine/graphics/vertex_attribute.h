#pragma once

#include <vector>

#include "engine/base/opengl_support.h"

namespace urus
{
    template <typename T>
    class VertexAttribute
    {
        public:

            VertexAttribute();
            ~VertexAttribute();
            VertexAttribute(const VertexAttribute& other) = delete;
            VertexAttribute& operator= (const VertexAttribute& other) = delete;

            void setVertexAttribPointer(GLuint index);

            /**
             * Upload an array of data to GPU. Each element in the array represents
             * one vertex attribute.
             */
            void set(const T* attribs, size_t attribCount); 
            void set(const std::vector<T>& attribs);
            void bindTo(GLuint index);
            void unbindFrom(GLuint index);

            /**
             * Get number of vertex attributes.
             */
            inline size_t getCount() const;
            /**
             * Get the handle to the GPU resource associated with the vertex attribute data.
             */
            inline GLuint getHandle() const;
            
        private:

            GLuint mHandle;
            size_t mCount;
    }; // class VertexAttribute
} // namespace urus
