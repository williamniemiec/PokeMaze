#pragma once

#include <iostream>
#include <vector>

namespace wniemiec {namespace util {namespace data
{
    /**
     * Contains methods that perform string manipulation.
     */
    class StringUtils
    {
    //-------------------------------------------------------------------------
    //      Constructor
    //-------------------------------------------------------------------------
    private:
        StringUtils();


    //-------------------------------------------------------------------------
    //      Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Returns a list of the words in the string, separated by the 
         * delimiter string.
         * 
         * @param       str String to be splited.
         * @param       sep Character dividing the string into split groups.
         * 
         * @return      Vector with split groups
         * 
         * @throws      std::invalid_argument If string is null or if separator
         * is null
         */
        static std::vector<std::string> split(std::string str, std::string sep);

        /**
         * Returns a copy of the string in UPPER CASE.
         * 
         * @param       str Some string
         * 
         * @return      String in upper case
         * 
         * @throws      std::invalid_argument If string is null
         */
        static std::string to_upper(std::string str);
    };
}}}
