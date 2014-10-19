# add the modules subdirectories
set(INCROOT ${PROJECT_SOURCE_DIR}/include/DSF)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/DSF)

# all source files
set(SRC
	${INCROOT}/Config.h
	${INCROOT}/DualStateFramework.h
	${INCROOT}/Export.h
	${INCROOT}/Runnable.h
	${INCROOT}/Task.h
	${INCROOT}/TaskArgument.h
	${INCROOT}/TaskBox.h
	${INCROOT}/TaskFunction.h
	${INCROOT}/TaskQueue.h
	${SRCROOT}/DualStateFramework.cpp
	${SRCROOT}/Task.cpp
	${SRCROOT}/TaskQueue.cpp
	PARENT_SCOPE
)
source_group("" FILES ${SRC})
