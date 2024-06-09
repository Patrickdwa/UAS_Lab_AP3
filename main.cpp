#include <iostream> //Input / Output 
#include <cstdlib> // Digunakan untuk random rumber generator 
#include <ctime> //Digunakan untuk mengacak Random Numver Generator dengan waktu sekarang
#include <vector> // untuk menggunakan vector

using namespace std;

class LifeSim 
{
    private:
        int health;
        int maxHealth;
        int money;
        int energy;
        int maxEnergy;
        int jobExperienceFF;
        int jobExperienceOW;
        int jobExperienceGO;
        bool gameOver;
        int homeType; 
        int jobType;  
    
    public:
        LifeSim() 
        {
            health = 100;
            maxHealth = 100;
            money = 0;
            energy = 100;
            maxEnergy = 100;
            jobExperienceFF = 0;
            jobExperienceOW = 0;
            jobExperienceGO = 0;
            gameOver = false;
            homeType = 0;
            jobType = 0;
        }
    
        void displayStatus() 
        {
            cout<<"=================================\n";
            cout << "Hobo" << endl;
            cout << "Health: " << health << "/" << maxHealth << endl;
            cout << "Energy: " << energy << "/" << maxEnergy << endl;
            cout << "Money: $" << money << endl;
            cout << "Occupation: ";
            switch(jobType) 
            {
                case 0:
                    cout << "Fast Food Worker";
                    break;
                case 1:
                    cout << "Office Worker";
                    break;
                case 2:
                    cout << "Government Official";
                    break;
            }
            cout << endl;
        
            cout << "Living: ";
            switch(homeType) 
            {
                case 0:
                    cout << "Street";
                    break;
                case 1:
                    cout << "Apartment";
                    break;
                case 2:
                    cout << "House";
                    break;
                case 3:
                    cout << "Mansion";
                    break;
            }
            cout << endl;
            cout<<"=================================\n";
        }
    
        void work() 
        {
            if (!gameOver) // Dibuat bertujuan agar function akan berhenti jika game sudah berakhir
            {
                switch(jobType) 
                {
                    case 0:
                        jobExperienceFF += 1;
                        money += 20;
                        health -= 5;
                        energy -= 10;
                        break;
                    case 1:
                        jobExperienceOW += 1;
                        money += 400;
                        health -= 10;
                        energy -= 15;
                        break;
                    case 2:
                        jobExperienceGO += 1;
                        money += 1500;
                        health -= 15;
                        energy -= 20;
                        break;
                }
                if (energy <= 0) 
                {
                    energy = 0;
                    gameOver = true;
                }
                if (health <= 0) 
                {
                    health = 0;
                    gameOver = true;
                }
                if ((money >= 50000) && (homeType == 3)) 
                {
                    gameOver = true;
                }
                if (shouldTriggerRandomEvent()) 
                {
                    handleRandomEvent();
                }
                displayStatus();
            }
        }
    
        void jobraise() 
        {
            if (!gameOver) 
            {
                if (jobType == 0 && jobExperienceFF >= 5) 
                {
                    jobExperienceFF -= 5; // job experience dikurangi agar ketentuan diatas tidak berjalan sehingga mengatasi masalah ngebug
                    jobType = 1;
                    cout << "Congratulations on the raise! You are now an Office Worker!" << endl;
                    displayStatus();
                } else if(jobType == 0 && jobExperienceFF < 5) 
                {
                    cout << "You are not yet qualified to be an Office Worker!" << endl;
                    cout << "Job Experience (" << jobExperienceFF << "/5)\n";
                } else if (jobType == 1 && jobExperienceOW >= 5) 
                {
                    jobExperienceOW -= 5;
                    jobType = 2;
                    cout << "Congratulations on the raise! You are now a Government Official!" << endl;
                    displayStatus();
                } else if(jobType == 1 && jobExperienceOW < 5) 
                {
                    cout << "You are not yet qualified to be a Government Official!" << endl;
                    cout << "Job Experience (" << jobExperienceOW << "/5)\n";
                }
            }
        }
    
        void sleep() 
        {
            if (!gameOver) 
            {
                energy += 10;
                switch(homeType) 
                {
                    case 0:
                        health += 5;
                        energy += 5;
                        break;
                    case 1:
                        health += 10;
                        energy += 10;
                        break;
                    case 2:
                        health += 20;
                        energy += 15;
                        break;
                    case 3:
                        health += 40;
                        energy += 50;
                        break;
                }
                if (health > maxHealth)
                    health = maxHealth;
                if (energy > maxEnergy)
                    energy = maxEnergy;
                displayStatus();
            }
        }
    
