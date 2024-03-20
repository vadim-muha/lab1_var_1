#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_DiSH = 10;

struct Dish
{
    string nameDish;
    string type;
    int quantity;
    string vaga;
};

Dish dishes[MAX_DiSH];
int numDish = 0;

void AddDish()
{
    if (numDish < MAX_DiSH)
    {
        Dish newDish;
        cout << "Enter name stravi: ";
        cin >> newDish.nameDish;
        cout << "Enter type stravi: ";
        cin >> newDish.type;
        cout << "Enter koll calories: ";
        cin >> newDish.quantity;
        cout << "Enter vaga: ";
        cin >> newDish.vaga;
        dishes[numDish++] = newDish;
        cout << "Group added successfully. \n";
    }
    else
    {
        cout << "The maximum number of dishes has been reached. \n";
    }
}

void DeleteDish(string type)
{
    for (int i = 0; i < numDish; ++i)
    {
        if (dishes[i].type == type)
        {
            for (int j = i; j < numDish - 1; ++j)
            {
                dishes[j] = dishes[j + 1];
            }
            --numDish;
            cout << "Dish with number " << type << " deleted successfully.\n";
            return;
        }
    }
    cout << "Dish with number " << type << " not found.\n";
}


void ModifyDish(string type)
{
    for (int i = 0; i < numDish; ++i)
    {
        if (dishes[i].type == type)
        {
            cout << "Enter a new dish: ";
            cin >> dishes[i].nameDish;
            cout << "Enter new number of calories: ";
            cin >> dishes[i].quantity;
            cout << "Enter new weight: ";
            cin >> dishes[i].vaga;
            cout << "Dish information modified successfully.\n";
            return;
        }
    }
    cout << "Dish with number " << type << " not found.\n";
}

void SortByNameDish()
{
    for (int i = 0; i < numDish - 1; ++i)
    {
        for (int j = 0; j < numDish - i - 1; ++j)
        {
            if (dishes[j].nameDish < dishes[j + 1].nameDish)
            {
                Dish temp = dishes[j];
                dishes[j] = dishes[j + 1];
                dishes[j + 1] = temp;
            }
        }
    }
}


void SaveDishToFile()
{
    ofstream outFile("dishes.bin", ios::binary | ios::out);
    if (!outFile)
    {
        cout << "Unable to open file.\n";
        return;
    }

    outFile.write((char*)&numDish, sizeof(numDish));
    outFile.write((char*)dishes, numDish * sizeof(Dish));
    outFile.close();
    cout << "Dishes saved to file successfully.\n";
}

void LoadDishesFromFile()
{
    ifstream inFile("dishes.bin", ios::binary | ios::in);
    if (!inFile)
    {
        cout << "Unable to open file or file does not exist.\n";
        return;
    }

    inFile.read((char*)&numDish, sizeof(numDish));
    inFile.read((char*)dishes, numDish * sizeof(Dish));
    inFile.close();

    cout << "Dishes loaded from file successfully.\n";
}

void ShowDish()
{
    for (int i = 0; i < numDish; ++i)
    {
        cout << endl;
        cout << "Dish name: " << dishes[i].nameDish << endl;
        cout << "Dish type: " << dishes[i].type << endl;
        cout << "Number of calories : " << dishes[i].quantity << endl;
        cout << "Weight: " << dishes[i].vaga << endl;

    }
}

int main()
{
    int choice;
    string dishNumber;

    LoadDishesFromFile();

    do {
        cout << "\nMenu:\n";
        cout << "1. Show dish\n";
        cout << "2. Add dish\n";
        cout << "3. Delete dish\n";
        cout << "4. Modify dish information\n";
        cout << "5. Sort dish by name of the dish\n";
        cout << "6. Save dish to file\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            ShowDish();
            break;

        case 2:
            AddDish();
            break;

        case 3:
            cout << "Enter dish number to delete: ";
            cin >> dishNumber;
            DeleteDish(dishNumber);
            break;

        case 4:
            cout << "Enter dish number to modify: ";
            cin >> dishNumber;
            ModifyDish(dishNumber);
            break;

        case 5:
            SortByNameDish();
            break;

        case 6:
            SaveDishToFile();
            break;
        case 7:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}
