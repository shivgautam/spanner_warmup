PHP_ARG_ENABLE(spanner_warmup, for spanner warmup support,
[  --enable-spanner_warmup             Include spanner warmup support])

if test "$PHP_SPANNER_WARMUP" != "no"; then

  LIBNAME=php
  SPANNER_WARMUP_DIR=<path to the php source dir>

  LIBSYMBOL=php_embed_init

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SPANNER_WARMUP_DIR/$PHP_LIBDIR, SPANNER_WARMUP_SHARED_LIBADD)
    AC_DEFINE(HAVE_SPANNER_WARMUPLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong spanner_warmup lib version or lib not found])
  ],[
    -L$SPANNER_WARMUP_DIR/$PHP_LIBDIR -lm
  ])

  PHP_SUBST(SPANNER_WARMUP_SHARED_LIBADD)
  PHP_REQUIRE_CXX()
  PHP_NEW_EXTENSION(spanner_warmup, spanner_warmup.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
