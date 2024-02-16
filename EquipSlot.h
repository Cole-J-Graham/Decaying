#pragma once
#include"Item.h"
class EquipSlot
{
public:
	//Constructors and Destructors
	EquipSlot(Item* item);
	~EquipSlot();

	//Core Functions
	void equip();

private:
	Item* item;
};

