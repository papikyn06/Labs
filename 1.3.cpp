#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

class Entity {
protected:
    std::string name;
    int health;
    int attack;
    int defense;
    int maxHealth;

public:
    Entity(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d), maxHealth(h) {
    }

    // Виртуальный метод для атаки
    virtual void attackEntity(Entity& target) {
        int damage = attack - target.getDefense();
        if (damage > 0) {
            target.takeDamage(damage);
            std::cout << name << " attacks " << target.getName() << " for "
                << damage << " damage!" << std::endl;
        }
        else {
            std::cout << name << " attacks " << target.getName()
                << ", but it has no effect!" << std::endl;
        }
    }

    // Виртуальный метод для вывода информации
    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health << "/" << maxHealth
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    // Виртуальный метод для лечения
    virtual void heal(int amount) {
        if (amount <= 0) return;

        int oldHealth = health;
        health += amount;
        if (health > maxHealth) {
            health = maxHealth;
        }

        std::cout << name << " healed for " << (health - oldHealth)
            << " HP! Current health: " << health << "/" << maxHealth << std::endl;
    }

    // Метод для получения урона - виртуальный для возможности переопределения
    virtual void takeDamage(int damage) {
        if (damage <= 0) return;

        health -= damage;
        if (health < 0) health = 0;
    }

    // Геттер для здоровья
    int getHealth() const {
        return health;
    }

    // Геттер для имени
    std::string getName() const {
        return name;
    }

    // Геттер для защиты
    int getDefense() const {
        return defense;
    }

    // Виртуальный деструктор
    virtual ~Entity() {}
};

class Character : public Entity {
private:
    int experience;
    int level;

public:
    Character(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d), experience(0), level(1) {
    }

    // Переопределение метода attack
    void attackEntity(Entity& target) override {
        int damage = attack - target.getDefense();
        if (damage > 0) {
            // Шанс на критический удар (20%)
            if (rand() % 100 < 20) {
                damage *= 2;
                std::cout << "Critical hit! ";
            }
            target.takeDamage(damage);
            std::cout << name << " attacks " << target.getName() << " for "
                << damage << " damage!" << std::endl;
        }
        else {
            std::cout << name << " attacks " << target.getName()
                << ", but it has no effect!" << std::endl;
        }
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        std::cout << "Character: ";
        Entity::displayInfo();
        std::cout << "Level: " << level << ", Experience: " << experience << std::endl;
    }

    // Переопределение метода heal с добавлением специфики для персонажа
    void heal(int amount) override {
        std::cout << "Character uses a healing potion! ";
        Entity::heal(amount);
    }

    // Метод для получения опыта и повышения уровня
    void gainExperience(int exp) {
        if (exp <= 0) return;

        experience += exp;
        std::cout << name << " gained " << exp << " experience!" << std::endl;

        // Проверка на повышение уровня (100 опыта = 1 уровень)
        if (experience >= 100) {
            level += experience / 100;
            experience %= 100;
            std::cout << name << " leveled up to level " << level << "!" << std::endl;

            // Увеличение характеристик при повышении уровня
            maxHealth += 20;
            health = maxHealth;
            attack += 5;
            defense += 3;
            std::cout << "Stats increased: Health=" << maxHealth
                << ", Attack=" << attack << ", Defense=" << defense << std::endl;
        }
    }
};

class Monster : public Entity {
protected:
    std::string type;

public:
    Monster(const std::string& n, int h, int a, int d, const std::string& t)
        : Entity(n, h, a, d), type(t) {
    }

    // Переопределение метода attack
    void attackEntity(Entity& target) override {
        int damage = attack - target.getDefense();
        if (damage > 0) {
            // Шанс на ядовитую атаку (30%)
            if (rand() % 100 < 30) {
                damage += 5; // Дополнительный урон от яда
                std::cout << "Poisonous attack! ";
            }
            target.takeDamage(damage);
            std::cout << name << " attacks " << target.getName() << " for "
                << damage << " damage!" << std::endl;
        }
        else {
            std::cout << name << " attacks " << target.getName()
                << ", but it has no effect!" << std::endl;
        }
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        std::cout << "Monster (" << type << "): ";
        Entity::displayInfo();
    }
};

class Boss : public Monster {
private:
    std::string specialAbility;
    int specialAttackPower;

public:
    Boss(const std::string& n, int h, int a, int d, const std::string& t,
        const std::string& ability, int specialPower)
        : Monster(n, h, a, d, t), specialAbility(ability), specialAttackPower(specialPower) {
    }

    // Переопределение метода attack с использованием особой способности
    void attackEntity(Entity& target) override {
        // Шанс использования особой способности (40%)
        if (rand() % 100 < 40) {
            useSpecialAbility(target);
        }
        else {
            Monster::attackEntity(target);
        }
    }

    // Метод для использования особой способности
    void useSpecialAbility(Entity& target) {
        std::cout << name << " uses " << specialAbility << "!" << std::endl;
        int damage = specialAttackPower - target.getDefense() / 2; // Особая атака игнорирует часть защиты
        if (damage > 0) {
            target.takeDamage(damage);
            std::cout << "Special attack deals " << damage << " damage to "
                << target.getName() << "!" << std::endl;
        }
        else {
            std::cout << "But it has no effect on " << target.getName() << "!" << std::endl;
        }
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        std::cout << "Boss (" << type << "): ";
        Entity::displayInfo();
        std::cout << "Special Ability: " << specialAbility
            << " (Power: " << specialAttackPower << ")" << std::endl;
    }
};

int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned>(time(0)));

    // Создание объектов
    Character hero("Hero", 100, 20, 10);
    Monster goblin("Goblin", 50, 15, 5, "Goblin");
    Boss dragon("Dragon", 200, 30, 15, "Dragon", "Fire Breath", 40);

    // Массив указателей на базовый класс
    std::vector<Entity*> entities = { &hero, &goblin, &dragon };

    // Полиморфное поведение - вывод информации о всех сущностях
    std::cout << "Initial stats of all entities:" << std::endl;
    for (auto& entity : entities) {
        entity->displayInfo();
        std::cout << std::endl;
    }

    // Бой между сущностями
    std::cout << "\n--- Combat begins ---\n" << std::endl;

    // Герой атакует гоблина
    hero.attackEntity(goblin);
    std::cout << "Goblin's status after hero's attack:" << std::endl;
    goblin.displayInfo();
    std::cout << std::endl;

    // Гоблин атакует героя
    goblin.attackEntity(hero);
    std::cout << "Hero's status after goblin's attack:" << std::endl;
    hero.displayInfo();
    std::cout << std::endl;

    // Дракон атакует героя
    dragon.attackEntity(hero);
    std::cout << "Hero's status after dragon's attack:" << std::endl;
    hero.displayInfo();
    std::cout << std::endl;

    // Герой лечится
    hero.heal(30);
    std::cout << "Hero's status after healing:" << std::endl;
    hero.displayInfo();
    std::cout << std::endl;

    // Герой получает опыт за победу над гоблином
    hero.gainExperience(50);
    std::cout << "Hero's status after gaining experience:" << std::endl;
    hero.displayInfo();
    std::cout << std::endl;

    // Герой получает еще опыт и повышает уровень
    hero.gainExperience(60);
    std::cout << "Hero's status after leveling up:" << std::endl;
    hero.displayInfo();

    return 0;
}