# Create an empty set of sources for the ExceptionLib
set(EXCEPTION_SOURCES  EmptyStack.cpp)  # Replace with actual filenames if needed

# Create the ExceptionLib library
add_library(ExceptionLib ${EXCEPTION_SOURCES})

# Specify the library's include directories
target_include_directories(ExceptionLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}  # Include current directory
)
# Link ExceptionTestLib to ExceptionLib
target_link_libraries(ExceptionLib)