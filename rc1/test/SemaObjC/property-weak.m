// RUN: %clang_cc1 -triple i386-apple-darwin9 -fsyntax-only -verify %s

@interface foo
@property(nonatomic) int foo __attribute__((weak_import));
@end
