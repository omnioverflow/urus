#pragma once

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

            // FIXME: no need in the following method?
            //void setAttributePointer(unsigned int slot);
            /**
             * Upload an array of data to GPU. Each element in the array represents
             * the attribute for one vertex.
             */
            void set(T* inputArray, unsigned int arrayLength); // FIXME: const ?
            void set(std::vector<T>& input); // FIXME: const std::vector<T>& ?
            void bindTo(unsigned int slot);
            void unbindFrom(unsigned int slot);

            /**
             * Get number of attributes.
             */
            unsigned int getCount() const;
            /**
             * Get the hamdle to the GPU resource associated with the attribute data.
             */
            unsigned int getHandle() const;
            
        private:

            unsigned int handle;
            unsigned int mCount;
    }; // class Attribute
} // namespace urus

