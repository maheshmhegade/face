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

INCLUDE_DIRECTORIES(${QDBUS_INCLUDE_DIRS}
                    ${KDE4_INCLUDES}
                    ${OpenCV_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_SOURCE_DIR}/opentld/3rdparty/cvblobs
                    ${CMAKE_CURRENT_SOURCE_DIR}/opentld/libopentld/imacq
                    ${CMAKE_CURRENT_SOURCE_DIR}/opentld/libopentld/mftracker
                    ${CMAKE_CURRENT_SOURCE_DIR}/opentld/libopentld/tld
                    ${CMAKE_CURRENT_SOURCE_DIR}/opentld/opentld/main
                    ${CMAKE_CURRENT_SOURCE_DIR}/tldinterface
                    ${OpenCV_INCLUDE_DIRS}
                    )

#start OpenTLD

SUBDIRS(opentld/3rdparty/cvblobs)
SUBDIRS(opentld/libopentld)
SUBDIRS(opentld/opentld)
SUBDIRS(tldinterface)

#end OpenTLD

KDE4_ADD_UI_FILES(face_SRS mainwindow.ui)

KDE4_ADD_EXECUTABLE(face ${face_SRS})

target_link_libraries(face    ${OpenCV_LIBS}
                              ${KDE4_KDECORE_LIBS}
                              ${KDE4_KDEUI_LIBS}
                              ${QT_QTCORE_LIBRARY}
                              ${QT_QTGUI_LIBRARY}

                              tldinterface
                              main
                              libopentld
                              cvblobs
                              sqlite3
                              QtSql
                              )
