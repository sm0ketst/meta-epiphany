##################################################################
# Part two of this refactoring will move this file to
# exotic-newlib-1.20.inc
# But the exotic version will reference normal newlib and 
# as a result the .bb file will have to override SRC_URI
##################################################################

##
## modelled on gcc-${PV}.inc
##

require epiphany-elf-newlib-common.inc

# Third digit in PV should be incremented after a minor release

PV = "1.20"

# BINV should be incremented to a revision after a minor gcc release

BINV = "1.20"

#FILESEXTRAPATHS =. "${FILE_DIRNAME}/newlib-1.20:"

DEPENDS =+ "mpfr gmp libmpc zlib"

LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

LIC_FILES_CHKSUM="\
    file://src-release;endline=17;md5=4830a9ef968f3b18dd5e9f2c00db2d35\
    file://COPYING;md5=59530bdf33659b29e73d4adb9f9f6552\
    file://COPYING.LIB;md5=9f604d8a4f8e74f4f5140845a21b6674\
    file://COPYING3;md5=d32239bcb673463ab874e80d47fae504\
    file://COPYING3.LIB;md5=6a6a8e020838b23406c81b19c1d46df6\
    file://COPYING.LIBGLOSS;md5=3b001af45e794098f2d25681da304976\
    file://COPYING.NEWLIB;md5=83b8a8d7d3da9eeb75d99feba4fdc614\
    "

ENEWLIBBRANCH = "epiphany-newlib-1.20-software-cache"
SRC_URI = " git://github.com/adapteva/epiphany-newlib.git;branch=${ENEWLIBBRANCH};name=${ENEWLIBBRANCH} \
          "

# Tag: epiphany-newlib-esdk-2014.11
SRCREV = "35a4aa0fd514c506cdd0f9043ee9248728db8ffc"

# Language Overrides
FORTRAN = ""
JAVA = ""

EXTRA_OECONF = " --enable-languages=c,c++ \
    --with-cross-host=${EXOTIC_TARGET_SYS} \
    --with-gxx-include-dir=${STAGING_DIR_TARGET}${target_includedir}/c++/${BINV} \ 
    --with-sysroot=${STAGING_DIR_TARGET} \ 
    --with-build-sysroot=${STAGING_DIR_TARGET} \
"
