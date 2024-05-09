cmake_minimum_required(VERSION 3.28)

find_package(Zephyr REQUIRED)
project(lidar_test)

target_sources(app PRIVATE src/main.c)
