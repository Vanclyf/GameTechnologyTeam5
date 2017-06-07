#include "Character.h"
#include "GameManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="Character"/> class.
/// This class is contained by the <see cref="LevelManager"/>, which manages all instances in the level. 
/// All characters in the game, NPC's and the player, inherit from this base class. 
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
Character::Character(Ogre::SceneNode* pMyNode, Ogre::Entity* pMyEntity) : _myNode(pMyNode), _myEntity(pMyEntity), _stats(0), _dirVec(0, 0, 0),
_movespeed(100), _runspeed(250), _rotationspeed(0.13), _isRunning(false), _currentLevel(1), _currentHealth(0), _currentStamina(0), _canAttack(true),
_attackDistance(20), _currAttackCooldown(0), _lightAttackCooldown(5.0f), _hitted(false), _totalHitTime(.5f), _weapon(0)
{
}

/// <summary>
/// Initializes this instance.
/// </summary>
/// <returns>False if something failed during initialization</returns>
bool Character::initialize()
{
	_isRunning = false;

	setUpStats();

	_currentHealth = _stats->GetStat(MaxHealth);
	_currentStamina = _stats->GetStat(MaxStamina);


	//show what is in the gear slots.
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	//FILE* fp;
	//freopen_s(&fp, "CONOUT$", "w", stdout);
	//std::cout << "I am a " << _myNode->getName() << " and I have a " << _weapon->getName() << std::endl;
	//fclose(fp);
	for (int i = 0; i < _armorEquipSlots.size(); i++)
	{
		std::cout << "gear slot " << i << " :" << _armorEquipSlots[i]->getName() << " Item Level: " << _armorEquipSlots[i]->getLevel() << std::endl;
	}
#endif

	return true;
}

/// <summary>
/// Updates the frame based on the specified pDeltatime.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
void Character::update(Ogre::Real pDeltatime)
{

	adjustStaminaOverTime(pDeltatime);

	if (_currAttackCooldown > 0) {
		_currAttackCooldown -= pDeltatime;
	}else {
		_canAttack = true;
	}

	if (_hitTime > 0) {
		_hitTime -= pDeltatime;
		return;
	}
	else {
		_hitted = false;
	}

	_myNode->translate(_dirVec * getSpeed() * pDeltatime, Ogre::Node::TS_LOCAL);

}

//TODO: these methods should be generic
/// <summary>
/// Finds the target.
/// </summary>
/// <param name="pPossibleTargets">The possible targets vector.</param>
void Character::findTarget(std::vector<Character*> pPossibleTargets)
{
	for (int i = 0; i < pPossibleTargets.size(); ++i) {
		if (getPosition().distance(pPossibleTargets[i]->getPosition()) < _attackDistance) {
			//TODO: check for allignment with the other character
			_target = pPossibleTargets[i];
			return;
		}
	}

	_target = nullptr;
}

/// <summary>
/// Sets up stats to default values.
/// </summary>
/// <returns></returns>
bool Character::setUpStats()
{
	std::vector<Stat> tempStats;

	int statNr = (int)StatType::AMOUNT_OF_TYPES;

	for (int i = 0; i < statNr; ++i)
	{
		Stat tempStat((StatType)i, 0);

		tempStats.push_back(tempStat);
	}

	// Set all key _stats. 
	tempStats.at((int)Strength).value = 8;
	tempStats.at((int)Dexterity).value = 8;
	tempStats.at((int)Intelligence).value = 8;
	tempStats.at((int)Vitality).value = 8;

	// Add 2 to the prim stat of player class. 
	tempStats.at((int)Strength).value += 2;

	tempStats.at((int)Armor).value = 18;
	tempStats.at((int)Damage).value = 2;
	tempStats.at((int)Resistance).value = 1;
	tempStats.at((int)MaxHealth).value = 40;
	tempStats.at((int)MaxStamina).value = 125;
	tempStats.at((int)StaminaRegen).value = 4;
	tempStats.at((int)AttackSpeed).value = 0;

	_stats = new CharacterStats(tempStats);

	return true;
}

