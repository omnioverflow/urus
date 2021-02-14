#pragma once

namespace urus
{
    /**
     * A helper class that provides utilities to get configurations 
     * of the host display
     */
    class DisplayConfig
    {
    public:
        /**
         * Get main screen width in pixels.
         */
        static int getScreenWidth();
        static int getScreenHeight();
    }; // class DisplayConfig
} // namespace urus
