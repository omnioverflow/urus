#pragma once

#include <vector>

namespace urus
{
    template <typename T>
    class Attribute
    {
        public:

            Attribute();
            ~Attribute();
            Attribute(const Attribute& other) = delete;
            Attribute& operator= (const Attribute& other) = delete;

         
            void setAttributePointer(unsigned int index);

            /**
             * Upload an array of data to GPU. Each element in the array represents
             * the attribute for one vertex.
             */
            void set(const T* attribs, unsigned int nbAttribs); 
            void set(const std::vector<T>& attribs);
            void bindTo(unsigned int index);
            void unbindFrom(unsigned int index);

            /**
             * Get number of attributes.
             */
            unsigned int getCount() const;
            /**
             * Get the hamdle to the GPU resource associated with the attribute data.
             */
            unsigned int getHandle() const;
            
        private:

            unsigned int mHandle;
            unsigned int mCount;
    }; // class Attribute
} // namespace urus
