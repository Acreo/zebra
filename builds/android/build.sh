#!/usr/bin/env bash
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################

# Use directory of current script as the build directory and working directory
cd "$( dirname "${BASH_SOURCE[0]}" )"
ANDROID_BUILD_DIR="$(pwd)"

# Get access to android_build functions and variables
source ${ANDROID_BUILD_DIR}/android_build_helper.sh

# Choose a C++ standard library implementation from the ndk
ANDROID_BUILD_CXXSTL="gnustl_shared_48"

# Set up android build environment and set ANDROID_BUILD_OPTS array
android_build_env
android_build_opts

# Use a temporary build directory
cache="/tmp/android_build/${TOOLCHAIN_NAME}"
rm -rf "${cache}"
mkdir -p "${cache}"

# Check for environment variable to clear the prefix and do a clean build
if [[ $ANDROID_BUILD_CLEAN ]]; then
    echo "Doing a clean build (removing previous build and depedencies)..."
    rm -rf "${ANDROID_BUILD_PREFIX}"/*
fi

##
# Make sure czmq is built and copy the prefix

(android_build_verify_so "libczmq.so" &> /dev/null) || {
    # Use a default value assuming the czmq project sits alongside this one
    test -z "$CZMQ_ROOT" && CZMQ_ROOT="$(cd ../../../czmq && pwd)"

    if [ ! -d "$CZMQ_ROOT" ]; then
        echo "The CZMQ_ROOT directory does not exist"
        echo "  ${CZMQ_ROOT}"
        exit 1
    fi

    (bash ${CZMQ_ROOT}/builds/android/build.sh) || exit 1
    UPSTREAM_PREFIX=${CZMQ_ROOT}/builds/android/prefix/${TOOLCHAIN_NAME}
    cp -r ${UPSTREAM_PREFIX}/* ${ANDROID_BUILD_PREFIX}
}

##
# Make sure libmicrohttpd is built and copy the prefix

(android_build_verify_so "libmicrohttpd.so" &> /dev/null) || {
    # Use a default value assuming the libmicrohttpd project sits alongside this one
    test -z "$LIBMICROHTTPD_ROOT" && LIBMICROHTTPD_ROOT="$(cd ../../../libmicrohttpd && pwd)"

    if [ ! -d "$LIBMICROHTTPD_ROOT" ]; then
        echo "The LIBMICROHTTPD_ROOT directory does not exist"
        echo "  ${LIBMICROHTTPD_ROOT}"
        exit 1
    fi

    (bash ${LIBMICROHTTPD_ROOT}/builds/android/build.sh) || exit 1
    UPSTREAM_PREFIX=${LIBMICROHTTPD_ROOT}/builds/android/prefix/${TOOLCHAIN_NAME}
    cp -r ${UPSTREAM_PREFIX}/* ${ANDROID_BUILD_PREFIX}
}

##
# Build zebra from local source

(android_build_verify_so "libzebra.so" "libczmq.so" "libmicrohttpd.so" &> /dev/null) || {
    rm -rf "${cache}/zebra"
    (cp -r ../.. "${cache}/zebra" && cd "${cache}/zebra" \
        && make clean && rm -f configure config.status)

    export LIBTOOL_EXTRA_LDFLAGS='-avoid-version'

    (cd "${cache}/zebra" && ./autogen.sh \
        && ./configure "${ANDROID_BUILD_OPTS[@]}" --without-documentation \
        && make -j 4 \
        && make install) || exit 1
}

##
# Verify shared libraries in prefix

android_build_verify_so "libczmq.so"
android_build_verify_so "libmicrohttpd.so"
android_build_verify_so "libzebra.so" "libczmq.so" "libmicrohttpd.so"
echo "Android build successful"
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
