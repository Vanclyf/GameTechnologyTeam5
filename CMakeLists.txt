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
cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)
	
set(APP "Diabro")
 
set(HDRS
	./Diabro/Diabro/BaseApplication.h
	./Diabro/Diabro/GameManager.h
	./Diabro/Diabro/Player.h
	./Diabro/Diabro/Npc.h
	./Diabro/Diabro/CharacterStats.h
	./Diabro/Diabro/LevelManager.h
	./Diabro/Diabro/BasicEnemy.h
	./Diabro/Diabro/Character.h
	./Diabro/Diabro/BaseItem.h
	./Diabro/Diabro/ItemInstance.h
	./Diabro/Diabro/BaseEquipment.h
	./Diabro/Diabro/StatRange.h
	./Diabro/Diabro/FloatRange.h
	./Diabro/Diabro/Affix.h
	./Diabro/Diabro/Modifier.h
	./Diabro/Diabro/EquimentInstance.h
	./Diabro/Diabro/BaseWeapon.h
	./Diabro/Diabro/BaseNpc.h
	./Diabro/Diabro/UIManager.h
)
 
set(SRCS
	./Diabro/Diabro/BaseApplication.cpp
	./Diabro/Diabro/GameManager.cpp
	./Diabro/Diabro/Player.cpp
	./Diabro/Diabro/Npc.cpp
	./Diabro/Diabro/LevelManager.cpp
	./Diabro/Diabro/BaseItem.cpp
	./Diabro/Diabro/BasicEnemy.cpp
	./Diabro/Diabro/ItemInstance.cpp
	./Diabro/Diabro/Character.cpp
	./Diabro/Diabro/BaseEquipment.cpp
	./Diabro/Diabro/FloatRange.cpp
	./Diabro/Diabro/EquimentInstance.cpp
	./Diabro/Diabro/BaseWeapon.cpp
	./Diabro/Diabro/BaseNpc.cpp
	./Diabro/Diabro/Npc.cpp
	./Diabro/Diabro/UIManager.cpp
)
 
include("tools/cmake/common.cmake") 
