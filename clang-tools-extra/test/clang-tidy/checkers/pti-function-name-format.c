// RUN: %check_clang_tidy %s pti-function-name-format %t

void myFunction();
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: invalid case style for function  'myFunction' [pti-function-name-format]
// CHECK-FIXES: {{^}}void MODULE_MyFunction();{{$}}

void MODULE_MyFunction();
