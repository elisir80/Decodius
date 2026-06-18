cmake_minimum_required(VERSION 3.21)

project(Decodius VERSION 1.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Componenti Qt6 necessari. TextToSpeech è opzionale: se manca, l'app
# compila lo stesso (solo senza voce sintetizzata).
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Multimedia Network)
find_package(Qt6 QUIET OPTIONAL_COMPONENTS TextToSpeech)

qt_standard_project_setup(REQUIRES 6.4)

qt_add_executable(decodius
    main.cpp
    AudioAnalyzer.cpp
    OllamaClient.cpp
    Assistant.cpp
    PiperTts.cpp
    XttsTts.cpp
    WhisperStt.cpp
)

qt_add_qml_module(decodius
    URI Decodius
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        AudioAnalyzer.h
        Assistant.h
)

target_link_libraries(decodius PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Multimedia
    Qt6::Network
)

if (TARGET Qt6::TextToSpeech)
    target_link_libraries(decodius PRIVATE Qt6::TextToSpeech)
    target_compile_definitions(decodius PRIVATE HAVE_TTS)
    message(STATUS "Decodius: TextToSpeech ATTIVO (voce sintetizzata).")
else()
    message(STATUS "Decodius: TextToSpeech non trovato -> build senza voce.")
endif()

# Su Windows: app GUI senza finestra console + icona dell'exe (risorsa .rc).
if (WIN32)
    set_target_properties(decodius PROPERTIES WIN32_EXECUTABLE TRUE)
    enable_language(RC)
    target_sources(decodius PRIVATE decodius.rc)
endif()

# Su macOS l'eseguibile "decodius" collide con la directory QML "Decodius"
# su filesystem case-insensitive. Genera quindi il bundle GUI nativo.
if (APPLE)
    set_target_properties(decodius PROPERTIES
        MACOSX_BUNDLE TRUE
        OUTPUT_NAME Decodius
        MACOSX_BUNDLE_BUNDLE_NAME Decodius
        MACOSX_BUNDLE_GUI_IDENTIFIER it.iu8lmc.Decodius
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    )

endif()

set(DECODIUS_RUNTIME_FILES
    decodius.ico
    decodius_model.txt
    decodius_system.txt
    decodius_ham_kb.md
    LEGGIMI.txt
    LEGGIMI-Decodium.txt
    setup_cervello.ps1
)

if (APPLE)
    set(DECODIUS_RUNTIME_OUTPUT_DIR "$<TARGET_BUNDLE_DIR:decodius>/Contents/Resources")
else()
    set(DECODIUS_RUNTIME_OUTPUT_DIR "$<TARGET_FILE_DIR:decodius>")
endif()

foreach(runtime_file IN LISTS DECODIUS_RUNTIME_FILES)
    add_custom_command(TARGET decodius POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/${runtime_file}"
            "${DECODIUS_RUNTIME_OUTPUT_DIR}/${runtime_file}"
        VERBATIM
    )
endforeach()

add_custom_command(TARGET decodius POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/edge"
        "${DECODIUS_RUNTIME_OUTPUT_DIR}/edge"
    VERBATIM
)

if (APPLE)
    add_custom_command(TARGET decodius POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rm -rf
            "$<TARGET_FILE_DIR:decodius>/edge"
            "$<TARGET_FILE_DIR:decodius>/decodius_model.txt"
            "$<TARGET_FILE_DIR:decodius>/decodius_system.txt"
            "$<TARGET_FILE_DIR:decodius>/decodius_ham_kb.md"
            "$<TARGET_FILE_DIR:decodius>/setup_cervello.ps1"
        COMMAND Qt6::macdeployqt
            "$<TARGET_BUNDLE_DIR:decodius>"
            "-qmldir=${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Deploying Decodius macOS bundle with macdeployqt"
        VERBATIM
    )
endif()
