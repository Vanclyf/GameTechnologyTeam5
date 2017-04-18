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

	std::vector<StatRange*> baseStatsWeapon;
	baseStatsWeapon.push_back(attackStat);
	baseStatsWeapon.push_back(speedStat);

	BaseWeapon* tempWeapon = new BaseWeapon("Simple Sword", "/", ItemType::Equipment, 1, 
		EquipmentType::EquipmentWeapon, StatType::Damage, baseStatsWeapon, HandedType::OneHanded, "/");

	std::vector<BaseWeapon*> weapons;
	weapons.push_back(tempWeapon);

	_itemContainer->setWeapons(weapons);
	//armor

	StatRange* strengthStat = new StatRange(StatType::Strength, FloatRange(2, 18));
	StatRange* vitalityStat = new StatRange(StatType::Vitality, FloatRange(1.3f, 1.4f));
	StatRange* armorStat = new StatRange(StatType::Armor, FloatRange(1.3f, 1.4f));

	std::vector<StatRange*> baseStatsArmor;
	baseStatsArmor.push_back(armorStat);
	baseStatsArmor.push_back(vitalityStat);
	baseStatsArmor.push_back(strengthStat);

	BaseArmor* tempChestArmor = new BaseArmor("Chest Armor", "/", ItemType::Equipment, 2, EquipmentType::EquipmentArmor, 
		StatType::Armor, baseStatsArmor, SlotType::Chest, "/");
	BaseArmor* tempHelmArmor = new BaseArmor("Helm Armor", "/", ItemType::Equipment, 2, EquipmentType::EquipmentArmor, 
		StatType::Armor, baseStatsArmor, SlotType::Helm, "/");
	BaseArmor* tempShouldersArmor = new BaseArmor("Shoulder Armor", "/", ItemType::Equipment, 2, EquipmentType::EquipmentArmor, 
		StatType::Armor, baseStatsArmor, SlotType::Shoulders, "/");
	BaseArmor* tempGlovesArmor = new BaseArmor("Glove Armor", "/", ItemType::Equipment, 2, EquipmentType::EquipmentArmor, 
		StatType::Armor, baseStatsArmor, SlotType::Gloves, "/");
	BaseArmor* tempBracersArmor = new BaseArmor("Bracer Armor", "/", ItemType::Equipment, 2, EquipmentType::EquipmentArmor, 
		StatType::Armor, baseStatsArmor, SlotType::Bracers, "/");
	BaseArmor* tempLegsArmor = new BaseArmor("Leg Armor", "/", ItemType::Equipment, 2, EquipmentType::EquipmentArmor, 
		StatType::Armor, baseStatsArmor, SlotType::Legs, "/"); 
	BaseArmor* tempFeetArmor = new BaseArmor("Feet Armor", "/", ItemType::Equipment, 2, EquipmentType::EquipmentArmor, 
		StatType::Armor, baseStatsArmor, SlotType::Feet, "/");


	std::vector<BaseArmor*> armors;
	armors.push_back(tempChestArmor);
	armors.push_back(tempHelmArmor);
	armors.push_back(tempShouldersArmor);
	armors.push_back(tempGlovesArmor);
	armors.push_back(tempBracersArmor);
	armors.push_back(tempLegsArmor);
	armors.push_back(tempFeetArmor);

	_itemContainer->setArmors(armors);
}

