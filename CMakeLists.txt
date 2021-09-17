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
    src/engine/base/OpenGLSupport.h
    src/engine/base/Core.h
    src/engine/base/Macros.h
    src/engine/base/Singleton.h
    # engine/controls
    src/engine/controls/InputDispatcher.h
    src/engine/controls/InputDispatcher.cpp
    src/engine/controls/Trackball.h
    # engine/backend/opengl
    src/engine/backend/gl/Draw.h
    src/engine/backend/gl/Draw.cpp
    src/engine/backend/gl/GLRenderer.h
    src/engine/backend/gl/GLRenderer.cpp
    src/engine/backend/gl/IndexBuffer.h
    src/engine/backend/gl/IndexBuffer.cpp
    src/engine/backend/gl/Uniform.h
    src/engine/backend/gl/Uniform.cpp
    src/engine/backend/gl/VertexAttribute.h
    src/engine/backend/gl/VertexAttribute.cpp
    # engine/geometry
    src/engine/geometry/BoundingBox.h
    src/engine/geometry/Mesh.h
    src/engine/geometry/Mesh.cpp
    # engine/renderer
    src/engine/renderer/Renderer.h
    # engine/scene
    src/engine/scene/SceneNode.h
    src/engine/scene/SceneNode.cpp
    src/engine/scene/Scene.h
    src/engine/scene/Scene.cpp
    # engine/shader
    src/engine/shader/Shader.h
    src/engine/shader/Shader.cpp
    # engine/texture
    src/engine/texture/Texture.h
    src/engine/texture/Texture.cpp
    src/engine/texture/TextureLoader.h
    src/engine/texture/TextureLoader.cpp
    # engine/viewtransform
    src/engine/viewtransform/DisplayConfig.h
    src/engine/viewtransform/DisplayConfig.cpp
    src/engine/viewtransform/ViewTransform.h
    src/engine/viewtransform/ViewTransform.cpp
    # game
    src/game/PathTracer.h
    src/game/PathTracer.cpp
    src/game/PointCloudViewer.h
    src/game/PointCloudViewer.cpp
    src/game/Game.h
    src/game/Game.cpp
    # game/model
    src/game/model/GameWorld.h
    src/game/model/GameWorld.cpp
    # game/view
    src/game/view/AnyView.h
    src/game/view/AnyView.cpp
    src/game/view/ConsoleView.h
    src/game/view/ConsoleView.cpp
    src/game/view/GameView.h
    src/game/view/GameView.cpp
    src/game/view/Views.h
    # glsl
    src/glsl/shader0.vert
    src/glsl/shader0.frag
    src/glsl/shader1.vert
    src/glsl/shader1.frag
    src/glsl/coord_sys.vert
    src/glsl/coord_sys.frag
    # Macaque Math (mqMath) vector math lib
    # TODO: extract mqMath as a library into a dedicated repo
    src/mqMath/Mat.h
    src/mqMath/Mat2.cpp
    src/mqMath/Mat3.cpp
    src/mqMath/Mat4.cpp
    src/mqMath/RowMajorMat4.h
    src/mqMath/MqMath.h
    src/mqMath/Vec.h
    src/mqMath/Vec2.h
    src/mqMath/Vec3.h
    src/mqMath/Vec3.cpp
    src/mqMath/Vec4.h
    src/mqMath/Vec4.cpp
    )

# third-party sources
target_sources (${PROJECT_NAME}
    PRIVATE
    # stb_image
    lib/include/stb_image/stb_image.h
    lib/impl/stb_image/stb_image.cpp
    # gsl 
    lib/include/gsl/assert.h
    )

# configure source groups
# ==============================================================================

source_group (engine\\base
    FILES
    src/engine/base/OpenGLSupport.h
    src/engine/base/Core.h
    src/engine/base/Macros.h
    src/engine/base/Singleton.h
    )

source_group (engine\\backend\\gl
    FILES 
    src/engine/backend/gl/VertexAttribute.h
    src/engine/backend/gl/VertexAttribute.cpp
    src/engine/backend/gl/Draw.h
    src/engine/backend/gl/Draw.cpp
    src/engine/backend/gl/GLRenderer.h
    src/engine/backend/gl/GLRenderer.cpp
    src/engine/backend/gl/IndexBuffer.h
    src/engine/backend/gl/IndexBuffer.cpp
    src/engine/backend/gl/Uniform.h
    src/engine/backend/gl/Uniform.cpp
    )

source_group (engine\\controls
    FILES 
    src/engine/controls/InputDispatcher.h
    src/engine/controls/InputDispatcher.cpp
    src/engine/controls/Trackball.h
    )

source_group (engine\\geometry
    FILES
    src/engine/geometry/BoundingBox.h
    src/engine/geometry/Mesh.h
    src/engine/geometry/Mesh.cpp
    )

source_group (engine\\renderer
    FILES
    src/engine/renderer/Renderer.h
    )

source_group (engine\\scene
    FILES
    src/engine/scene/SceneNode.h
    scr/engine/scene/SceneNode.cpp
    src/engine/scene/Scene.h
    scr/engine/scene/Scene.cpp
    )

source_group (engine\\shader
    src/engine/shader/Shader.h
    src/engine/shader/Shader.cpp
    )

source_group (engine\\texture
    src/engine/texture/Texture.h
    src/engine/texture/Texture.cpp
    src/engine/texture/TextureLoader.h
    src/engine/texture/TextureLoader.cpp
    )

source_group (engine\\viewtransform
    FILES
    src/engine/viewtransform/DisplayConfig.h
    src/engine/viewtransform/DisplayConfig.cpp
    src/engine/viewtransform/ViewTransform.h
    src/engine/viewtransform/ViewTransform.cpp
    )

# ==============================================================================
source_group (game
    FILES
    src/game/PointCloudViewer.h
    src/game/PointCloudViewer.cpp
    src/game/Game.h
    src/game/Game.cpp
    )

source_group (game\\model
    FILES
    src/game/model/GameWorld.h
    src/game/model/GameWorld.cpp
    )

source_group (game\\view
    FILES
    src/game/view/AnyView.h
    src/game/view/AnyView.cpp
    src/game/view/ConsoleView.h
    src/game/view/ConsoleView.cpp
    src/game/view/GameView.h
    src/game/view/GameView.cpp
    src/game/view/Views.h
    )
# ==============================================================================

source_group (glsl
    FILES
    src/glsl/shader0.vert
    src/glsl/shader0.frag
    src/glsl/shader1.vert
    src/glsl/shader1.frag
    src/glsl/coord_sys.vert
    src/glsl/coord_sys.frag
    )

# ==============================================================================

# Macaque Math (mqMath)
source_group (mqMath
    FILES
    src/mqMath/Mat.h
    src/mqMath/Mat2.cpp
    src/mqMath/Mat3.cpp
    src/mqMath/Mat4.cpp
    src/mqMath/RowMajorMat4.h
    src/mqMath/MqMath.h
    src/mqMath/Vec.h
    src/mqMath/Vec2.h
    src/mqMath/Vec3.h
    src/mqMath/Vec3.cpp
    src/mqMath/Vec4.h
    src/mqMath/Vec4.cpp
    )

# ==============================================================================

source_group (third_party\\stb_image
    FILES
    lib/include/stb_image/stb_image.h
    lib/impl/stb_image/stb_image.cpp
    )

source_group (third_party\\gsl
    FILES
    lib/include/gsl/assert.h
    )

source_group (main
    FILES
    main.cpp
    )

# ==============================================================================

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
    src/mqMath
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
