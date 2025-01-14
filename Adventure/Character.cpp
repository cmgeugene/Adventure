#include <iostream>
#include "Character.h"
#include "GenerateRandomNumber.h"
using namespace std;
//test dev123
Character::Character(const string& name)
	: name(name), level(1), health(100), maxHealth(100), attack(15), experience(0), gold(0)
{

}

Character* Character::getInstance(const string& name)
{
	if (instance == nullptr)
		instance = new Character(name);
	return instance;
}

void Character::displayStatus()
{
	cout << "        ---------- stat ----------" << endl;
	cout << "        name :       " << name << endl;
	cout << "        level :      " << level << endl;
	cout << "        health :     " << health << "/" << maxHealth << endl;
	cout << "        attack :     " << attack << endl;
	cout << "        experience : " << experience << "/100" << endl;
	cout << "        gold :       " << gold << endl;
	cout << "        --------------------------" << endl << endl << endl;
}

void Character::levelUp()
{
	if (level < 10) {
		level++;
		maxHealth = maxHealth + (level * 20);
		attack = attack + (level * 5);
		health = maxHealth;
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
		cout << "           LEVEL UP↑ 체력↑ 공격력↑ " << endl;
		cout << "  최대 체력 : " << maxHealth - (level * 20) << " -> " << maxHealth
			<< ", 공격력 : " << attack - (level * 5) << " -> " << attack << endl;
		cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
	}
}

void Character::useRandomItem()
{
	// 아이템이 있으면 랜덤 사용
	if (inventory.size() >= 1) {
		int maxIndex = (int)inventory.size() - 1;
		int index = generateRandomNumber(0, maxIndex);

		inventory[index]->use(instance);
		// 사용하고나면 벡터에서 삭제
		inventory.erase(inventory.begin() + index);
	}
}

void Character::enhanceAttack(int attackIncrease)
{
	attack += attackIncrease;
	cout << " (" << attack - attackIncrease << " -> " << attack << ")" << endl;
}

void Character::Heal(int heal)
{
	health += heal;
	if (health > maxHealth)
		health = maxHealth;
	cout << " (" << health - heal << " -> " << health << ")" << endl;
}

void Character::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0) {
		health = 0;
		cout << "(" << name << " 체력 : " << health << ")" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << ">> ㅠㅠ " << name << "가(이) 사망했습니다. GAME OVER" << endl;
	}
	else {
		cout << "(" << name << " 체력 : " << health << ")" << endl;
	}
}

bool Character::isDead()
{
	return health <= 0 ? true : false;
}

void Character::addExperience(int exp)
{
	if (level < 10) {
		experience += exp;
		if (experience >= 100) {
			levelUp();
			experience -= 100;
		}
	}
}

void Character::addGold(int _gold)
{
	gold += _gold;
}

void Character::getDropedItem(Item* item)
{
	inventory.push_back(item);
	cout << ">> " << name << "가(이) [★ " << item->getName() << "]을(를) 얻었습니다!" << endl;
}

Character* Character::instance = nullptr;
