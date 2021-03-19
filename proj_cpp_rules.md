Rules
Name: Don't use prefix get_. Give the get method the same name as the resource it returns.
For complex types (std::vector, std::string), return a const reference.
Don't const the return type for simple types (int, float), because this prevents move semantics to be applied.
For simple types (int, float), just copy the return value.
Mark get methods as [[nodiscard]] in the header file only.
Mark get methods as const, so they don't change members.
Do not add documentation for get methods, since it is self-explanatory.
Keep get methods directly in the header file.
Do not add inline since get methods in header files are always inlined.
The get method should not run any other code, like checking if the value is actually valid. Since we are using RAII, the value to return must be in a valid state anyways.

Also refer to:
- https://github.com/lefticus/cppbestpractices/blob/master/00-Table_of_Contents.md

C++ Core Guidelines
https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
https://github.com/isocpp/CppCoreGuidelines
