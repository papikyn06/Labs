#include <iostream>
#include <string>

class Character {
private:
    std::string name; // Приватное поле: имя персонажа
    int health; // Приватное поле: уровень здоровья
    int attack; // Приватное поле: уровень атаки
    int defense; // Приватное поле: уровень защиты
    int maxHealth; // Приватное поле: максимальное здоровье

public:
    // Конструктор для инициализации данных
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d), maxHealth(h) {
    }

    // Метод для получения уровня здоровья
    int getHealth() const {
        return health;
    }

    // Метод для вывода информации о персонаже
    void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    // Метод для атаки другого персонажа
    void attackEnemy(Character& enemy) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.health -= damage;
            std::cout << name << " attacks " << enemy.name << " for "
                << damage << " damage!" << std::endl;
        }
        else {
            std::cout << name << " attacks " << enemy.name
                << ", but it has no effect!" << std::endl;
        }
    }

    // Метод для лечения персонажа
    void heal(int amount) {
        if (amount <= 0) {
            std::cout << "Cannot heal by non-positive amount!" << std::endl;
            return;
        }

        int oldHealth = health;
        health += amount;
        if (health > maxHealth) {
            health = maxHealth;
        }

        std::cout << name << " healed for " << (health - oldHealth)
            << " HP! Current health: " << health << std::endl;
    }

    // Метод для получения урона
    void takeDamage(int amount) {
        if (amount <= 0) {
            std::cout << "Damage must be positive!" << std::endl;
            return;
        }

        health -= amount;
        if (health < 0) {
            health = 0;
        }

        std::cout << name << " took " << amount << " damage! "
            << "Remaining health: " << health << std::endl;
    }
};

int main() {
    // Создаем объекты персонажей
    Character hero("Hero", 100, 20, 10);
    Character monster("Goblin", 50, 15, 5);

    // Выводим информацию о персонажах
    std::cout << "Initial stats:" << std::endl;
    hero.displayInfo();
    monster.displayInfo();
    std::cout << std::endl;

    // Герой атакует монстра
    hero.attackEnemy(monster);
    std::cout << "After hero's attack:" << std::endl;
    monster.displayInfo();
    std::cout << std::endl;

    // Монстр атакует героя
    monster.attackEnemy(hero);
    std::cout << "After monster's attack:" << std::endl;
    hero.displayInfo();
    std::cout << std::endl;

    // Тестируем метод heal
    hero.heal(30);
    hero.displayInfo();
    std::cout << std::endl;

    // Тестируем метод takeDamage
    monster.takeDamage(25);
    monster.displayInfo();
    std::cout << std::endl;

    // Проверяем граничные случаи
    monster.heal(100); // Должно ограничиться максимальным здоровьем
    monster.displayInfo();

    monster.takeDamage(100); // Здоровье не должно стать отрицательным
    monster.displayInfo();

    return 0;
}