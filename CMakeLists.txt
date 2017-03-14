#/*
#-----------------------------------------------------------------------------
#Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
#
#This source file is part of the
#   ___                 __    __ _ _    _ 
#  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
# //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
#/ \_// (_| | | |  __/  \  /\  /| |   <| |
#\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
#      |___/                              
#      Tutorial Framework
#      http://www.ogre3d.org/tikiwiki/
#-----------------------------------------------------------------------------
#*/
cmake_minimum_required(VERSION 2.6)

set(APP "OgreApp")
 
set(HDRS
	./Diabro/Diabro/Player.h
	./Diabro/Diabro/LevelManager.h
	./Diabro/Diabro/GameManager.h
	./Diabro/Diabro/CharacterStats.h
	./Diabro/Diabro/BaseApplication.h
)
 
set(SRCS
	./Diabro/Diabro/Player.cpp
	./Diabro/Diabro/LevelManager.cpp
	./Diabro/Diabro/GameManager.cpp
	./Diabro/Diabro/BaseApplication.cpp
)
 
include("tools/cmake/common.cmake") 
