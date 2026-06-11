cmake_minimum_required(VERSION 3.21)

project(Decodius VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Componenti Qt6 necessari. TextToSpeech è opzionale: se manca, l'app
# compila lo stesso (solo senza voce sintetizzata).
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Multimedia Network)
find_package(Qt6 QUIET OPTIONAL_COMPONENTS TextToSpeech)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(decodius
    main.cpp
    AudioAnalyzer.cpp
    OllamaClient.cpp
    Assistant.cpp
    PiperTts.cpp
    XttsTts.cpp
    WhisperStt.cpp
    DecodiumConfig.cpp
)

qt_add_qml_module(decodius
    URI Decodius
    VERSION 1.0
    QML_FILES
        Main.qml
    RESOURCES
        world.png
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
