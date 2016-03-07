@ECHO OFF
:-  configure.bat creates platform.h and configures the build process
:-  You MUST run this before building via msbuild or VisualStudio.

IF %1.==--help. (
    ECHO Syntax: configure [ switch ]
    ECHO    --help                  show this help
    ECHO    --enable-drafts         from zip package, enables DRAFT API
    ECHO    --disable-drafts        from git repository, disables DRAFT API
    ECHO    --without-zebra_selftest  do not build zebra_selftest.exe
    GOTO END
)
ECHO Configuring zebra...

ECHO //  Generated by configure.bat> platform.h
ECHO. >> platform.h
ECHO #ifndef __PLATFORM_H_INCLUDED__>> platform.h
ECHO #define __PLATFORM_H_INCLUDED__>> platform.h
ECHO. >> platform.h
ECHO #define ZEBRA_HAVE_WINDOWS 1>> platform.h

:-  Check for dependencies
IF EXIST "..\..\..\libzmq" (
    ECHO Building with libzmq
    ECHO #define HAVE_LIBZMQ 1>> platform.h
) ELSE (
    ECHO Building without libzmq
    ECHO zebra cannot build without libzmq
    ECHO Please clone https://github.com/zeromq/libzmq, and then configure & build
    ECHO TODO: resolve this problem automatically.
    GOTO error
)
IF EXIST "..\..\..\czmq" (
    ECHO Building with czmq
    ECHO #define HAVE_CZMQ 1>> platform.h
) ELSE (
    ECHO Building without czmq
    ECHO zebra cannot build without czmq
    ECHO Please clone https://github.com/zeromq/czmq, and then configure & build
    ECHO TODO: resolve this problem automatically.
    GOTO error
)
IF EXIST "..\..\..\libmicrohttpd" (
    ECHO Building with libmicrohttpd
    ECHO #define HAVE_LIBMICROHTTPD 1>> platform.h
) ELSE (
    ECHO Building without libmicrohttpd
    ECHO zebra cannot build without libmicrohttpd
    ECHO TODO: resolve this problem automatically.
    GOTO error
)
IF EXIST "..\..\..\libcurl" (
    ECHO Building with libcurl
    ECHO #define HAVE_LIBCURL 1>> platform.h
) ELSE (
    ECHO Building without libcurl
    ECHO #undef HAVE_LIBCURL>> platform.h
)
IF EXIST "..\..\..\libsodium" (
    ECHO Building with libsodium
    ECHO #define HAVE_LIBSODIUM 1>> platform.h
) ELSE (
    ECHO Building without libsodium
    ECHO #undef HAVE_LIBSODIUM>> platform.h
)

:-  Check if we want to build the draft API
IF NOT EXIST "..\..\.git" GOTO no_draft
    ECHO Building with draft API (stable + legacy + draft API)
    ECHO //  Provide draft classes and methods>>platform.h
    ECHO #define ZEBRA_BUILD_DRAFT_API 1>>platform.h
    GOTO end_draft
:no_draft
    ECHO Building without draft API (stable + legacy API)
    ECHO #undef ZEBRA_BUILD_DRAFT_API 1>>platform.h
:end_draft
ECHO. >> platform.h
ECHO #endif>> platform.h
:error
