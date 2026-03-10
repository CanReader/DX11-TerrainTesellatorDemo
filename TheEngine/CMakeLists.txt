add_library(TheEngine STATIC
    BaseApplication.cpp
    BaseMesh.cpp
    BaseShader.cpp
    Camera.cpp
    CubeMesh.cpp
    D3D.cpp
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_impl_dx11.cpp
    Input.cpp
    Light.cpp
    Mesh.cpp
    Model.cpp
    OrthoMesh.cpp
    PlaneMesh.cpp
    PointMesh.cpp
    QuadMesh.cpp
    RenderTexture.cpp
    SphereMesh.cpp
    System.cpp
    TessellationMesh.cpp
    Texture.cpp
    Timer.cpp
    TokenStream.cpp
    TriangleMesh.cpp
)

target_include_directories(TheEngine
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(TheEngine PUBLIC
    DirectXTK
    d3d11.lib
    d3dcompiler.lib
    dxguid.lib
    dxgi.lib
)

target_compile_definitions(TheEngine PRIVATE
    WIN32
    UNICODE
    _UNICODE
    _LIB
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

target_compile_options(TheEngine PRIVATE /W3)
