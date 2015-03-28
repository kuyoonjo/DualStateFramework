# source files
set(DSF_SRC
    ${SRCROOT}/dsf/DualStateFramework.cpp
    ${SRCROOT}/dsf/Lock.cpp
    ${SRCROOT}/dsf/SynchronizedObject.cpp
    ${SRCROOT}/dsf/SynchronizedVar.cpp
    ${SRCROOT}/dsf/Task.cpp
    ${SRCROOT}/dsf/TaskBox.cpp
	PARENT_SCOPE
)
source_group("" FILES ${DSF_SRC})

# headers

set(DSF_INC
    ${INCROOT}/dsf/Config.h
    ${INCROOT}/dsf/Declaration.h
    ${INCROOT}/dsf/DualStateFramework.h
    ${INCROOT}/dsf/Export.h
    ${INCROOT}/dsf/Lock.h
    ${INCROOT}/dsf/Runnable.h
    ${INCROOT}/dsf/SynchronizedObject.h
    ${INCROOT}/dsf/SynchronizedVar.h
    ${INCROOT}/dsf/Synchronisable.h
    ${INCROOT}/dsf/Task.h
    ${INCROOT}/dsf/TaskArgument.h
    ${INCROOT}/dsf/TaskBox.h
    ${INCROOT}/dsf/TaskFunction.h
	PARENT_SCOPE
)
source_group("" FILES ${DSF_INC})

