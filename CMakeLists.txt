cmake_minimum_required (VERSION 3.15)
set (PROJECT_NAME "Urus")
project (${PROJECT_NAME})

set (CMAKE_CXX_STANDARD 14)
# get rid of configuration/generation of ZERO_CHECK target
set (CMAKE_SUPPRESS_REGENERATION true)
# Note that there is no way to suppress the ALL_BUILD target.
# It must exist for commands like cmake --build. 
# To be able to build the "all" target by default.
# see https://gitlab.kitware.com/cmake/cmake/-/issues/16979
# However, there are other solutions around the issue,
# as discussed for example here: https://stackoverflow.com/questions/49069493

# Group predefined targets INSTALL, RUN_TESTS etc. in global PREDEFINED_TARGETS_FOLDER 
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# set VS startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

find_package (OpenGL)

add_executable (${PROJECT_NAME}
    main.cpp
    )

target_sources (${PROJECT_NAME}
    PRIVATE
    # engine/base
    src/engine/base/opengl_support.h
    src/engine/base/core.h
    src/engine/base/macros.h
    src/engine/base/singleton.h
    # game
    src/game/point_cloud_viewer.h
    src/game/point_cloud_viewer.cpp
    src/game/game.h
    src/game/game.cpp
    src/game/glut_dispatch.h
    # game/view
    src/game/view/any_view.h
    src/game/view/any_view.cpp
    src/game/view/console_view.h
    src/game/view/console_view.cpp
    src/game/view/game_view.h
    src/game/view/game_view.cpp
    src/game/view/views.h
    # engine/graphics
    src/engine/graphics/vertex_attribute.h
    src/engine/graphics/vertex_attribute.cpp
    src/engine/graphics/display_config.h
    src/engine/graphics/display_config.cpp
    src/engine/graphics/draw.h
    src/engine/graphics/draw.cpp
    src/engine/graphics/indexbuffer.h
    src/engine/graphics/indexbuffer.cpp
    src/engine/graphics/node.h
    src/engine/graphics/node.cpp
    src/engine/graphics/scene.h
    src/engine/graphics/scene.cpp
    src/engine/graphics/shader.h
    src/engine/graphics/shader.cpp
    src/engine/graphics/texture.h
    src/engine/graphics/texture.cpp
    src/engine/graphics/texture_loader.h
    src/engine/graphics/texture_loader.cpp
    src/engine/graphics/uniform.h
    src/engine/graphics/uniform.cpp
    # engine/graphics/viewtransform
    src/engine/graphics/viewtransform/viewtransform.h
    src/engine/graphics/viewtransform/viewtransform.cpp
    # engine/input
    src/engine/input/input_processor.h
    src/engine/input/input_processor.cpp
    src/engine/input/trackball.h
    # engine/glsl
    src/glsl/shader0.vert
    src/glsl/shader0.frag
    src/glsl/shader1.vert
    src/glsl/shader1.frag
    src/glsl/coord_sys.vert
    src/glsl/coord_sys.frag
    # Macaque vector math lib
    # TODO: extract Macaque as a library into a dedicated repo
    src/macaque/mat.h
    src/macaque/mat4.h
    src/macaque/mq_math.h
    src/macaque/vec.h
    src/macaque/vec2.h
    src/macaque/vec3.h
    src/macaque/vec3.cpp
    src/macaque/vec4.h
    )

# third-party sources
target_sources (${PROJECT_NAME}
    PRIVATE
    lib/include/stb_image/stb_image.h
    lib/impl/stb_image/stb_image.cpp
    )

# configure source groups

source_group (game
    FILES
    src/game/point_cloud_viewer.h
    src/game/point_cloud_viewer.cpp
    src/game/game.h
    src/game/game.cpp
    src/game/glut_dispatch.h
    )

source_group (game\\view
    FILES
    src/game/view/any_view.h
    src/game/view/any_view.cpp
    src/game/view/console_view.h
    src/game/view/console_view.cpp
    src/game/view/game_view.h
    src/game/view/game_view.cpp
    src/game/view/views.h
    )

