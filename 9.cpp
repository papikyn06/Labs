#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

template<typename T>
class Logger {
private:
    std::ofstream out;
public:
    Logger(const std::string& filename) { out.open(filename, std::ios::app); }
    ~Logger() { if (out.is_open()) out.close(); }
    void log(const T& entry) { out << entry << std::endl; }
};

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;
    int level;
    int experience;
public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d), level(1), experience(0) {
    }
    void attackEnemy(Character& enemy, Logger<std::string>& logger) {
        int dmg = attack - enemy.defense;
        if (dmg > 0) {
            enemy.health -= dmg;
            logger.log(name + " attacks " + enemy.name + " for " + std::to_string(dmg));
        }
        else {
            logger.log(name + " attacks " + enemy.name + " but it has no effect");
        }
        if (enemy.health <= 0) throw std::runtime_error(enemy.name + " has been defeated");
    }
    void heal(int amount, Logger<std::string>& logger) {
        health += amount;
        if (health > 100) health = 100;
        logger.log(name + " heals for " + std::to_string(amount));
    }
    void gainExperience(int exp, Logger<std::string>& logger) {
        experience += exp;
        logger.log(name + " gains " + std::to_string(exp) + " XP");
        if (experience >= 100) {
            level++;
            experience -= 100;
            logger.log(name + " leveled up to " + std::to_string(level));
        }
    }
    void displayInfo() const {
        std::cout << name << " HP:" << health << " ATK:" << attack
            << " DEF:" << defense << " LVL:" << level
            << " XP:" << experience << std::endl;
    }
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    void save(std::ofstream& out) const {
        out << name << ' ' << health << ' ' << attack << ' '
            << defense << ' ' << level << ' ' << experience << std::endl;
    }
    void load(std::ifstream& in) {
        in >> name >> health >> attack >> defense >> level >> experience;
    }
};

class Monster {
protected:
    std::string name;
    int health;
    int attack;
    int defense;
public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
    }
    virtual ~Monster() = default;
    virtual void attackCharacter(Character& c, Logger<std::string>& logger) {
        int dmg = attack - c.getDefense();
        if (dmg > 0) {
            // reduce via setter logic
        }
        logger.log(name + " attacks " + c.getName() + " for " + std::to_string(dmg));
    }
    virtual void displayInfo() const {
        std::cout << name << " HP:" << health
            << " ATK:" << attack << " DEF:" << defense << std::endl;
    }
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    void save(std::ofstream& out) const {
        out << name << ' ' << health << ' ' << attack << ' ' << defense << std::endl;
    }
    void load(std::ifstream& in) {
        in >> name >> health >> attack >> defense;
    }
};

class Goblin : public Monster {
public:
    Goblin() : Monster("Goblin", 30, 10, 5) {}
};

class Dragon : public Monster {
public:
    Dragon() : Monster("Dragon", 200, 25, 15) {}
};

class Skeleton : public Monster {
public:
    Skeleton() : Monster("Skeleton", 50, 15, 10) {}
};

class Inventory {
private:
    std::vector<std::string> items;
public:
    void addItem(const std::string& item) { items.push_back(item); }
    void removeItem(const std::string& item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) items.erase(it);
    }
    void display() const {
        std::cout << "Inventory:";
        for (const auto& i : items) std::cout << ' ' << i;
        std::cout << std::endl;
    }
    void save(std::ofstream& out) const {
        out << items.size();
        for (const auto& i : items) out << ' ' << i;
        out << std::endl;
    }
    void load(std::ifstream& in) {
        size_t n; in >> n;
        items.clear();
        for (size_t i = 0; i < n; ++i) { std::string s; in >> s; items.push_back(s); }
    }
};

class Game {
private:
    Character hero;
    Inventory inv;
    Logger<std::string> logger;
public:
    Game() : hero("Hero", 100, 20, 10), logger("game.log") {}
    void start() {
        logger.log("Game started");
        hero.displayInfo();
        inv.display();
    }
    void battle(Monster& m) {
        logger.log("Battle with " + m.getName() + " begins");
        try {
            while (hero.getHealth() > 0 && m.getHealth() > 0) {
                hero.attackEnemy(*reinterpret_cast<Character*>(&m), logger);
                m.attackCharacter(hero, logger);
            }
        }
        catch (const std::runtime_error& e) {
            logger.log(std::string("Exception: ") + e.what());
        }
    }
    void saveGame(const std::string& filename) {
        std::ofstream out(filename);
        hero.save(out);
        inv.save(out);
    }
    void loadGame(const std::string& filename) {
        std::ifstream in(filename);
        hero.load(in);
        inv.load(in);
    }
};

int main() {
    Game g;
    g.start();
    Goblin gob;
    g.battle(gob);
    g.saveGame("save.dat");
    Game g2;
    g2.loadGame("save.dat");
    return 0;
}
