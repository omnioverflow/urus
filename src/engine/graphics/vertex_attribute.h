#pragma once

#include <vector>

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

            void setVertexAttribPointer(unsigned int index);

            /**
             * Upload an array of data to GPU. Each element in the array represents
             * one vertex attribute.
             */
            void set(const T* attribs, unsigned int nbAttribs); 
            void set(const std::vector<T>& attribs);
            void bindTo(unsigned int index);
            void unbindFrom(unsigned int index);

            /**
             * Get number of vertex attributes.
             */
            inline unsigned int getCount() const;
            /**
             * Get the handle to the GPU resource associated with the vertex attribute data.
             */
            inline unsigned int getHandle() const;
            
        private:

            unsigned int mHandle;
            unsigned int mCount;
    }; // class VertexAttribute
} // namespace urus