source_group (engine\\base
    FILES
    src/engine/base/opengl_support.h
    src/engine/base/core.h
    src/engine/base/macros.h
    src/engine/base/singleton.h
    )

source_group (engine\\graphics 
    FILES 
    src/engine/graphics/vertex_attribute.h
    src/engine/graphics/vertex_attribute.cpp
    src/engine/graphics/display_config.h
    src/engine/graphics/display_config.cpp
    src/engine/graphics/draw.h
    src/engine/graphics/draw.cpp
    src/engine/graphics/indexbuffer.h
    src/engine/graphics/indexbuffer.cpp
    src/engine/graphics/node.h
    src/engine/graphics/node.cpp
    src/engine/graphics/scene.h
    src/engine/graphics/scene.cpp
    src/engine/graphics/shader.h
    src/engine/graphics/shader.cpp
    src/engine/graphics/texture.h
    src/engine/graphics/texture.cpp
    src/engine/graphics/texture_loader.h
    src/engine/graphics/texture_loader.cpp
    src/engine/graphics/uniform.h
    src/engine/graphics/uniform.cpp
    )

source_group (engine\\graphics\\viewtransform
    FILES
    src/engine/graphics/viewtransform/viewtransform.h
    src/engine/graphics/viewtransform/viewtransform.cpp
    )

source_group (engine\\input
    FILES 
    src/engine/input/input_processor.h
    src/engine/input/input_processor.cpp
    src/engine/input/trackball.h
    )

source_group (glsl
    FILES
    src/glsl/shader0.vert
    src/glsl/shader0.frag
    src/glsl/shader1.vert
    src/glsl/shader1.frag
    src/glsl/coord_sys.vert
    src/glsl/coord_sys.frag
    )

source_group (macaque
    FILES
    src/macaque/mat.h
    src/macaque/mat4.h
    src/macaque/mq_math.h
    src/macaque/vec.h
    src/macaque/vec2.h
    src/macaque/vec3.h
    src/macaque/vec3.cpp
    src/macaque/vec4.h
    )

source_group (third_party
    FILES
    lib/include/stb_image/stb_image.h
    lib/impl/stb_image/stb_image.cpp
    )

source_group (main
    FILES
    main.cpp
    )

# copy shaders to the output direcotry
configure_file (src/glsl/shader0.vert ${CMAKE_CURRENT_BINARY_DIR}/shader0.vert)
configure_file (src/glsl/shader0.frag ${CMAKE_CURRENT_BINARY_DIR}/shader0.frag)
configure_file (src/glsl/shader1.vert ${CMAKE_CURRENT_BINARY_DIR}/shader1.vert)
configure_file (src/glsl/shader1.frag ${CMAKE_CURRENT_BINARY_DIR}/shader1.frag)
configure_file (src/glsl/coord_sys.vert ${CMAKE_CURRENT_BINARY_DIR}/coord_sys.vert)
configure_file (src/glsl/coord_sys.frag ${CMAKE_CURRENT_BINARY_DIR}/coord_sys.frag)

file (COPY assets/container.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file (COPY assets/grass.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file (COPY assets/red_sand.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file (COPY assets/smoking_monkey.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

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

if (APPLE)
	message ("  APPLE platform detected. Additionally linking frameworks:\n"
			 "  - CoreFoundation\n"
			 "  - CoreGraphics")
	target_link_libraries (${PROJECT_NAME}
		${CMAKE_SOURCE_DIR}/lib/x64/freeglut_staticd.lib
		${CMAKE_SOURCE_DIR}/lib/x64/glew64_staticd.lib
		"-framework CoreFoundation"
 		"-framework CoreGraphics")
elseif (WIN32)
    target_link_libraries (${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/lib/x64/freeglut_staticd.lib
        ${CMAKE_SOURCE_DIR}/lib/x64/glew64_staticd.lib)
endif ()
			
# FIXME: Add FREEGLUT_STATIC and GLEW_STATIC preprocessor directives
add_definitions (-DFREEGLUT_STATIC -DGLEW_STATIC)
# set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-DFREEGLUT_STATIC")
