#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


// Display a file ----------------------------------------------------------------------------

void display_file(const vector<string> &lines)
{
    cout << "\n--- File Contents ---\n";
    for (size_t i = 0; i < lines.size(); ++i)
    {
        cout << i + 1 << ": " << lines[i] << '\n';
    }
    cout << "---------------------\n";
}

void edit_file(vector<string> &lines)
{
    cout << "Enter the line number you want to edit( or 0 to stop): ";
    int line_number;
    cin >> line_number;

    while (line_number != 0)
    {
        if (line_number < 1 || line_number > lines.size())
        {
            cout << "Invalid line number. Try again: ";
        }
        else
        {
            cin.ignore(); // Clear the newline character from input buffer
            cout << "Enter new text for line " << line_number << ": ";
            string new_text;
            getline(cin, new_text);
            lines[line_number - 1] = new_text;
        }

        cout << "Enter the line number you want to edit (or 0 to stop): ";
        cin >> line_number;
    }
}

void save_file(const string &filename, const vector<string> &lines)
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error saving the file!" << endl;
        return;
    }
    for (const auto &line : lines)
    {
        outfile << line << '\n';
    }
    outfile.close();
    cout << "File saved successfully!" << endl;
}

int main()
{

    string filename;
    cout << "Enter the flename to open: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    vector<string> lines;
    string line;

    // Read file line by line
    while (getline(infile, line))
    {
        lines.push_back(line);
    }
    infile.close();
    display_file(lines);

    // Edit file content
    edit_file(lines);

    // Option to save the file
    char save;
    cout << "Do you want to save the file? (y/n): ";
    cin >> save;

    if (save == 'y' || save == 'Y')
    {
        save_file(filename, lines);
    }
    else
    {
        cout << "Changes not saved!" << endl;
    }

    return 0;
}