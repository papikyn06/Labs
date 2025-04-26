#include <iostream>
#include <string>
#include <memory>
#include <vector>

// ������� ����� Entity ��� ���������� � ��������
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

// ����������� ����� Player (�����)
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

// ����������� ����� Enemy (����)
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

// ����� Inventory ��� �������� ���������
class Inventory {
private:
    std::vector<std::unique_ptr<std::string>> items; // ������������ ������ ���������

public:
    // ���������� �������� � ���������
    void addItem(const std::string& item) {
        items.push_back(std::make_unique<std::string>(item));
        std::cout << "Item added to inventory: " << item << std::endl;
    }

    // ����� ���� ��������� � ���������
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

    // ��������� ���������� ��������� � ���������
    size_t getSize() const {
        return items.size();
    }

    // �������� �������� �� ��������� �� �������
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
    // ������� ������
    std::unique_ptr<Player> hero = std::make_unique<Player>("Hero", 100, 20, 10);

    // ������� ������
    std::unique_ptr<Enemy> goblin = std::make_unique<Enemy>("Goblin", 50, 15, 5, "Goblin");
    std::unique_ptr<Enemy> dragon = std::make_unique<Enemy>("Dragon", 200, 30, 20, "Dragon");

    // ������� ���������� � ����������
    std::cout << "Game characters:" << std::endl;
    hero->displayInfo();
    goblin->displayInfo();
    dragon->displayInfo();

    // ������� ��������� ������
    Inventory playerInventory;

    // ��������� �������� � ���������
    playerInventory.addItem("Health Potion");
    playerInventory.addItem("Iron Sword");
    playerInventory.addItem("Leather Armor");
    playerInventory.addItem("Magic Scroll");

    // ������� ���������� ���������
    playerInventory.displayInventory();

    // ������� ������� �� ��������� (��������, ������������ �����)
    playerInventory.removeItem(0);

    // ��������� ��������� ����� �������� ��������
    playerInventory.displayInventory();

    // ������� ������ ����� ���������� �� ������� ����� Entity
    std::vector<std::unique_ptr<Entity>> entities;

    // ��������� ���������� � ������
    entities.push_back(std::make_unique<Player>("Wizard", 80, 25, 5, 10));
    entities.push_back(std::make_unique<Enemy>("Skeleton", 40, 10, 3, "Undead"));
    entities.push_back(std::make_unique<Enemy>("Orc", 70, 18, 8, "Humanoid"));

    // ������� ���������� � ���� ��������� (������������ ������������)
    std::cout << "\nAll game entities:" << std::endl;
    for (const auto& entity : entities) {
        entity->displayInfo();
    }

    return 0;
}