add_executable(TheTerrain WIN32
    Main.cpp
    TheApp.cpp
    CameraFrustum.cpp
    DepthShader.cpp
    Patch.cpp
    Skybox.cpp
    Terrain.cpp
    TessellationShader.cpp
    TextureShader.cpp
)

target_link_libraries(TheTerrain PRIVATE
    TheEngine
    d3d11.lib
    dxgi.lib
    D3DCompiler.lib
)

target_compile_definitions(TheTerrain PRIVATE
    WIN32
    UNICODE
    _UNICODE
    _WINDOWS
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

target_compile_options(TheTerrain PRIVATE /W3)

# Copy assets to output directory
add_custom_command(TARGET TheTerrain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:TheTerrain>/assets
)
