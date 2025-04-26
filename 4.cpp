#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Базовый класс Entity для персонажей и монстров
class Entity {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Entity(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
            << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    const std::string& getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    virtual ~Entity() {}
};

// Производный класс Player (игрок)
class Player : public Entity {
private:
    int experience;

public:
    Player(const std::string& n, int h, int a, int d, int exp = 0)
        : Entity(n, h, a, d), experience(exp) {
    }

    void displayInfo() const override {
        Entity::displayInfo();
        std::cout << "Experience: " << experience << std::endl;
    }
};

// Производный класс Enemy (враг)
class Enemy : public Entity {
private:
    std::string type;

public:
    Enemy(const std::string& n, int h, int a, int d, const std::string& t)
        : Entity(n, h, a, d), type(t) {
    }

    void displayInfo() const override {
        Entity::displayInfo();
        std::cout << "Type: " << type << std::endl;
    }
};

// Класс Inventory для хранения предметов
class Inventory {
private:
    std::vector<std::unique_ptr<std::string>> items; // Динамический массив предметов

public:
    // Добавление предмета в инвентарь
    void addItem(const std::string& item) {
        items.push_back(std::make_unique<std::string>(item));
        std::cout << "Item added to inventory: " << item << std::endl;
    }

    // Вывод всех предметов в инвентаре
    void displayInventory() const {
        if (items.empty()) {
            std::cout << "Inventory is empty." << std::endl;
            return;
        }

        std::cout << "Inventory contents:" << std::endl;
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << *items[i] << std::endl;
        }
    }

    // Получение количества предметов в инвентаре
    size_t getSize() const {
        return items.size();
    }

    // Удаление предмета из инвентаря по индексу
    bool removeItem(size_t index) {
        if (index >= 0 && index < items.size()) {
            std::cout << "Item removed from inventory: " << *items[index] << std::endl;
            items.erase(items.begin() + index);
            return true;
        }
        return false;
    }
};

int main() {
    // Создаем игрока
    std::unique_ptr<Player> hero = std::make_unique<Player>("Hero", 100, 20, 10);

    // Создаем врагов
    std::unique_ptr<Enemy> goblin = std::make_unique<Enemy>("Goblin", 50, 15, 5, "Goblin");
    std::unique_ptr<Enemy> dragon = std::make_unique<Enemy>("Dragon", 200, 30, 20, "Dragon");

    // Выводим информацию о персонажах
    std::cout << "Game characters:" << std::endl;
    hero->displayInfo();
    goblin->displayInfo();
    dragon->displayInfo();

    // Создаем инвентарь игрока
    Inventory playerInventory;

    // Добавляем предметы в инвентарь
    playerInventory.addItem("Health Potion");
    playerInventory.addItem("Iron Sword");
    playerInventory.addItem("Leather Armor");
    playerInventory.addItem("Magic Scroll");

    // Выводим содержимое инвентаря
    playerInventory.displayInventory();

    // Удаляем предмет из инвентаря (например, использовали зелье)
    playerInventory.removeItem(0);

    // Проверяем инвентарь после удаления предмета
    playerInventory.displayInventory();

    // Создаем массив умных указателей на базовый класс Entity
    std::vector<std::unique_ptr<Entity>> entities;

    // Добавляем персонажей в массив
    entities.push_back(std::make_unique<Player>("Wizard", 80, 25, 5, 10));
    entities.push_back(std::make_unique<Enemy>("Skeleton", 40, 10, 3, "Undead"));
    entities.push_back(std::make_unique<Enemy>("Orc", 70, 18, 8, "Humanoid"));

    // Выводим информацию о всех сущностях (демонстрация полиморфизма)
    std::cout << "\nAll game entities:" << std::endl;
    for (const auto& entity : entities) {
        entity->displayInfo();
    }

    return 0;
}