/// <summary>
/// Set the direction vector of the character with the specified vector.
/// </summary>
/// <param name="pMoveVec">The new direction vector.</param>
void Character::move(Ogre::Vector3& pMoveVec)
{
	_dirVec = pMoveVec;
}

bool Character::lightAttack()
{
	if (!_canAttack || _hitted)
	{
		return false;
	}

	return true;
}
/// <summary>
/// Adjusts the health.
/// </summary>
/// <param name="pAdjust">The adjustment of health.</param>
/// <returns>False if the character runs out of health.</returns>
bool Character::adjustHealth(float pAdjust)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("I got hit... %f \n", _currentHealth);
	fclose(fp);
#endif

	_hitTime = _totalHitTime;
	_hitted = true;

	if ((_currentHealth -= pAdjust) <= 0)
	{
		die();
		return false;
	}

	return true;
}

/// <summary>
/// Adjusts the stamina over time.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
/// <returns>False if the character runs out of statina.</returns>
bool Character::adjustStaminaOverTime(Ogre::Real pDeltaTime)
{
	Ogre::Real adjust = _isRunning ? -_stats->GetStat(StaminaRegen) / 2 : _stats->GetStat(MaxStamina);

	adjust *= pDeltaTime;

	if ((_currentStamina += adjust) <= 0)
	{
		toggleRun(false);

		return false;
	}
	else if ((_currentStamina += adjust) >= _stats->GetStat(MaxStamina))
	{
		_currentStamina = _stats->GetStat(MaxStamina);
	}

	return true;
}

/// <summary>
/// Adjusts the stamina.
/// </summary>
/// <param name="pAdjust">The adjustment in stamina.</param>
/// <returns>False if the character runs out of statina.</returns>
bool Character::adjustStamina(float pAdjust)
{
	if ((_currentStamina += pAdjust) <= 0)
	{
		// attack should be canceled
		return false;
	}
	else if ((_currentStamina += pAdjust) >= _stats->GetStat(MaxStamina))
	{
		_currentStamina = _stats->GetStat(MaxStamina);
	}

	return true;
}

/// <summary>
/// Character dies.
/// </summary>
void Character::die()
{
	GameManager::getSingletonPtr()->getUIManager()->setPickUpEventLogText();
	Player *player = GameManager::getSingletonPtr()->getLevelManager()->getPlayer();
	_myNode->setVisible(false);

	switch(getTypeNpc())
	{
	case NpcType::Good:
		player->adjustKarma(-10);		
		break;
	case NpcType::Bad:
		player->adjustKarma(10);
		break;
	case NpcType::Princess:
		player->adjustKarma(-100);
		break;
	}
	player->gainXP(10);
	//TODO: actually destroy the node and its children
	//_myNode->removeAndDestroyAllChildren();
	//GameManager::getSingletonPtr()->getSceneManager()->destroySceneNode(_myNode);
}

//TODO: call this from the init from NPC's and from the inventory for the player
//for now: standard weapon assigned in init
void Character::setHand(WeaponInstance* pWeapon) {
	if(_weapon != nullptr) {
		removeFromHand();
	}

	_weapon = pWeapon;

	//TODO: set the weapon entity as child of the character and set it to visible
}

void Character::removeFromHand() {
	//TODO: un-parent the weapon

	_weapon = NULL;
}

