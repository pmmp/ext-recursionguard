PHP_ARG_ENABLE(recursionguard, whether to enable recursionguard support,
[  --enable-recursionguard           Enable recursionguard support])

if test "$PHP_RECURSIONGUARD" != "no"; then
  PHP_NEW_EXTENSION(recursionguard, recursionguard.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
