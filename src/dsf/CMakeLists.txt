# add the modules subdirectories
set(INCROOT ${PROJECT_SOURCE_DIR}/include/DSF)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/DSF)

# all source files
set(SRC
	${INCROOT}/Config.h
	${INCROOT}/Debug.h
	${INCROOT}/Declaration.h
	${INCROOT}/DualStateFramework.h
	${INCROOT}/Export.h
	${INCROOT}/Runnable.h
	${INCROOT}/SynchronizedObject.h
	${INCROOT}/Task.h
	${INCROOT}/TaskArgument.h
	${INCROOT}/TaskBox.h
	${INCROOT}/TaskFunction.h
	${SRCROOT}/DualStateFramework.cpp
	${SRCROOT}/SynchronizedObject.cpp
	${SRCROOT}/Task.cpp
	${SRCROOT}/TaskBox.cpp
	${SRCROOT}/CMakeLists.txt
	PARENT_SCOPE
)
source_group("" FILES ${SRC})
