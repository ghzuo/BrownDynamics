SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_DEFINITIONS("-O3 -std=c++11")
LINK_LIBRARIES(m)

SET(BROWN_SRC
  myVector.h myVector.cpp
  interaction.h interaction.cpp
  atom.h atom.cpp
  brownDynamics.h brownDynamics.cpp
  stringOpt.h stringOpt.cpp
  )

SET(TESTV_SRC
  myVector.h myVector.cpp
  testvec.cpp
  )


ADD_EXECUTABLE(testvec ${TESTV_SRC})
ADD_EXECUTABLE(brown   ${BROWN_SRC})

INSTALL(TARGETS testvec brown
  RUNTIME DESTINATION bin)
