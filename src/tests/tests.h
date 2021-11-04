#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#include <check.h>

TCase* CreateStrpbrkCase();
TCase* CreateStrrchrCase();
TCase* CreateMemcmpCase();

TCase* CreateStrchrCase();
TCase* CreateStrcmpCase();
TCase* CreateStrncmpCase();
TCase* CreateStrcatCase();
TCase* CreateStrncatCase();

#endif  // SRC_TESTS_TESTS_H_
