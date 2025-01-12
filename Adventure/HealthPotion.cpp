#include "HealthPotion.h"
#include "Character.h"
#include <iostream>

HealthPotion::HealthPotion() : name("�� ����"), healthRestore(50)
{
}

string HealthPotion::getName()
{
	return name;
}

void HealthPotion::use(Character* character)
{
	cout << " �� " << character->getName() << "��(��) " << name << "��(��) ����߽��ϴ�";
	character->Heal(healthRestore);

	// �������� ���ǰ� ���� ��ü �޸� ����
	delete this;
}
