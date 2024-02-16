#include "EquipSlot.h"
//Constructors and Destructors
EquipSlot::EquipSlot(Item* item)
{
	this->item = item;
}

EquipSlot::~EquipSlot()
{
	delete this->item;
}

//Core Functions
void EquipSlot::equip()
{

}