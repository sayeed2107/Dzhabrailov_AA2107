#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <map>

using namespace std;

struct Pipe
{
    float length;
    float diameter;
    bool status;
};

struct CS
{
    string name;
    int workshops;
    int active_workshops;
    float efficiency;
};

int GetCorrectNumber(int min, int max)
{
    int i;
    while ((cin >> i).fail() || i < min || i > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Choose action(0-9): ";
    }
    return i;
}

void GetCorrectStatus(Pipe &p)
{
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe status(Is it working or not, enter '1' or '0'): ";
        cin >> p.status;
    } while (cin.fail());
}

void GetCorrectActWorkshops(CS &st)
{
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter the amount of active workshops in CS: ";
        cin >> st.active_workshops;
    } while (cin.fail() || st.active_workshops > st.workshops || st.active_workshops < 0);
}

void GetCorrectObjectsView(const map<string, Pipe> &PipeMap, const map<string, CS> &CSMap)
{
    if (PipeMap.empty() == 1 && CSMap.empty() == 1)
    {
        cout << endl
             << "There are no objects to view" << endl;
    }
}

void AddToPipeMap(Pipe &p, map<string, Pipe> &PipeMap)
{
    string name;
    cout << "Enter name of the tube: ";
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, name);
    for (const auto &it : PipeMap)
    {
        if (name == it.first)
        {
            do
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Tube with such a name already exists, create different name: ";
                getline(cin, name);
            } while (name == it.first);
        }
    }
    PipeMap.insert(make_pair(name, p));
    return;
}

int AddToCsMap(CS &st, map<string, CS> &CSMap)
{
    for (const auto &it : CSMap)
    {
        if (st.name == it.first)
        {
            do
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Tube with such a name already exists, create different name: ";
                getline(cin, st.name);
            } while (st.name == it.first);
        }
    }
    CSMap.insert(make_pair(st.name, st));
    return 0;
}

void EditPipeMap(map<string, Pipe> &PipeMap)
{
    if (PipeMap.empty() == 1)
    {
        cout << endl
             << "There are no objects to edit" << endl;
        return;
    }

    string name;
    cout << "Enter name of the tube to change: ";
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, name);
    Pipe p = PipeMap[name];

    if (p.length == 0)
    {
        cout << endl
             << "There are no pipes with such a name, pleaese create a new pipe." << endl;
        PipeMap.erase(name);
        return;
    }

    bool old_status = p.status;
    GetCorrectStatus(p);
    if (old_status == p.status)
    {
        cout << endl
             << "Nothing was changed" << endl;
    }
    else
    {
        cout << endl
             << "Changes were applied!" << endl;
    }

    PipeMap[name] = p;
}

void EditCSMap(map<string, CS> &CSMap)
{
    if (CSMap.empty() == 1)
    {
        cout << endl
             << "There are no objects to edit" << endl;
        return;
    }

    string name;
    cout << "Enter name of the CS to change: ";
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, name);
    CS st = CSMap[name];

    if (st.workshops == 0)
    {
        cout << endl
             << "There are no CS with such name, pleaese create a new one." << endl;
        CSMap.erase(name);
        return;
    }

    int old_active_workshops = st.active_workshops;

    GetCorrectActWorkshops(st);
    if (old_active_workshops == st.active_workshops)
    {
        cout << endl
             << "Nothing was changed" << endl;
    }
    else
    {
        st.efficiency = (float)st.active_workshops / st.workshops * 100;
        cout << endl
             << "Changes were applied!" << endl;
    }

    CSMap[name] = st;
}

istream &operator>>(istream &in, Pipe &p)
{
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe length: ";
        cin >> p.length;
    } while (cin.fail() || p.length <= 0);
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe diameter: ";
        cin >> p.diameter;
    } while (cin.fail() || p.diameter <= 0);

    GetCorrectStatus(p);

    return in;
}

istream &operator>>(istream &in, CS &st)
{
    cout << "Enter CS name: ";
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, st.name);
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter the amount of workshops in CS: ";
        cin >> st.workshops;
    } while (cin.fail() || st.workshops <= 0);
    GetCorrectActWorkshops(st);
    st.efficiency = (float)st.active_workshops / st.workshops * 100;
    return in;
}

ostream &operator<<(ostream &out, const Pipe &p)
{
    out << "Length:" << p.length << "\tDiameter:" << p.diameter << "\tStatus:" << p.status << endl;
    return out;
}

ostream &operator<<(ostream &out, const CS &st)
{
    out << "Compressor station #" << st.name << endl;
    out << "Workshops:" << st.workshops << "\tActive workshops:" << st.active_workshops << "\tEfficiency:" << round(st.efficiency) << "%\n";
    return out;
}

ostream &operator<<(ostream &out, const map<string, CS> &CSMap)
{
    for (const auto &it : CSMap)
    {
        out << it.second << endl;
    }
    return out;
}

ostream &operator<<(ostream &out, const map<string, Pipe> &PipeMap)
{
    for (const auto &it : PipeMap)
    {
        out << "Pipe #" << it.first << endl;
        out << it.second << endl;
    }
    return out;
}

