cmake_minimum_required (VERSION 3.15)
set (PROJECT_NAME "Urus")
project (${PROJECT_NAME})

set (CMAKE_CXX_STANDARD 14)

add_executable (${PROJECT_NAME}
    main.cpp
    )

target_sources (${PROJECT_NAME}
    PRIVATE
    # application
    src/application/viewer.h
    src/application/viewer.cpp
    src/application/application.h
    src/application/application.cpp
    # engine/base
    src/engine/base/compiler_support.h
    src/engine/base/core.h
    src/engine/base/macros.h
    src/engine/base/singleton.h
    # engine/graphics
    src/engine/graphics/attribute.h
    src/engine/graphics/attribute.cpp
    src/engine/graphics/display_config.h
    src/engine/graphics/display_config.cpp
    src/engine/graphics/draw.h
    src/engine/graphics/draw.cpp
    src/engine/graphics/indexbuffer.h
    src/engine/graphics/indexbuffer.cpp
    src/engine/graphics/shader.h
    src/engine/graphics/shader.cpp
    src/engine/graphics/texture.h
    src/engine/graphics/uniform.h
    src/engine/graphics/uniform.cpp
    # engine/graphics/viewtransform
    src/engine/graphics/viewtransform/viewtransform.h
    src/engine/graphics/viewtransform/viewtransform.cpp
    # engine/input
    src/engine/input/input_processor.h
    src/engine/input/input_processor.cpp
    src/engine/input/trackball.h
    # engine/window
    src/engine/window/console.h
    src/engine/window/console.cpp
    src/engine/window/window.h
    src/engine/window/window.cpp
    # engine/glsl
    src/glsl/color.vert
    src/glsl/color.frag
    src/glsl/coord_sys.vert
    src/glsl/coord_sys.frag
    # Macaque vector math lib
    # TODO: extract Macaque as a library into a dedicated repo
    src/macaque/mat.h
    src/macaque/mat4.h
    src/macaque/vec.h
    src/macaque/vec2.h
    src/macaque/vec3.h
    src/macaque/vec3.cpp
    src/macaque/vec4.h
    )

# configure souorce groups

source_group (application
    FILES
    src/application/viewer.h
    src/application/viewer.cpp
    src/application/application.h
    src/application/application.cpp
    )

source_group (engine/base
    FILES
    src/engine/base/compiler_support.h
    src/engine/base/core.h
    src/engine/base/macros.h
    src/engine/base/singleton.h
    )

source_group (engine/graphics 
    FILES 
    src/engine/graphics/attribute.h
    src/engine/graphics/attribute.cpp
    src/engine/graphics/display_config.h
    src/engine/graphics/display_config.cpp
    src/engine/graphics/draw.h
    src/engine/graphics/draw.cpp
    src/engine/graphics/indexbuffer.h
    src/engine/graphics/indexbuffer.cpp
    src/engine/graphics/shader.h
    src/engine/graphics/shader.cpp
    src/engine/graphics/texture.h
    src/engine/graphics/uniform.h
    src/engine/graphics/uniform.cpp
    )

source_group (engine/graphics/viewtransform
    FILES
    src/engine/graphics/viewtransform/viewtransform.h
    src/engine/graphics/viewtransform/viewtransform.cpp
    )

source_group (engine/input
    FILES 
    src/engine/input/input_processor.h
    src/engine/input/input_processor.cpp
    src/engine/input/trackball.h
    )

source_group (engine/window
    FILES
    src/engine/window/console.h
    src/engine/window/console.cpp
    src/engine/window/window.h
    src/engine/window/window.cpp
    )

source_group (glsl
    FILES
    src/glsl/color.vert
    src/glsl/color.frag
    src/glsl/coord_sys.vert
    src/glsl/coord_sys.frag
    )

source_group (macaque
    FILES
    src/macaque/mat.h
    src/macaque/mat4.h
    src/macaque/vec.h
    src/macaque/vec2.h
    src/macaque/vec3.h
    src/macaque/vec3.cpp
    src/macaque/vec4.h
    )

source_group (main
    FILES
    main.cpp
    )

# copy shaders to the output direcotry
configure_file (src/glsl/color.vert ${CMAKE_CURRENT_BINARY_DIR}/color.vert)
configure_file (src/glsl/color.frag ${CMAKE_CURRENT_BINARY_DIR}/color.frag)
configure_file (src/glsl/coord_sys.vert ${CMAKE_CURRENT_BINARY_DIR}/coord_sys.vert)
configure_file (src/glsl/coord_sys.frag ${CMAKE_CURRENT_BINARY_DIR}/coord_sys.frag)

target_include_directories (${PROJECT_NAME}
    PRIVATE
    lib/include
    src
    src/macaque
    )

target_link_libraries (${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/lib/x64/freeglut_staticd.lib
    ${CMAKE_SOURCE_DIR}/lib/x64/glew64_staticd.lib
    )

# FIXME: Add FREEGLUT_STATIC and GLEW_STATIC preprocessor directives
add_definitions (-DFREEGLUT_STATIC -DGLEW_STATIC)
# set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-DFREEGLUT_STATIC")