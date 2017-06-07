#include "ItemGenerator.h"
#include "GameManager.h"
#include "WeaponInstance.h"
#include "ArmorInstance.h"
#include "GameState.h"

class BaseArmor;

/// <summary>
/// Initializes a new instance of the <see cref="ItemGenerator"/> class.
/// </summary>
ItemGenerator::ItemGenerator()
: _dropEntity("sphere.mesh"), _summedQualityProbability(0)
{
	_qualityProbablity.insert(std::pair<Quality, int>(Quality::Poor, 30));
	_qualityProbablity.insert(std::pair<Quality, int>(Quality::Common, 25));
	_qualityProbablity.insert(std::pair<Quality, int>(Quality::UnCommon, 20));
	_qualityProbablity.insert(std::pair<Quality, int>(Quality::Rare, 15));
	_qualityProbablity.insert(std::pair<Quality, int>(Quality::Epic, 10));
	_qualityProbablity.insert(std::pair<Quality, int>(Quality::Legendary, 5));

	for (std::map<Quality, int>::iterator it = _qualityProbablity.begin(); it != _qualityProbablity.end(); ++it) {
		_summedQualityProbability += it->second;
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="ItemGenerator"/> class.
/// </summary>
ItemGenerator::~ItemGenerator() {
}

/// <summary>
/// Generates the random item.
/// </summary>
/// <param name="pItemList">The item list to put the items in.</param>
/// <param name="pAmount">The pAmount.</param>
std::vector<ItemInstance*> ItemGenerator::generateRandomItem(Ogre::SceneNode* pNode, int pAmount, Ogre::Vector3 position) {
	std::vector<ItemInstance*> returnList;

	// generate the x items
	//TODO: test with lists, may not working because pointer deleted after execution of method.
	for (int i = 0; i < pAmount; ++i) {
		ItemInstance* item = generateRandomItem(pNode, position);
		returnList.push_back(item);
	}

	return returnList;
}

//TODO: create the item drop and set pNode as parent
ItemInstance* ItemGenerator::generateRandomItem(Ogre::SceneNode* pNode, Ogre::Vector3 position) {
	ItemInstance* returnItem;




	GameState::getSingletonPtr()->addItemNumber();
	int itemnumber = GameState::getSingleton().getItemNumber();
	Ogre::Entity* itemEntity = GameState::getSingletonPtr()->getSceneManager()->createEntity("sphere.mesh");

	
	std::stringstream nodename("_itemNode");
	nodename << itemnumber << "_" << "0";
	_itemNode = GameState::getSingletonPtr()->getLevelManager()->getLevelNode()->createChildSceneNode(nodename.str());
	_itemNode->createChildSceneNode()->attachObject(itemEntity);
	position.x += GameState::getSingletonPtr()->getRandomInRange(0, 200) - 100;
	position.z += GameState::getSingletonPtr()->getRandomInRange(0, 200) - 100;
	position.y += 10;
	_itemNode->setPosition(position);
	_itemNode->setScale(.2, .2, .2);

	//TODO: this should be a random itemtype
	int itemType = 2;
	int randomObj = 3;

	// set the quality by default to poor.
	Quality quality = Quality::Poor;

	// determine random quality by rolling and checking the probabiliies in the map
	int randomRoll = (int)GameState::getSingletonPtr()->getRandomInRange(0, _summedQualityProbability);
	int counter = 0;
	for (std::map<Quality, int>::iterator it = _qualityProbablity.begin(); it != _qualityProbablity.end(); ++it) {
		counter += it->second;

		if (randomRoll < counter) {
			quality = it->first;
			break;
		}
	}

	//int level = (int)((int)(quality + 1) * GameManager::getSingletonPtr()->getRandomInRange(1.0f, 2.5f));
	int offset = GameState::getSingletonPtr()->getRandomInRange(2, 7);
	int playerLevel = GameState::getSingletonPtr()->getLevelManager()->getPlayer()->getLevel();
	int level = GameState::getSingletonPtr()->getRandomInRange((playerLevel - offset) + quality, playerLevel + quality);
	double multiplier = GameState::getSingletonPtr()->getLevelManager()->getPlayer()->getKarma() * 0.00167;
	if (multiplier < 0) {
		multiplier = multiplier * -1;
	}else
	{
		multiplier = multiplier + 1;
	}

	// switch based on the type of item to generate it
	switch (itemType) {
		// potion
	case 0: {
		//TODO: generate the potion 
		// - randomly pick a basepotion from itemcontianer
		// - create new potion instance
		break;
	}

			// gold
	case 1: {
		//TODO: generate the gold 
		// - create a new basegold instance
		// - pick a random value based on the choosen quality and lvl
		// - create enw gold instance
		break;
	}

			// equipment
	case 2: {
		// create variables for gen
		std::vector<Stat*> baseStats;
		int typeSelection = GameState::getSingletonPtr()->getRandomInRange(1, 2);;
		Ogre::String genName = "";

		//TODO: these are defined here to enable using them after the following switch case. This is kind of ugly.
		BaseWeapon* weapon;
		
		BaseArmor* armor;
		//BaseShield* shield;
		//BaseJewelry* jewelry;

		//TODO: randomly pick an equipment type
		switch (typeSelection) {
			// shield
		case 0: {
			//TODO: shield gen
			break;
		}

				// weapon
		case 1: {
			randomObj = (int)GameState::getSingletonPtr()->getRandomInRange(0, GameState::getSingletonPtr()->getItemManager()->getItemContianer()->getWeapons().size());
			weapon = GameState::getSingletonPtr()->getItemManager()->getItemContianer()->getWeapons()[randomObj];
			
			_type = EquipmentWeapon;
			genName = weapon->getName();
			_slot = weapon->getHandedType();
			int numb = weapon->getMainStat();
			int damageValue = (int)weapon->getValueOfStat(weapon->getMainStat()).randomInRange();
			float attackSpeedValue = (float)weapon->getValueOfStat(StatType::AttackSpeed).randomInRange();
			Stat* damage = new Stat(StatType::WeaponDamage, damageValue * multiplier);
			Stat* attackSpeed = new Stat(StatType::AttackSpeed, attackSpeedValue * multiplier);
			baseStats.push_back(damage);
			baseStats.push_back(attackSpeed);

			break;
		}

				// armor
		case 2: {
			//TODO: armor gen 
			randomObj = (int)GameState::getSingletonPtr()->getRandomInRange(0, GameState::getSingletonPtr()->getItemManager()->getItemContianer()->itemAmount());
			armor = GameState::getSingletonPtr()->getItemManager()->getItemContianer()->GetArmors()[randomObj];

			_type = EquipmentArmor;
			genName = armor->getName();
			_slot = armor->getSlotType();

			int numb = armor->getMainStat();
			int armorValue = (int)armor->getValueOfStat(armor->getMainStat()).randomInRange();
			int vitalityValue = (int)armor->getValueOfStat(StatType::Vitality).randomInRange();
			int strengthValue = (int)armor->getValueOfStat(StatType::Strength).randomInRange();
			Stat* armorStat = new Stat(StatType::Armor, armorValue * multiplier);
			Stat* vitalityStat = new Stat(StatType::Vitality, vitalityValue * multiplier);
			Stat* strengthStat = new Stat(StatType::Strength, strengthValue * multiplier);
			baseStats.push_back(armorStat);
			baseStats.push_back(vitalityStat);
			baseStats.push_back(strengthStat);
			break;
		}

				// jewelry
		case 3: {
			//TODO: jewelry gen
			break;
		}

		default:
			break;
		}

		//TODO: generate affixes
		// - determine pAmount based on quality
		// - choose random affixes from the possible affixes for this item and this level, add to possibleaffixes list
		// - if pAmount > 1: choose one prefix and one suffix, remove them from possibleaffixes list, add to chosenaffixeslist
		// - choose as much affixes as affixamount, add to chosenaffixeslist
		// - generate the name with pre- and suffix
		// - choose random values for the chosen affixes
		// - add the affixes that are the same type but from a different tier (same in stattype and modifier)

		switch (typeSelection) {
		case 0: {
			//TODO: add shield instance to itemlist
			break;
		}

		case 1: {
			returnItem = new WeaponInstance(weapon, quality, itemEntity, level, genName, baseStats, _slot, _itemNode);
			//TODO: add set subID to all instances so i cann add subid after creating the returnitem.
			returnItem->id = GameState::getSingletonPtr()->getLevelManager()->subscribeItemInstance(returnItem);
			break;
		}

		case 2: {
			//TODO: add armor instance to itemlist
			returnItem = new ArmorInstance(armor, quality, itemEntity, level, genName, baseStats, _slot, _itemNode);
			returnItem->id = GameState::getSingletonPtr()->getLevelManager()->subscribeItemInstance(returnItem);
			break;
		}

		case 3: {
			//TODO: add jewelry instance to itemlist
			break;
		}

		default:
			break;
		}

		break;
	}

	default: {
		break;
	}
	}

	return returnItem;
}