        void visitHospital() 
        {
            if (!gameOver) {
                if (money >= 50) 
                {
                    health = maxHealth;
                    money -= 50;
                    if (shouldTriggerRandomEvent()) 
                    {
                        handleRandomEvent();
                    }
                    displayStatus();
                } 
                else 
                {
                    cout << "Not enough money to visit the hospital." << endl;
                }
            }
        }
    
        void buyRealEstate() 
        {
            if (!gameOver) 
            {
                cout << "u==u==u==u==u==u==u==u==u==u==u==u==u==u"<<endl;
                cout << "Choose the type of property to buy:" << endl;
                cout << "1. Apartment ($100)" << endl;
                cout << "2. House ($1000)" << endl;
                cout << "3. Mansion ($50000)" << endl;
                cout << "n==n==n==n==n==n==n==n==n==n==n==n==n==n"<<endl;
                
                int choice;
                cout << "Enter your choice: ";
                cin >> choice;
            
                switch(choice) 
                {
                    case 1:
                        if (money >= 100 && homeType < 1) 
                        {
                            money -= 100;
                            homeType = 1;
                            if (shouldTriggerRandomEvent()) 
                            {
                                handleRandomEvent();
                            }
                            displayStatus();
                        } else if (homeType >= 1) 
                        {
                            cout << "You already own the apartment." << endl;
                        } 
                        else 
                        {
                            cout << "Not enough money to buy the apartment." << endl;
                        }
                        break;
                    case 2:
                        if (money >= 1000 && homeType < 2) 
                        {
                            money -= 1000;
                            homeType = 2;
                            if (shouldTriggerRandomEvent()) 
                            {
                                handleRandomEvent();
                            }
                            displayStatus();
                        } else if (homeType >= 2) 
                        {
                            cout << "You already own the house." << endl;
                        } 
                        else 
                        {
                            cout << "Not enough money to buy the house." << endl;
                        }
                        break;
                    case 3:
                        if (money >= 50000 && homeType < 3) 
                        {
                            money -= 50000;
                            homeType = 3;
                            if (shouldTriggerRandomEvent()) 
                            {
                                handleRandomEvent();
                            }
                            displayStatus();
                        } else if (homeType >= 3) 
                        {
                            cout << "You already own the mansion." << endl;
                        } 
                        else 
                        {
                            cout << "Not enough money to buy the mansion." << endl;
                        }
                        break;
                    case 66:
                        money += 50000;
                        cout << "Cheat activated! +$50,000." << endl;
                        displayStatus();
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
    
        void handleRandomEvent() 
        {
            vector<string> events = 
            {
                "You lost $10.",
                "You got into an accident and lost some health.",
                "You found $20 in the street!"
            };
            
            int event = rand() % events.size();
            cout << events[event] << endl;
            switch(event) 
            {
                case 0:
                    money -= 10;
                    break;
                case 1:
                    health -= 10;
                    if (health <= 0) 
                    {
                        health = 0;
                        gameOver = true;
                    }
                    break;
                case 2:
                    money += 20;
                    break;
            }
        }
    
        bool shouldTriggerRandomEvent() 
        {
            return rand() % 100 < 20;       // event random diset dengan kemungkinan 20 %
        }
    
        bool isGameOver() 
        {
            return gameOver;
        }
};

int main() 
{
    srand(time(0)); // randomizer sesuai dengan waktu yang akan selalu berubah
    LifeSim game;
    cout << "Your name is Hobo. Hobo is an orphan that is expelled from his orphanage for causing too much trouble. \nNow he has to survive by his own. Currently he lives in a street, and somehow has gotten a job as a fast food worker. \nNow his goal is to earn $50,000 and a mansion, and he will be happy.\n";
    while (!game.isGameOver()) 
    {
        int choice;
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
        cout << "1. Work 2. Sleep 3. Visit Hospital 4. Buy Real Estate 5. Ask for Raise\n";
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
        cout<<"You decide to do: ";
        cin >> choice;
        
        switch(choice) 
        {
            case 1:
                game.work();
                break;
            case 2:
                game.sleep();
                break;
            case 3:
                game.visitHospital();
                break;
            case 4:
                game.buyRealEstate();
                break;
            case 5:
                game.jobraise();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    cout << "Game over." << endl;
    return 0;
}
