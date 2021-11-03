#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#include <check.h>

TCase* CreateStrpbrkCase();
TCase* CreateStrrchrCase();
TCase* CreateMemcmpCase();
TCase* CreateStrcspnCase();
TCase* CreateMemchrCase();
TCase* CreateTrimCase();
TCase* CreateStrtokCase();
TCase* CreateSprintfCase();

#endif  // SRC_TESTS_TESTS_H_