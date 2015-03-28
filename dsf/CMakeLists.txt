# source files
set(DSF_SRC
    ${SRCROOT}/DSF/DualStateFramework.cpp
    ${SRCROOT}/DSF/Lock.cpp
    ${SRCROOT}/DSF/SynchronizedObject.cpp
    ${SRCROOT}/DSF/SynchronizedVar.cpp
    ${SRCROOT}/DSF/Task.cpp
    ${SRCROOT}/DSF/TaskBox.cpp
	PARENT_SCOPE
)
source_group("" FILES ${DSF_SRC})

# headers

set(DSF_INC
    ${INCROOT}/DSF/Config.h
    ${INCROOT}/DSF/Declaration.h
    ${INCROOT}/DSF/DualStateFramework.h
    ${INCROOT}/DSF/Export.h
    ${INCROOT}/DSF/Lock.h
    ${INCROOT}/DSF/Runnable.h
    ${INCROOT}/DSF/SynchronizedObject.h
    ${INCROOT}/DSF/SynchronizedVar.h
    ${INCROOT}/DSF/Synchronisable.h
    ${INCROOT}/DSF/Task.h
    ${INCROOT}/DSF/TaskArgument.h
    ${INCROOT}/DSF/TaskBox.h
    ${INCROOT}/DSF/TaskFunction.h
	PARENT_SCOPE
)
source_group("" FILES ${DSF_INC})

