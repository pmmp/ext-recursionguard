# ext-recursionguard
![CI](https://github.com/pmmp/ext-recursionguard/workflows/CI/badge.svg)

Lightweight PHP extension to hard-cap function call depth.

## Features
This extension will throw an `Error` if the function call stack reaches a depth of `256` calls. This is currently non-configurable, but usable for most cases.

## Configuration
- `recursionguard.enabled` (default `1`): Controls whether the extension will guard for recursions even when loaded (useful for static builds).

## Motivation
Recursion errors can be difficult to debug because they cause PHP to crash without any stack trace when something overrides `zend_execute_ex`. Therefore, it's desirable to have this barf at a hard limit instead of segfaulting without apparent reason.

However, the only way to do this before now was the `xdebug` extension, which causes huge performance degradation and as such is unsuitable for production. This extension keeps to the point, causing a hit of only 10% extra function call overhead, versus `xdebug`'s 2000+% overhead. This additional overhead becomes insignicant outside of synthetic benchmarks.
