#include <iostream>
#include <string>
#include <vector>

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
    }

    // Геттеры
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }

    // Перегрузка оператора ==
    bool operator==(const Character& other) const {
        return name == other.name && health == other.health;
    }

    // Перегрузка оператора !=
    bool operator!=(const Character& other) const {
        return !(*this == other);
    }

    // Перегрузка оператора 
    friend std::ostream& operator<<(std::ostream& os, const Character& character) {
        os << "Character: " << character.name << ", HP: " << character.health
            << ", Attack: " << character.attack << ", Defense: " << character.defense;
        return os;
    }
};

class Weapon {
private:
    std::string name;
    int damage;
    double weight;

public:
    Weapon(const std::string& n, int d, double w)
        : name(n), damage(d), weight(w) {
    }

    // Геттеры
    std::string getName() const { return name; }
    int getDamage() const { return damage; }
    double getWeight() const { return weight; }

    // Перегрузка оператора +
    Weapon operator+(const Weapon& other) const {
        std::string newName = name + " + " + other.name;
        int newDamage = damage + other.damage;
        double newWeight = weight + other.weight;
        return Weapon(newName, newDamage, newWeight);
    }

    // Перегрузка оператора >
    bool operator>(const Weapon& other) const {
        return damage > other.damage;
    }

    // Перегрузка оператора 
    bool operator<(const Weapon& other) const {
        return damage < other.damage;
    }

    // Перегрузка оператора ==
    bool operator==(const Weapon& other) const {
        return damage == other.damage && weight == other.weight;
    }

    // Перегрузка оператора 
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
        os << "Weapon: " << weapon.name << ", Damage: " << weapon.damage
            << ", Weight: " << weapon.weight << " kg";
        return os;
    }
};

int main() {
    // Тестирование перегрузки операторов для класса Character
    Character hero1("Hero", 100, 20, 10);
    Character hero2("Hero", 100, 20, 10);
    Character hero3("Warrior", 150, 25, 15);

    std::cout << "Testing Character operator overloading:" << std::endl;

    if (hero1 == hero2) {
        std::cout << "hero1 and hero2 are the same!" << std::endl;
    }

    if (hero1 != hero3) {
        std::cout << "hero1 and hero3 are different!" << std::endl;
    }

    std::cout << "hero1: " << hero1 << std::endl;
    std::cout << "hero3: " << hero3 << std::endl;
    std::cout << std::endl;

    // Тестирование перегрузки операторов для класса Weapon
    Weapon sword("Sword", 15, 2.5);
    Weapon bow("Bow", 12, 1.0);
    Weapon axe("Axe", 20, 4.0);

    std::cout << "Testing Weapon operator overloading:" << std::endl;
    std::cout << "sword: " << sword << std::endl;
    std::cout << "bow: " << bow << std::endl;
    std::cout << "axe: " << axe << std::endl;
    std::cout << std::endl;

    // Оператор +
    Weapon combinedWeapon = sword + bow;
    std::cout << "Combined weapon (sword + bow): " << combinedWeapon << std::endl;

    // Оператор >
    if (axe > sword) {
        std::cout << "Axe has higher damage than sword!" << std::endl;
    }

    if (bow < axe) {
        std::cout << "Bow has lower damage than axe!" << std::endl;
    }

    // Создание нескольких комбинированных оружий
    Weapon swordAxe = sword + axe;
    Weapon bowAxe = bow + axe;

    std::cout << "\nMore combined weapons:" << std::endl;
    std::cout << "sword + axe: " << swordAxe << std::endl;
    std::cout << "bow + axe: " << bowAxe << std::endl;

    // Сравнение комбинированных оружий
    if (swordAxe > bowAxe) {
        std::cout << "sword + axe has higher damage than bow + axe!" << std::endl;
    }
    else if (swordAxe < bowAxe) {
        std::cout << "sword + axe has lower damage than bow + axe!" << std::endl;
    }
    else {
        std::cout << "sword + axe and bow + axe have the same damage!" << std::endl;
    }

    return 0;
}