#ifndef CHARLES_ASSIGNMENT_INCLUDED
#define CHARLES_ASSIGNMENT_INCLUDED

// Macro to easily implement CreateAssignment.
#define CREATE_ASSIGNMENT(TYPE) \
std::unique_ptr<Assignment> CreateAssignment() { \
    return std::make_unique<TYPE>(); \
}

#define CREATE_ASSIGNMENT_WITH_ARGS(TYPE, ...) \
std::unique_ptr<Assignment> CreateAssignment() { \
    return std::make_unique<TYPE>(__VA_ARGS__); \
}

#else
// Generate error to indicate multiple assignments have been included, which is not allowed.
// There should always only be exactly one assignment that is included in agent.cpp.
#error Multiple Charles assignments included in agent.cpp, please only include one assignment

// Redefine create assignment macro to a NOP to prevent redefinition error of CreateAssignment.
#undef CREATE_ASSIGNMENT
#undef CREATE_ASSIGNMENT_WITH_ARGS
#define CREATE_ASSIGNMENT(TYPE)
#define CREATE_ASSIGNMENT_WITH_ARGS(TYPE, ...)

#endif