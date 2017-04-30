#include "ItemManager.h"
#include "GameManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="ItemManager"/> class.
/// </summary>
ItemManager::ItemManager() {
	// init itemgen
	
	_itemContainer = new ItemContainer();
	_itemGenerator = new ItemGenerator();

	readFromDB();
}

ItemManager::~ItemManager() {
	delete _itemContainer;
	delete _itemGenerator;
}



/// <summary>
/// Reads item information from database.
/// </summary>
void ItemManager::readFromDB() {
	//TODO: make this method read from the database
	//for now: fill itemcontainer with one item to enable generation

	StatRange* attackStat = new StatRange(StatType::Damage, FloatRange(2, 18));
	StatRange* speedStat = new StatRange(StatType::AttackSpeed, FloatRange(1.3f, 1.4f));

	std::vector<StatRange*> baseStats;
	baseStats.push_back(attackStat);
	baseStats.push_back(speedStat);

	BaseWeapon* tempWeapon = new BaseWeapon("Simple Sword", "/", ItemType::Equipment, 1, 
		EquipmentType::EquipmentWeapon, StatType::Damage, baseStats, HandedType::OneHanded, "/");

	std::vector<BaseWeapon*> weapons;
	weapons.push_back(tempWeapon);

	_itemContainer->setWeapons(weapons);
}



