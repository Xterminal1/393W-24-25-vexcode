#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

// autons
void auto_blue_right();
void auto_red_left();
void auto_red_right();
void auto_blue_left();
void auto_skills();
void test();

void redLeft();
void redRight();
void blueRight();
void blueLeft();
void skills();

// test autons
void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void holonomic_odom_test();