/// <summary>
/// Sets the armor to a equipment slot.
/// </summary>
/// <param name="pArmor">The armor instance that needs to be equiped.</param>
void Character::setEquipmentSlot(ArmorInstance* pArmor)
{
	bool duplicate = false;

	if (pArmor->getLevel() <= _currentLevel)
	{
		for (int i = 0; i < _armorEquipSlots.size(); i++)
		{
			if (pArmor->getInfo()->getSlotType() == _armorEquipSlots[i]->getInfo()->getSlotType())
			{
				swapEquipmentSlot(pArmor, i);
				duplicate = true;
			}
		}
		if (!duplicate)
		{
			std::vector<ArmorInstance*> armors = _armorEquipSlots;
			armors.push_back(pArmor);
			_armorEquipSlots = armors;
			addStats(reinterpret_cast<EquipmentInstance*>(pArmor));

			#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				FILE* fp;
				freopen_s(&fp, "CONOUT$", "w", stdout);
				std::cout << "I equiped the following item: " << pArmor->getInfo()->getName() << "in Slot: " << pArmor->getInfo()->getSlotType() << std::endl;
				fclose(fp);
			#endif
		}

	}
	else
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		std::cout << "Cannot equip item too high level: " << reinterpret_cast<EquipmentInstance*>(pArmor)->getLevel() << " current level: " << GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getLevel() << std::endl;
		fclose(fp);
#endif

	}
}

/// <summary>
/// Sets the weapon to its equipment slot.
/// </summary>
/// <param name="pWeapon">The weaponn instance that needs to be equiped.</param>
void Character::setEquipmentSlot(WeaponInstance* pWeapon)
{
	int oneHandedWeaponCount = 0;
	bool duplicate = false;
	//check if the levelrequirment is met.
	if (pWeapon->getLevel() <= _currentLevel)
	{
		//check if the weapon type is twohanded
		if(pWeapon->getInfo()->getHandedType() == 1)
		{
			swapEquipmentSlot(pWeapon, 0);
		}
		else
		{
			for (int i = 0; i < _weaponEquipSlots.size(); i++)
			{
				//if a slot contains a onehanded weapon it adds one to the weaponcount
				if (_weaponEquipSlots[i]->getInfo()->getHandedType() == 0)
				{
					oneHandedWeaponCount++;
					//if the weaponcount is equal to 2 the max ammount of onehanded weapons is reached. 
					if (oneHandedWeaponCount == 2)
					{
						//swapEquipmentSlot(pWeapon, i);
						duplicate = true;
					}
				}
			}
			//if no swap is needed add the weapon to the equipslots.
			if (!duplicate)
			{
				std::vector<WeaponInstance*> weapons = _weaponEquipSlots;
				weapons.push_back(pWeapon);
				_weaponEquipSlots = weapons;
				setHand(pWeapon);
				addStats(reinterpret_cast<EquipmentInstance*>(pWeapon));

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				FILE* fp;
				freopen_s(&fp, "CONOUT$", "w", stdout);
				std::cout << "I equiped the following item: " << pWeapon->getInfo()->getName() << "in Slot: " << pWeapon->getInfo()->getHandedType() << std::endl;
				fclose(fp);
#endif
			}
		}

	}
	else
	{
		#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			FILE* fp;
			freopen_s(&fp, "CONOUT$", "w", stdout);
			std::cout << "Cannot equip item too high level: " << reinterpret_cast<EquipmentInstance*>(pWeapon)->getLevel() << " current level: " << GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getLevel() << std::endl;
			fclose(fp);
		#endif

	}
}

