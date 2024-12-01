#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

using std::filesystem::current_path;
using std::filesystem::absolute;
using std::filesystem::exists;
using std::filesystem::path;
using std::getline;
using std::string;
using std::cout;
using std::endl;
using std::cin;

static const string s_versionNumber = "0.1.0";

void displayHelpMessage();

int main(int p_argCount, char const *p_argValues[]) {

  path l_workingDirectory = path(current_path());
  path l_templateDirectory = path("./templates");
  string l_name = "ppgProject";
  string l_alias = "main";

  // get information from the arguments
  if (p_argCount > 1) {
    int l_argCheckStart = 1;

    if (exists(path(p_argValues[0])) && path(p_argValues[0]).is_absolute()) {

      l_workingDirectory = p_argValues[0];
      l_argCheckStart++;
    } else if(exists(absolute(l_workingDirectory / path(p_argValues[1])))) {

      l_workingDirectory = absolute(l_workingDirectory / path(p_argValues[1]));
      l_argCheckStart++;
    }

    for (int i = l_argCheckStart; i < p_argCount; i++) {

      if("-t" == string(p_argValues[i])) {
        l_templateDirectory =
          i + 1 <= p_argCount ?

            exists(p_argValues[i + 1]) ?

              path(p_argValues[i + 1]) :

              l_templateDirectory :
            l_templateDirectory;
        i++;
      }
      if("-n" == string(p_argValues[i])) {
        l_name = string(p_argValues[i + 1]);
        l_alias = l_alias == "main" ? l_name : l_alias;
        i++;
      }
      if("-a" == string(p_argValues[i])) {
        l_alias = string(p_argValues[i + 1]);
        i++;
      }
      if("-h" == string(p_argValues[i])) {
        displayHelpMessage();
        return 0;
      }
      if("-v" == string(p_argValues[i])) {
        cout << "PPG version: " << s_versionNumber << endl;
        return 0;
      }
    }
  }

  if (!exists(l_templateDirectory)) {
    cout << "Template directory missing!" << endl;
    return 0;
  }

  cout <<
    "Project name: " << l_name << endl <<
    "Project alias: " << l_alias << endl <<
    endl <<
    "Template directory: " << l_templateDirectory << endl <<
    "Project directory: " << l_workingDirectory << endl <<
    endl <<
    "Is this information correct? (Y/n): ";

  string l_answer = "";


  while (true) {
      getline(cin, l_answer);

      // validate input
      if (l_answer != "y" && l_answer != "Y" &&
          l_answer != "n" && l_answer != "N") {

          // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          cout << "Invalid input! Please y or n: ";
      } else {
          // Valid input
          break;
      }
  }

  if (l_answer == "n" || l_answer == "N") {
    cout << "Please re-enter command with corrections, for help use: ppg -h" << endl;
    return 0;
  }

  // create project

  return 0;
}

void displayHelpMessage() {
  cout <<
    "PPG version: " << s_versionNumber << endl <<
    endl <<
    "USAGE: ppg <directory to make project> <PARAMETERS>" << endl <<
    endl <<
    "PARAMETERS:" << endl <<
    "-t" << "  " << "Sets the template directory (-t <DIRECTORY>)" << endl <<
    "-n" << "  " << "Sets the project name (-n <NAME>)" << endl <<
    "-a" << "  " << "Sets the project alias (-a <ALIAS>)" << endl <<
    "-h" << "  " << "Displays this message" << endl <<
    "-v" << "  " << "Displays the version number" << endl;
}
