PHP_ARG_ENABLE(gcp_spanner_warmup, for spanner warmup support,
[  --enable-gcp_spanner_warmup             Include spanner warmup support])

if test "$PHP_GCP_SPANNER_WARMUP" != "no"; then

  LIBNAME=libs
  LIBSYMBOL=php_embed_init

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GCP_SPANNER_WARMUP_DIR/$PHP_LIBDIR, GCP_SPANNER_WARMUP_SHARED_LIBADD)
    AC_DEFINE(HAVE_GCP_SPANNER_WARMUPLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong gcp_spanner_warmup lib version or lib not found])
  ],[
    -L$GCP_SPANNER_WARMUP_DIR/$PHP_LIBDIR -lm
  ])

  PHP_SUBST(GCP_SPANNER_WARMUP_SHARED_LIBADD)
  PHP_REQUIRE_CXX()
  PHP_NEW_EXTENSION(gcp_spanner_warmup, gcp_spanner_warmup.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
