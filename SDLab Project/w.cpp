#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

class Player {
private:
    string name;
    int level;
    int score;

public:
    Player(string playerName, int playerLevel, int playerScore)
        : name(playerName), level(playerLevel), score(playerScore) {}
    ~Player() = default;

    void displayInfo() const {
        cout << left << setw(15) << name << " | Level: " << setw(5) << level << " | Score: " << score << endl;
    }

    string getName() const { return name; }
    int getLevel() const { return level; }
    int getScore() const { return score; }

    void saveToFile(ofstream& file) const {
        file << name << " " << level << " " << score << endl;
    }

    static Player loadFromFile(ifstream& file) {
        string name;
        int level, score;
        file >> name >> level >> score;
        return Player(name, level, score);
    }
};

class PlayerManager {
private:
    vector<Player> players;
    const string fileName = "players.txt";

public:
    void addPlayer() {
        string name;
        int level, score;

        cout << "\n--- Add a New Player ---\n";
        cout << "Enter Player Name: ";
        cin >> name;

        cout << "Enter Player Level (positive integer): ";
        while (!(cin >> level) || level < 1) {
            cout << "Invalid level. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Player Score (non-negative integer): ";
        while (!(cin >> score) || score < 0) {
            cout << "Invalid score. Please enter a non-negative number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        players.push_back(Player(name, level, score));
        cout << "\n✅ Player added successfully!\n";
        displayPlayers();
    }

    void displayPlayers() const {
        cout << "\n--- Player List ---\n";
        if (players.empty()) {
            cout << "No players found!\n";
            return;
        }
        cout << left << setw(15) << "Name" << " | " << "Level" << " | " << "Score" << "\n";
        cout << string(35, '-') << endl;
        for (const auto& player : players) {
            player.displayInfo();
        }
    }

    void saveToFile() {
        ofstream file(fileName);
        if (!file) {
            cerr << "\n❌ Error opening file for writing!\n";
            return;
        }
        for (const auto& player : players) {
            player.saveToFile(file);
        }
        file.close();
        cout << "\n💾 Player data saved successfully!\n";
    }

    void loadFromFile() {
        ifstream file(fileName);
        if (!file) {
            cout << "\nℹ️ No existing data found. Starting fresh.\n";
            return;
        }
        players.clear();
        while (file) {
            Player player = Player::loadFromFile(file);
            if (!file.eof()) players.push_back(player);
        }
        file.close();
        cout << "\n📂 Player data loaded successfully!\n";
    }

    void findBestPlayer() const {
        cout << "\n--- Best Player ---\n";
        if (players.empty()) {
            cout << "No players found!\n";
            return;
        }
        const Player* bestPlayer = &players[0];
        for (const auto& player : players) {
            if (player.getScore() > bestPlayer->getScore()) {
                bestPlayer = &player;
            }
        }
        bestPlayer->displayInfo();
    }
};

int main() {
    PlayerManager manager;
    manager.loadFromFile();
    std::cout << "Welcome to StatGuardian!\n";
    int choice;
    do {
        cout << "\n=========================";
        cout << "\n   🎮 Player Manager   ";
        cout << "\n=========================";
        cout << "\n1️⃣ Add Player";
        cout << "\n2️⃣ View Players";
        cout << "\n3️⃣ Find Best Player";
        cout << "\n4️⃣ Save & Exit";
        cout << "\n=========================";
        cout << "\nEnter choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Invalid input. Please enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            manager.addPlayer();
            break;
        case 2:
            manager.displayPlayers();
            break;
        case 3:
            manager.findBestPlayer();
            break;
        case 4:
            manager.saveToFile();
            cout << "\n👋 Goodbye! Your data has been saved.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}