/// <summary>
/// Replaces the old item in the appropriate equipment slot.
/// </summary>
/// <param name="pArmor">The armor instance that needs to be equiped.</param>
/// <param name="pDuplicate">The duplicate is the index of the duplicate item which has to be swaped.</param>
void Character::swapEquipmentSlot(ArmorInstance* pArmor, int pDuplicate)
{
	//you can address the old item by _armorEquipSlots[pDuplicate]
	removeStats(reinterpret_cast<EquipmentInstance*>(_armorEquipSlots[pDuplicate]));
	addStats(reinterpret_cast<EquipmentInstance*>(pArmor));
	
	///Ignore this ATM work in progress.
	/*Ogre::Entity* itemEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("sphere.mesh");
	GameManager::getSingletonPtr()->addItemNumber();
	int itemnumber = GameManager::getSingleton().getItemNumber();
	std::stringstream nodename("_itemNode");
	nodename << itemnumber << "_" << "0";
	Ogre::SceneNode* itemNode = GameManager::getSingletonPtr()->getLevelManager()->getLevelNode()->createChildSceneNode(nodename.str());
	itemNode->createChildSceneNode()->attachObject(itemEntity);
	itemNode->setPosition(GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition());
	itemNode->setScale(.2, .5, .2);
	reinterpret_cast<ItemInstance*>(_armorEquipSlots[pDuplicate])->setNodeAndEntity(itemNode, itemEntity);
	reinterpret_cast<ItemInstance*>(_armorEquipSlots[pDuplicate])->id = GameManager::getSingletonPtr()->getLevelManager()->subscribeItemInstance(reinterpret_cast<ItemInstance*>(_armorEquipSlots[pDuplicate]));*/

	_armorEquipSlots[pDuplicate] = pArmor;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "I swapped the following item: " << _armorEquipSlots[pDuplicate]->getInfo()->getName() << "with: " << pArmor->getInfo()->getName() << " in Slot: " << pArmor->getInfo()->getSlotType() << std::endl;
	fclose(fp);
#endif
}

/// <summary>
/// Swaps weapons in the weapon slot.
/// </summary>
/// <param name="pWeapon">The new weapon.</param>
/// <param name="pDuplicate">The index of the duplicate weapon.</param>
void Character::swapEquipmentSlot(WeaponInstance* pWeapon, int pDuplicate)
{
	//if it is an twohanded weapon remove all the weapons from the list and add the new one.
	if(pWeapon->getInfo()->getHandedType() == 1)
	{
		//remove all the stats of all weapons stored in the weaponEquipSlots.
		for (int i = 0; i < _weaponEquipSlots.size(); i++)
		{
			removeStats(reinterpret_cast<EquipmentInstance*>(_weaponEquipSlots[pDuplicate]));
		}
		addStats(reinterpret_cast<EquipmentInstance*>(pWeapon));
		_weaponEquipSlots.clear();
		std::vector<WeaponInstance*> weapons = _weaponEquipSlots;
		weapons.push_back(pWeapon);
		setHand(pWeapon);

		#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				FILE* fp;
				freopen_s(&fp, "CONOUT$", "w", stdout);
				std::cout << "I swapped the following weapon: " << _weaponEquipSlots[pDuplicate]->getInfo()->getName() << "with: " << pWeapon->getInfo()->getName() << " in Slot: " << pWeapon->getInfo()->getHandedType() << std::endl;
				fclose(fp);
		#endif
	}
	else
	{
		removeStats(reinterpret_cast<EquipmentInstance*>(_weaponEquipSlots[pDuplicate]));
		addStats(reinterpret_cast<EquipmentInstance*>(pWeapon));
		_weaponEquipSlots[pDuplicate] = pWeapon;
		setHand(pWeapon);

		#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				FILE* fp;
				freopen_s(&fp, "CONOUT$", "w", stdout);
				std::cout << "I swapped the following weapon: " << _armorEquipSlots[pDuplicate]->getInfo()->getName() << "with: " << pWeapon->getInfo()->getName() << " in Slot: " << pWeapon->getInfo()->getHandedType() << std::endl;
				fclose(fp);
		#endif
	}
}

