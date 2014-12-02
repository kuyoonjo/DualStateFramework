# add the modules subdirectories
set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

# all source files
set(SRC
	${INCROOT}/DSF/Config.h
	${INCROOT}/DSF/Debug.h
	${INCROOT}/DSF/Declaration.h
	${INCROOT}/DSF/DualStateFramework.h
	${INCROOT}/DSF/Export.h
	${INCROOT}/DSF/Runnable.h
	${INCROOT}/DSF/SynchronizedObject.h
    ${INCROOT}/DSF/SynchronizedVar.h
	${INCROOT}/DSF/Task.h
	${INCROOT}/DSF/TaskArgument.h
	${INCROOT}/DSF/TaskBox.h
	${INCROOT}/DSF/TaskFunction.h

	${SRCROOT}/DSF/DualStateFramework.cpp
	${SRCROOT}/DSF/SynchronizedObject.cpp
    ${SRCROOT}/DSF/SynchronizedVar.cpp
	${SRCROOT}/DSF/Task.cpp
	${SRCROOT}/DSF/TaskBox.cpp

    ${INCROOT}/YC/Any.h
    ${INCROOT}/YC/exception/AnyException.h
    ${SRCROOT}/YC/Any.cpp
    ${SRCROOT}/YC/exception/AnyException.cpp

	${SRCROOT}/CMakeLists.txt
	PARENT_SCOPE
)
source_group("" FILES ${SRC})
