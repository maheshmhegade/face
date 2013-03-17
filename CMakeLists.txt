project(face)

find_package(Qt4 4.6.0 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(KDE4 REQUIRED)

set(face_SRS    livevideo.cpp
                main.cpp
                mainwindow.cpp
                    
                livevideo.h
                mainwindow.h)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${KDE4_ENABLE_EXCEPTIONS})
ADD_DEFINITIONS(${QT_DEFINITIONS})

KDE4_ADD_UI_FILES(face_SRS mainwindow.ui)

KDE4_ADD_EXECUTABLE(face ${face_SRS})

INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

target_link_libraries(face    ${OpenCV_LIBS}
                              ${KDE4_KDECORE_LIBS}
                              ${KDE4_KDEUI_LIBS}
                              ${QT_QTCORE_LIBRARY}
                              ${QT_QTGUI_LIBRARY}
                              )
