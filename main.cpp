
#include "TaskManager.hpp"

#include <iostream>

using namespace std;

int main()
{
    TaskManager task_manager;
    unsigned int number_of_jobs = 0;

    bool set_number_of_jobs = false;
    while (!set_number_of_jobs)
    {
       if (number_of_jobs > task_manager.getMaxNumberOfTasks())
       {
           cout << "> Max number of jobs to run is " << task_manager.getMaxNumberOfTasks() << ", please enter another number: ";
       }
       else
       {
           cout << "> Please enter number of jobs to run: ";
       }
       cin >> number_of_jobs;

       if (!cin)
       {
           cin.clear();
           cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

           cout << "> Try again with a valid number!" << endl;
       }
       else
       {
           set_number_of_jobs = task_manager.setNumberOfTasks(number_of_jobs);
       }
    }

    task_manager.registerTasks();

    std::string command;

    bool execute_commands = true;
    while (execute_commands)
    {
        cout << "> Please enter your command: ";
        cin >> command;

        if (!cin)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "> Try again with a valid command!" << endl;
        }
        else if (task_manager.checkCommand(command))
        {
            execute_commands = task_manager.executeCommand(command);
        }
        else
        {
            cout << "> " << command << "is not a valid command!" << endl;
        }
    }

    return 0;
}
