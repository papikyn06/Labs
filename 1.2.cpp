#include <iostream>
#include <string>

class Entity {
protected:
    std::string name; // Защищенное поле: имя
    int health; // Защищенное поле: здоровье

public:
    // Конструктор базового класса
    Entity(const std::string& n, int h) : name(n), health(h) {}

    // Метод для вывода информации
    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health << std::endl;
    }

    // Виртуальный деструктор
    virtual ~Entity() {}
};

class Player : public Entity {
private:
    int experience; // Приватное поле: опыт

public:
    // Конструктор производного класса
    Player(const std::string& n, int h, int exp)
        : Entity(n, h), experience(exp) {
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        Entity::displayInfo(); // Вызов метода базового класса
        std::cout << "Experience: " << experience << std::endl;
    }

    // Метод для получения опыта
    void gainExperience(int exp) {
        if (exp > 0) {
            experience += exp;
            std::cout << name << " gained " << exp << " experience points! Total: "
                << experience << std::endl;
        }
    }
};

class Enemy : public Entity {
private:
    std::string type; // Приватное поле: тип врага

public:
    // Конструктор производного класса
    Enemy(const std::string& n, int h, const std::string& t)
        : Entity(n, h), type(t) {
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        Entity::displayInfo(); // Вызов метода базового класса
        std::cout << "Type: " << type << std::endl;
    }

    // Метод для атаки игрока
    void attackPlayer(Player& player) {
        std::cout << name << " (" << type << ") attacks the player!" << std::endl;
    }
};

class Boss : public Enemy {
private:
    std::string specialAbility; // Уникальная способность босса

public:
    // Конструктор класса Boss
    Boss(const std::string& n, int h, const std::string& t, const std::string& ability)
        : Enemy(n, h, t), specialAbility(ability) {
    }

    // Переопределение метода displayInfo
    void displayInfo() const override {
        Enemy::displayInfo(); // Вызов метода базового класса
        std::cout << "Special Ability: " << specialAbility << std::endl;
    }

    // Метод для использования специальной способности
    void useSpecialAbility() const {
        std::cout << name << " uses " << specialAbility << "!" << std::endl;
    }
};

int main() {
    // Создаем объекты игрока и врагов
    Player hero("Hero", 100, 0);
    Enemy goblin("Goblin", 50, "Goblin");
    Boss dragon("Dragon", 200, "Dragon", "Fire Breath");

    // Выводим информацию о персонажах
    std::cout << "Player info:" << std::endl;
    hero.displayInfo();
    std::cout << std::endl;

    std::cout << "Enemy info:" << std::endl;
    goblin.displayInfo();
    std::cout << std::endl;

    std::cout << "Boss info:" << std::endl;
    dragon.displayInfo();
    std::cout << std::endl;

    // Демонстрация методов
    hero.gainExperience(50);
    goblin.attackPlayer(hero);
    dragon.useSpecialAbility();

    // Проверяем обновленную информацию о герое
    std::cout << "\nUpdated player info:" << std::endl;
    hero.displayInfo();

    return 0;
}