void DeleteTube(map<string, Pipe> &PipeMap)
{
    if (PipeMap.empty() == 1)
    {
        cout
            << "\nThere are no objects to delete\n";
        return;
    }
    string name;
    cout << PipeMap;
    cout << "Enter the name of the tube to be deleted: ";
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, name);
    Pipe p = PipeMap[name];

    if (p.length == 0)
    {
        cout << endl
             << "There are no pipes with such a name, pleaese create a new pipe." << endl;
        PipeMap.erase(name);
        return;
    }

    PipeMap.erase(name);
    cout << "\nTube was successfully deleted!\n";
}

void DeleteCS(map<string, CS> &CSMap)
{
    if (CSMap.empty() == 1)
    {
        cout
            << "\nThere are no objects to delete\n";
        return;
    }

    string name;
    cout << CSMap;
    cout << "Enter name of the CS to be deleted: ";
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, name);
    CS st = CSMap[name];

    if (st.workshops == 0)
    {
        cout << endl
             << "There are no CS with such name." << endl;
        CSMap.erase(name);
        return;
    }

    CSMap.erase(name);
    cout << "\nCS was successfully deleted!\n";
}

int SaveFile(const Pipe &p, const CS &s)
{
    if (p.length == 0 && s.workshops == 0)
    {
        cout << "Nothing to save, please create new objects. " << endl;
        return 0;
    }
    ofstream fout;
    fout.open("DataForHuman.txt", ios::out);
    if (p.length != 0)
    {
        fout << p << endl;
    }
    if (s.workshops != 0 && p.length != 0)
    {
        fout << "\n";
    }
    if (s.workshops != 0)
    {
        fout << s << endl;
    }
    fout.close();

    fout.open("DataForProgramm.txt", ios::out);
    if (s.workshops != 0 && p.length != 0)
    {
        fout << p.length << endl
             << p.diameter << endl
             << p.status << endl;
        fout << s.name << endl
             << s.workshops << endl
             << s.active_workshops << endl
             << round(s.efficiency);
    }
    if (p.length != 0 && s.workshops == 0)
    {
        fout << p.length << endl
             << p.diameter << endl
             << p.status << endl;
    }
    if (s.workshops != 0 && p.length == 0)
    {
        fout << endl
             << endl
             << endl;
        fout << s.name << endl
             << s.workshops << endl
             << s.active_workshops << endl
             << round(s.efficiency);
    }

    fout.close();
    cout << "File was succefully saved!" << endl;
    return 0;
}

Pipe LoadPipe()
{
    Pipe p;
    ifstream check("DataForProgramm.txt");
    if (check.bad() == true)
    {
        cout << "No existing file to load, please create a new file" << endl;
        return p;
    }

    ifstream fin;
    fin.open("DataForProgramm.txt", ios::in);
    fin >> p.length;
    fin >> p.diameter;
    fin >> p.status;
    fin.close();
    return p;
}

CS LoadCS()
{
    CS s;
    ifstream check("DataForProgramm.txt");
    if (check.bad() == true)
    {
        cout << "No existing file to load, please create a new file" << endl;
        return s;
    }

    ifstream fin;
    fin.open("DataForProgramm.txt", ios::in);
    fin.ignore(256, '\n');
    fin.ignore(256, '\n');
    fin.ignore(256, '\n');
    fin >> s.name;
    fin >> s.workshops;
    fin >> s.active_workshops;
    fin >> s.efficiency;
    fin.close();
    return s;
}

void PrintMenu()
{
    cout << "1. Add new pipe" << endl
         << "2. Add new CS" << endl
         << "3. View all objects" << endl
         << "4. Edit pipe" << endl
         << "5. Edit CS" << endl
         << "6. Delete Tube" << endl
         << "7. Delete CS" << endl
         << "8. Save to the file" << endl
         << "9. Load from the file" << endl
         << "0. Exit" << endl
         << "Choose action: ";
}

int main()
{
    Pipe p = {};
    CS st = {};
    map<string, Pipe> PipeMap;
    map<string, CS> CSMap;

    while (1)
    {
        cout << "\n";
        PrintMenu();
        switch (GetCorrectNumber(0, 9))
        {
        case 1:
        {
            cin >> p;
            AddToPipeMap(p, PipeMap);
            break;
        }
        case 2:
        {
            cin >> st;
            AddToCsMap(st, CSMap);
            break;
        }
        case 3:
        {
            GetCorrectObjectsView(PipeMap, CSMap);
            cout << PipeMap;
            cout << CSMap;
            break;
        }
        case 4:
        {
            EditPipeMap(PipeMap);
            break;
        }
        case 5:
        {
            EditCSMap(CSMap);
            break;
        }
        case 6:
        {
            DeleteTube(PipeMap);
            break;
        }
        case 7:
        {
            DeleteCS(CSMap);
            break;
        }
        case 8:
        {
            SaveFile(p, st);
            break;
        }
        case 9:
        {
            p = LoadPipe();
            st = LoadCS();
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong action";
        }
        }
    }
    return 0;
}