/// <summary>
/// When an item instance needs to be equiped first the equipment type should be found,
/// then sends the item instance to the appropriate equipe function equipment slot.
/// </summary>
/// <param name="pItem">The item instance that should be checked and equiped.</param>
void Character::setEquipmentSlot(ItemInstance* pItem)
{
	//check if pItem is of type equipment which is 2.
	if (pItem->getInfo()->getItemType() == 2)
	{
		//checks if the level of the item is less or equal to character level.
		if (reinterpret_cast<EquipmentInstance*>(pItem)->getLevel() <= _currentLevel)
		{
			//checks which type of equpment it is, 0 = weapon, 1 = armor, 2 = jewelry.
			if (reinterpret_cast<EquipmentInstance*>(pItem)->getType() == 0)
			{
				WeaponInstance* tempWeapon = reinterpret_cast<WeaponInstance*>(pItem);
				setEquipmentSlot(reinterpret_cast<WeaponInstance*>(pItem));
			}
			else if (reinterpret_cast<EquipmentInstance*>(pItem)->getType() == 1)
			{
				ArmorInstance* tempArmor = reinterpret_cast<ArmorInstance*>(pItem);
				bool noDuplicate = true;
				for (int i = 0; i < _armorEquipSlots.size(); i++)
				{
					if (tempArmor->getInfo()->getSlotType() == _armorEquipSlots[i]->getInfo()->getSlotType())
					{
						swapEquipmentSlot(reinterpret_cast<ArmorInstance*>(pItem), i);
						noDuplicate = false;
					}
				}
				if (noDuplicate)
				{
					setEquipmentSlot(reinterpret_cast<ArmorInstance*>(pItem));
					addStats(reinterpret_cast<EquipmentInstance*>(pItem));
				}
			}
			else
			{
				//TODO: jewelrey slots for equipment.
			}

		}
		else
		{
			#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				FILE* fp;
				freopen_s(&fp, "CONOUT$", "w", stdout);
				std::cout << "Cannot equip item too high level: " << reinterpret_cast<EquipmentInstance*>(pItem)->getLevel() << " current level: " << GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getLevel() << std::endl;
				fclose(fp);
			#endif

		}
	}
}

/// <summary>
/// Adds the stats of the appropriate item to the character total stats.
/// </summary>
/// <param name="pItem">The item of which the stats should be added.</param>
void Character::addStats(EquipmentInstance* pItem)
{
	std::vector<Stat> tempStats;
	switch(pItem->getType())
	{
	case 0:
		//weapon
		tempStats = _stats->GetStats();
		for (int i = 0; i < reinterpret_cast<WeaponInstance*>(pItem)->getBaseStats().size(); i++)
		{
			tempStats.at((int)i).value += reinterpret_cast<WeaponInstance*>(pItem)->getBaseStats().at((int)i)->value;
			_stats->GetStats().at((int)i) = tempStats.at((int)i);
		}

		break;
	case 1:
		//armor
		tempStats = _stats->GetStats();
		for (int i = 0; i < reinterpret_cast<ArmorInstance*>(pItem)->getBaseStats().size(); i++)
		{
			tempStats.at((int)i).value += reinterpret_cast<ArmorInstance*>(pItem)->getBaseStats().at((int)i)->value;
			_stats->GetStats().at((int)i) = tempStats.at((int)i);
		}

		break;
	}
}

/// <summary>
/// Removes the stats of the item being removed.
/// </summary>
/// <param name="pItem">The item of which the stats should be removed.</param>
void Character::removeStats(EquipmentInstance* pItem)
{
	std::vector<Stat> tempStats;
	switch (pItem->getType())
	{
	case 0:
		//weapon
		tempStats = _stats->GetStats();
		for (int i = 0; i < reinterpret_cast<WeaponInstance*>(pItem)->getBaseStats().size(); i++)
		{
			tempStats.at((int)i).value -= reinterpret_cast<WeaponInstance*>(pItem)->getBaseStats().at((int)i)->value;
			_stats->GetStats().at((int)i) = tempStats.at((int)i);
		}

		break;
	case 1:
		//armor
		tempStats = _stats->GetStats();
		for (int i = 0; i < reinterpret_cast<ArmorInstance*>(pItem)->getBaseStats().size(); i++)
		{
			tempStats.at((int)i).value -= reinterpret_cast<ArmorInstance*>(pItem)->getBaseStats().at((int)i)->value;
			_stats->GetStats().at((int)i) = tempStats.at((int)i);
		}
		
		break;
	}
}