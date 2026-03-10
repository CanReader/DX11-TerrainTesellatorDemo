add_library(DirectXTK STATIC
    Src/AlphaTestEffect.cpp
    Src/BasicEffect.cpp
    Src/BinaryReader.cpp
    Src/CommonStates.cpp
    Src/DDSTextureLoader.cpp
    Src/DGSLEffect.cpp
    Src/DGSLEffectFactory.cpp
    Src/DualTextureEffect.cpp
    Src/EffectCommon.cpp
    Src/EffectFactory.cpp
    Src/EnvironmentMapEffect.cpp
    Src/GamePad.cpp
    Src/GeometricPrimitive.cpp
    Src/Geometry.cpp
    Src/GraphicsMemory.cpp
    Src/Keyboard.cpp
    Src/Model.cpp
    Src/ModelLoadCMO.cpp
    Src/ModelLoadSDKMESH.cpp
    Src/ModelLoadVBO.cpp
    Src/Mouse.cpp
    Src/NormalMapEffect.cpp
    Src/pch.cpp
    Src/PrimitiveBatch.cpp
    Src/ScreenGrab.cpp
    Src/SimpleMath.cpp
    Src/SkinnedEffect.cpp
    Src/SpriteBatch.cpp
    Src/SpriteFont.cpp
    Src/VertexTypes.cpp
    Src/WICTextureLoader.cpp
)

target_include_directories(DirectXTK
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Src
)

target_compile_definitions(DirectXTK PRIVATE
    _WIN32_WINNT=0x0600
    _WIN7_PLATFORM_UPDATE
    WIN32
    _LIB
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

target_precompile_headers(DirectXTK PRIVATE Src/pch.h)

target_compile_options(DirectXTK PRIVATE
    /W4
    /fp:fast
    $<$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},Win32>:/arch:SSE2>
)
