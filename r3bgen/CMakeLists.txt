# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

# Check for gcc version, since for gcc 4 one has to add friend-injection
# as option to compile FairPlutoGenerator
#EXEC_PROGRAM( gcc ARGS "-dumpversion" OUTPUT_VARIABLE GCC_VERSION )
#STRING(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]" "\\1" req_gcc_major_vers "${GCC_VERSION}")
#STRING(REGEX REPLACE "^[0-9]+\\.([0-9]+)\\.[0-9]" "\\1" req_gcc_minor_vers "${GCC_VERSION}")
#IF(${req_gcc_major_vers} MATCHES "4" AND NOT ${req_gcc_minor_vers} MATCHES "0")
#  SET_SOURCE_FILES_PROPERTIES(FairPlutoGenerator.cxx PROPERTIES COMPILE_FLAGS
#  "-ffriend-injection")
#ENDIF(${req_gcc_major_vers} MATCHES "4" AND NOT ${req_gcc_minor_vers} MATCHES "0")

Set(SYSTEM_INCLUDE_DIRECTORIES 
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
#${PLUTO_INCLUDE_DIR}
)

set(INCLUDE_DIRECTORIES
${R3BROOT_SOURCE_DIR}/field 
${R3BROOT_SOURCE_DIR}/generators 
${R3BROOT_SOURCE_DIR}/r3bgen
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
#${PLUTO_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
R3BPrimaryGenerator.cxx
R3BSpecificGenerator.cxx
R3BReadKinematics.cxx
R3BCDGenerator.cxx
R3BBeamInfo.cxx
R3BBackTracking.cxx
R3BBackTrackingStorageState.cxx
R3BAsciiGenerator.cxx
R3BCosmicGenerator.cxx
R3Bp2pGenerator.cxx
R3BLandGenerator.cxx
R3BCALIFATestGenerator.cxx
R3BAsciiIQMDGen.cxx
R3BAsciiUrQMDGen.cxx
R3BIonGenerator.cxx

)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF R3BGenLinkDef.h)
set(LIBRARY_NAME R3BGen)
set(DEPENDENCIES
    Field Gen)

GENERATE_LIBRARY()

