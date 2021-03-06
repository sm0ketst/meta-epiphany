##################################################################
# Part two of this refactoring will move this file to
# exotic-gcc-4.8.inc
# The SRC_URI will point to official gcc-4.8 source and
# the following will override that content!
##################################################################

require epiphany-elf-gcc-common.inc

# Third digit in PV should be incremented after a minor release

PV = "4.8.2"

# BINV should be incremented to a revision after a minor gcc release

BINV = "4.8.2"

FILESEXTRAPATHS =. "${FILE_DIRNAME}/epiphany-elf-gcc-4.8:"

DEPENDS =+ "mpfr gmp libmpc zlib"
NATIVEDEPS = "mpfr-native gmp-native libmpc-native zlib-native"

LICENSE = "GPL-3.0-with-GCC-exception & GPLv3"

LIC_FILES_CHKSUM = "\
    file://COPYING;md5=59530bdf33659b29e73d4adb9f9f6552 \
    file://COPYING3;md5=d32239bcb673463ab874e80d47fae504 \
    file://COPYING3.LIB;md5=6a6a8e020838b23406c81b19c1d46df6 \
    file://COPYING.LIB;md5=2d5025d4aa3495befef8f17206a5b0a1 \
    file://COPYING.RUNTIME;md5=fe60d87048567d4fe8c8a0ed2448bcc8 \
"

EGCCBRANCH = "epiphany-gcc-4.8-software-cache"
SRC_URI = " git://github.com/adapteva/epiphany-gcc.git;branch=${EGCCBRANCH};name=${EGCCBRANCH} "

SRC_URI += " \
    file://0002-uclibc-conf.patch \
    file://0003-gcc-uclibc-locale-ctype_touplow_t.patch \
    file://0004-uclibc-locale.patch \
    file://0005-uclibc-locale-no__x.patch \
    file://0006-uclibc-locale-wchar_fix.patch \
    file://0007-uclibc-locale-update.patch \
    file://0008-missing-execinfo_h.patch \
    file://0009-c99-snprintf.patch \
    file://0010-c99-complex-ugly-hack.patch \
    file://0011-index_macro.patch \
    file://0012-libmudflap-susv3-legacy.patch \
    file://0013-libstdc-namespace.patch \
    file://0014-sh-pr24836.patch \
    file://0015-arm-Use-TARGET_ENDIAN_OPTION-for-determining-MULTILI.patch \
    file://0016-gcc-poison-system-directories.patch \
    file://0017-gcc-poison-dir-extend.patch \
    file://0018-gcc-4.3.3-SYSROOT_CFLAGS_FOR_TARGET.patch \
    file://0019-64-bit-multilib-hack.patch \
    file://0020-optional-libstdc.patch \
    file://0021-gcc-disable-MASK_RELAX_PIC_CALLS-bit.patch \
    file://0022-COLLECT_GCC_OPTIONS.patch \
    file://0023-Use-the-defaults.h-in-B-instead-of-S-and-t-oe-in-B.patch \
    file://0024-PR-target-32219.patch \
    file://0025-fortran-cross-compile-hack.patch \
    file://0026-libgcc-sjlj-check.patch \
    file://0027-cpp-honor-sysroot.patch \
    file://0028-MIPS64-Default-to-N64-ABI.patch \
    file://0029-Define-GLIBC_DYNAMIC_LINKER-and-UCLIBC_DYNAMIC_LINKE.patch \
    file://0030-gcc-Fix-argument-list-too-long-error.patch \
    file://0031-Disable-sdt.patch \
    file://0032-libtool.patch \
    file://0033-gcc-armv4-pass-fix-v4bx-to-linker-to-support-EABI.patch \
    file://0034-Use-the-multilib-config-files-from-B-instead-of-usin.patch \
    file://0035-wcast-qual-PR-55383.patch \
    file://0038-gcc-4.8-build-args.patch \
    file://0039-gcc-4.8-PR57717.patch \
    file://0040-fix-g++-sysroot.patch \
    file://0041-libtool-avoid-libdir.patch \
    file://0042-pr57748.patch \
    file://0043-cpp.patch \
    file://0044-gengtypes.patch \
    file://0045-gcc-4.8-PR57717-PowerPC-E500v2.patch \
    file://0046-libatomic-deptracking.patch \
    file://0047-repomembug.patch \
    file://0048-PR58854_fix_arm_apcs_epilogue.patch \
    file://0049-Enable-SPE-AltiVec-generation-on-powepc-linux-target.patch \
    file://0052-PR-rtl-optimization-61801.patch \
    file://target-gcc-includedir.patch \
    "

#    file://0050-PR-target-58595.patch \
#

# Tag: epiphany-gcc-esdk-2014.11
SRCREV = "005a35955747a2da8a48afdbbe00d80a12e41dde"

# Language Overrides
FORTRAN = ""
JAVA = ""

EXTRA_OECONF_INITIAL = "\
    --disable-libmudflap \
    --disable-libgomp \
    --disable-libssp \
    --disable-libquadmath \
    --disable-lto \
    --disable-plugin \
    --enable-decimal-float=no \
"

EXTRA_OECONF_INTERMEDIATE = "\
    --disable-libmudflap \
    --disable-libgomp \
    --disable-libquadmath \
    --disable-lto \
    --disable-plugin \
    --disable-libssp \
"

EXTRA_OECONF_PATHS = "\
    --with-libtool-sysroot=${STAGING_DIR_HOST} \
    --with-native-system-header-dir=${STAGING_DIR_TARGET}${target_includedir} \
    --with-gxx-include-dir=${STAGING_DIR_TARGET}${target_includedir}/c++/${BINV} \ 
    --with-sysroot=${STAGING_DIR_TARGET} \ 
    --with-build-sysroot=${STAGING_DIR_TARGET} \
"

