
link_directories(${OpenCV_LIB_DIR})

# main
add_library(main
    main/Gui.cpp
    main/Main.cpp
    main/Settings.cpp
    main/Gui.h
    main/Main.h
    main/Settings.h)

target_link_libraries(main libopentld cvblobs ${OpenCV_LIBS})

