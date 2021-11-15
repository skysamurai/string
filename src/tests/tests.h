#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#include <check.h>

TCase* CreateMemmoveCase();
TCase* CreateMemsetCase();
TCase* CreateMemcpyCase();
TCase* CreateInsertCase();
TCase* CreateStrpbrkCase();
TCase* CreateStrrchrCase();
TCase* CreateMemcmpCase();
TCase* CreateMemchrCase();
TCase* CreateTrimCase();
TCase* CreateStrtokCase();
TCase* CreateSprintfCase();
TCase* CreateStrchrCase();
TCase* CreateStrcmpCase();
TCase* CreateStrncmpCase();
TCase* CreateStrcspnCase();
TCase* CreateStrcpyCase();
TCase* CreateStrncpyCase();
TCase* CreateStrcatCase();
TCase* CreateStrncatCase();
TCase* CreateStrlenCase();
TCase* CreateStrerrorCase();
TCase* CreateStrstrCase();
TCase* CreateStrspnCase();
TCase* CreateTolowerCase();
TCase* CreateToupperCase();

#endif  // SRC_TESTS_TESTS_H_
