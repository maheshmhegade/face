include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../opentld/opentld/main
                    ${CMAKE_CURRENT_SOURCE_DIR}/../opentld/libopentld/tld
                    )

add_library(tldinterface    tldinterface.cpp
                            tlddatabase.cpp
                            tldface.cpp
                            tldrecognition.cpp

                            tldinterface.h
                            tlddatabase.h
                            tldface.h
                            tldrecognition.h
                            )

target_link_libraries(tldinterface
                      main
                      libopentld
                      cvblobs
                      sqlite3
                      QtSql
                      ${OpenCV_LIBS}
                      ${QT_QTCORE_LIBRARY}
                      )
