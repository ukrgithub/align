AC_INIT([align], [0.0], [https://github.com/ukrgithub/align])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])
AM_SILENT_RULES([yes])
AC_PROG_CC

LT_INIT

AC_CONFIG_FILES([
        Makefile
        src/Makefile
        test/Makefile
    ])

CFLAGS="$CFLAGS -Wall -Wextra"
CPPFLAGS="$CPPFLAGS -Wall -Wextra"

AC_OUTPUT
