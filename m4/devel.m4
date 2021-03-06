AC_DEFUN([adl_ENABLE_DEVEL],
[AC_ARG_ENABLE([devel],
	       [AC_HELP_STRING([--enable-devel],
			       [turn on useful developer options])])
 if test x"$enable_devel" = xyes; then
   enable_debug=${enable_debug-yes}
   enable_warnings=${enable_warnings-yes}
   enable_assert=${enable_assert-yes}
   enable_optimizations=${enable_optimizations--O}
 fi
])
