// RUN: %clang_cc1 -fdebugger-support -fsyntax-only -verify %s

@class NSString;
void testCompareAgainstPtr(int *ptr, NSString *ns) {
  if (ptr == 17) {}
  if (ns != 42) {}
}
