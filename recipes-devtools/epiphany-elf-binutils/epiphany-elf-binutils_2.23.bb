##################################################################
# Override variables with the remote target details

EXOTIC_TARGET_ARCH = "epiphany"
EXOTIC_TARGET_OS = "elf"
EXOTIC_TARGET_SYS = "epiphany-elf"

# update these as appropriate!
EXOTIC_TARGET_CFLAGS = "${TARGET_CFLAGS_GVARIABLE}"
EXOTIC_TARGET_CXXFLAGS = "${TARGET_CXXFLAGS_GVARIABLE}"
EXOTIC_TARGET_LDFLAGS = "${TARGET_LDFLAGS_GVARIABLE}" 

##################################################################
# Part two of this refactoring will make this file an append to
# the exotic-binutils_2.23.bb file and the following will be
# the content of that file!
##################################################################

##################################################################
# Extensions to bitbake.conf
#   Temp location.  These should go into poky/meta/conf/bitbake.conf
##################################################################
#
##################################################################
# Architecture-dependent build variables.
##################################################################

# For these recipes we may need to override TARGET and HOST whilst keeping 
# variables derived from the original TARGET and HOST unchanged.
# To do this create new variables to store the original TARGET and HOST
HOST_ARCH_GVARIABLE := "${HOST_ARCH}"
HOST_OS_GVARIABLE := "${HOST_OS}"
HOST_VENDOR_GVARIABLE := "${HOST_VENDOR}"
HOST_SYS_GVARIABLE := "${HOST_SYS}"
HOST_PREFIX_GVARIABLE := "${HOST_PREFIX}"
HOST_CC_ARCH_GVARIABLE := "${HOST_CC_ARCH}"
HOST_LD_ARCH_GVARIABLE := "${HOST_LD_ARCH}"
HOST_AS_ARCH_GVARIABLE := "${HOST_AS}"
HOST_EXEEXT_GVARIABLE := "${HOST_EXEEXT}"

## Moved to autotools_exotic
#TARGET_ARCH_GVARIABLE := "${TARGET_ARCH}"
#TARGET_OS_GVARIABLE := "${TARGET_OS}"
#TARGET_VENDOR_GVARIABLE := "${TARGET_VENDOR}"
#TARGET_SYS_GVARIABLE := "${TARGET_SYS}"
#TARGET_PREFIX_GVARIABLE := "${TARGET_SYS}-"
#TARGET_CC_ARCH_GVARIABLE := "${TARGET_CC_ARCH}"
#TARGET_LD_ARCH_GVARIABLE := "${TARGET_LD_ARCH}"
#TARGET_AS_ARCH_GVARIABLE := "${TARGET_AS_ARCH}"

##################################################################
# Build flags and options.
##################################################################
#TARGET_CFLAGS_GVARIABLE := "${TARGET_CFLAGS}"
#TARGET_CPPFLAGS_GVARIABLE := "${TARGET_CPPFLAGS}"
#TARGET_CXXFLAGS_GVARIABLE := "${TARGET_CXXFLAGS}"
#TARGET_LDFLAGS_GVARIABLE := "${TARGET_LDFLAGS}"


#
# Now update HOST variables
#
HOST_ARCH = "${TARGET_ARCH_GVARIABLE}"
HOST_OS = "${TARGET_OS_GVARIABLE}"
HOST_VENDOR = "${TARGET_VENDOR_GVARIABLE}"
HOST_SYS = "${TARGET_SYS_GVARIABLE}"
HOST_PREFIX = "${TARGET_PREFIX_GVARIABLE}"
HOST_CC_ARCH = "${TARGET_CC_ARCH_GVARIABLE}"
HOST_LD_ARCH = "${TARGET_LD_ARCH_GVARIABLE}"
HOST_AS_ARCH = "${TARGET_AS_ARCH_GVARIABLE}"
HOST_EXEEXT = ""

## following is moved to autotools_exotic
#TARGET_ARCH = "${EXOTIC_TARGET_ARCH}"
#TARGET_OS = "${EXOTIC_TARGET_OS}"
#TARGET_VENDOR = "${EXOTIC_TARGET_VENDOR}"
#TARGET_SYS = "${EXOTIC_TARGET_SYS}"
#TARGET_PREFIX = "${TARGET_SYS}-"
#TARGET_CC_ARCH = "${EXOTIC_TARGET_CC_ARCH}"
#TARGET_LD_ARCH = "${EXOTIC_TARGET_LD_ARCH}"
#TARGET_AS_ARCH = "${EXOTIC_TARGET_AS_ARCH}"

#
# Now all the scripts in this recipe can use TARGET_??
# or can use the original settings of TARGET_??_GVARIABLE
#
# For example override STAGING_BINDIR_TOOLCHAIN to match original TARGET
#
STAGING_BINDIR_TOOLCHAIN = "${STAGING_DIR_NATIVE}${bindir_native}/${TARGET_ARCH_GVARIABLE}${TARGET_VENDOR_GVARIABLE}-${TARGET_OS_GVARIABLE}"
MULTIMACH_TARGET_SYS = "${PACKAGE_ARCH}${TARGET_VENDOR_GVARIABLE}-${TARGET_OS_GVARIABLE}"
MULTIMACH_HOST_SYS = "${PACKAGE_ARCH}${HOST_VENDOR_GVARIABLE}-${HOST_OS_GVARIABLE}"

#
# Now the script
#
BASEDEPENDS = "virtual/${HOST_PREFIX}gcc virtual/${HOST_PREFIX}compilerlibs virtual/libc"

require epiphany-elf-binutils.inc
require epiphany-elf-binutils-${PV}.inc

DEPENDS += "flex bison zlib"

EXTRA_OECONF += "--with-sysroot=/ \
                --enable-shared \
                --disable-install-libiberty \
                "

# remove rpath from binaries that contain an rpath with build machine paths
DEPENDS += "chrpath-replacement-native"
EXTRANATIVEPATH += "chrpath-native"

do_install_append() {
        # TODO why does the cross compiler create /lib/lib folder?
	    rm -rf ${D}${prefix}/lib/lib/libiberty.a
        rm -rf ${D}${prefix}/lib/ldscripts
        # Remove rpath from the offending binaries
        chrpath -d ${D}${bindir}/${EXOTIC_TARGET_PREFIX}ar
        chrpath -d ${D}${bindir}/${EXOTIC_TARGET_PREFIX}ranlib
}
