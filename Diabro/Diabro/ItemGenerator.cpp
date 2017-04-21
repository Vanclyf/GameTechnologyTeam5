#include "ItemGenerator.h"
#include "GameManager.h"
#include "WeaponInstance.h"

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
std::vector<ItemInstance*> ItemGenerator::generateRandomItem(Ogre::SceneNode* pNode, int pAmount) {
	std::vector<ItemInstance*> returnList;

	// generate the x items
	//TODO: test with lists, may not working because pointer deleted after execution of method.
	for (int i = 0; i < pAmount; ++i) {
		ItemInstance* item = generateRandomItem(pNode);
		returnList.push_back(item);
	}

	return returnList;
}

//TODO: create the item drop and set pNode as parent
ItemInstance* ItemGenerator::generateRandomItem(Ogre::SceneNode* pNode) {
	ItemInstance* returnItem;

	Ogre::Entity* itemEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("sphere.mesh");

	//TODO: this should be a random itemtype
	int itemType = 2;
	int randomObj = 0;

	// set the quality by default to poor.
	Quality quality = Quality::Poor;

	// determine random quality by rolling and checking the probabiliies in the map
	int randomRoll = (int)GameManager::getSingletonPtr()->getRandomNumberBetween(0, _summedQualityProbability);
	int counter = 0;
	for (std::map<Quality, int>::iterator it = _qualityProbablity.begin(); it != _qualityProbablity.end(); ++it) {
		counter += it->second;

		if (randomRoll < counter) {
			quality = it->first;
			break;
		}
	}

	int level = (int)((int)(quality + 1) * GameManager::getSingletonPtr()->getRandomNumberBetween(1.0f, 2.5f));

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
		EquipmentType type = EquipmentWeapon;
		Ogre::String genName = "";

		//TODO: these are defined here to enable using them after the following switch case. This is kind of ugly.
		BaseWeapon* weapon;
		//BaseArmor* armor;
		//BaseShield* shield;
		//BaseJewelry* jewelry;

		//TODO: randomly pick an equipment type
		switch (type) {

			// shield
		case 0: {
			//TODO: shield gen
			break;
		}

				// weapon
		case 1: {
			randomObj = (int)GameManager::getSingletonPtr()->getRandomNumberBetween(0, GameManager::getSingletonPtr()->getItemManager()->getItemContianer()->getWeapons().size());
			weapon = GameManager::getSingletonPtr()->getItemManager()->getItemContianer()->getWeapons()[randomObj];

			type = EquipmentWeapon;
			genName = weapon->getName();

			level *= weapon->getItemTier();
			int numb = weapon->getMainStat();
			int damageValue = (int)weapon->getValueOfStat(weapon->getMainStat()).randomInRange();
			float attackSpeedValue = (float)weapon->getValueOfStat(StatType::AttackSpeed).randomInRange();
			Stat* damage = new Stat(StatType::WeaponDamage, damageValue);
			Stat* attackSpeed = new Stat(StatType::AttackSpeed, attackSpeedValue);
			baseStats.push_back(damage);
			baseStats.push_back(attackSpeed);

			break;
		}

				// armor
		case 2: {
			//TODO: armor gen
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

		switch (type) {
		case 0: {
			//TODO: add shield instance to itemlist
			break;
		}

		case 1: {
			returnItem = new WeaponInstance(weapon, quality, itemEntity, level, genName, baseStats);
			break;
		}

		case 2: {
			//TODO: add armor instance to itemlist
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
