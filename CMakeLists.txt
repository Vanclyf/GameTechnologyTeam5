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
        ./Diabro/Diabro/BasicPrincess.h
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
	./Diabro/Diabro/CharacterSpawner.h
	./Diabro/Diabro/WeaponInstance.h
	./Diabro/Diabro/ItemContainer.h
	./Diabro/Diabro/ItemManager.h
	./Diabro/Diabro/ItemGenerator.h
	./Diabro/Diabro/LevelGenerator.h
	./Diabro/Diabro/Zone.h
	./Diabro/Diabro/SoundManager.h
	./Diabro/Diabro/City.h
	./Diabro/Diabro/State.h
	./Diabro/Diabro/GenericFSM.h
	./Diabro/Diabro/TestFSM.h
	./Diabro/Diabro/Needs.h
	./Diabro/Diabro/BaseQuestItem.h
	./Diabro/Diabro/QuestContentManager.h 
	./Diabro/Diabro/QuestItem.h 
	./Diabro/Diabro/QuestItemContainer.h 
	./Diabro/Diabro/QuestItemGenerator.h
	./Diabro/Diabro/tinyxml2.h
	./Diabro/Diabro/ArmorInstance.h
	./Diabro/Diabro/BaseArmor.h
	./Diabro/Diabro/BuildingType.h
	./Diabro/Diabro/CityManager.h
        
)
 
set(SRCS
	./Diabro/Diabro/SoundManager.cpp
	./Diabro/Diabro/BaseApplication.cpp
	./Diabro/Diabro/GameManager.cpp
	./Diabro/Diabro/Player.cpp
	./Diabro/Diabro/Npc.cpp
	./Diabro/Diabro/LevelManager.cpp
	./Diabro/Diabro/BaseItem.cpp
	./Diabro/Diabro/BasicEnemy.cpp
        ./Diabro/Diabro/BasicPrincess.cpp
	./Diabro/Diabro/ItemInstance.cpp
	./Diabro/Diabro/Character.cpp
	./Diabro/Diabro/BaseEquipment.cpp
	./Diabro/Diabro/FloatRange.cpp
	./Diabro/Diabro/EquimentInstance.cpp
	./Diabro/Diabro/BaseWeapon.cpp
	./Diabro/Diabro/BaseNpc.cpp
	./Diabro/Diabro/Npc.cpp
	./Diabro/Diabro/UIManager.cpp
	./Diabro/Diabro/CharacterSpawner.cpp
	./Diabro/Diabro/WeaponInstance.cpp
	./Diabro/Diabro/ItemContainer.cpp
	./Diabro/Diabro/ItemManager.cpp
	./Diabro/Diabro/ItemGenerator.cpp
	./Diabro/Diabro/QuestContentManager.cpp
	./Diabro/Diabro/QuestItemContainer.cpp
	./Diabro/Diabro/QuestItemGenerator.cpp
	./Diabro/Diabro/LevelGenerator.cpp
	./Diabro/Diabro/Zone.cpp
	./Diabro/Diabro/City.cpp
	./Diabro/Diabro/tinyxml2.cpp
	./Diabro/Diabro/ArmorInstance.cpp
	./Diabro/Diabro/BaseArmor.cpp
	./Diabro/Diabro/BuildingType.cpp
	./Diabro/Diabro/CityManager.cpp

)
 
include("tools/cmake/common.cmake") 
