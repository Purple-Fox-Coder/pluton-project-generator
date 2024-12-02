#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

using std::filesystem::recursive_directory_iterator;
using std::filesystem::is_regular_file;
using std::filesystem::current_path;
using std::filesystem::absolute;
using std::filesystem::exists;
using std::filesystem::path;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::string;
using std::cout;
using std::endl;
using std::cin;

static const string s_versionNumber = "0.1.0";

void displayHelpMessage();
void findAndReplace(const string &p_findString, const string &p_replaceString,
  string &p_originalString);

int main(int p_argCount, char const *p_argValues[]) {

  const char* home = getenv("HOME");
  if (home == nullptr) {
    home = getenv("USERPROFILE");
  }

  path l_workingDirectory = path(current_path());
  path l_templateDirectory = path(home) / path("ppg/templates");
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
    cout <<
    "Please re-enter command with corrections, for help use: ppg -h" << endl;
    return 0;
  }

  // create project
  for (const path &i_file : recursive_directory_iterator(l_templateDirectory)) {
    if(is_regular_file(i_file)) {

      string l_fileName =
        i_file.string().substr(i_file.string().find_last_of("/\\") + 1);

      findAndReplace("PROJECT_NAME", l_name, l_fileName);
      findAndReplace("PROJECT_ALIAS", l_alias, l_fileName);

      ifstream l_templateFile(i_file);
      if(!l_templateFile.is_open()) {
        cout << "Could not read " << i_file << endl;
        continue;
      }

      ofstream l_outputFile(l_workingDirectory / l_fileName);
      if (!l_outputFile.is_open()) {
        cout << "Error creating the file " << l_fileName << endl;
        continue;
      }

      string l_line = "";

      while (getline(l_templateFile, l_line)) {
        findAndReplace("$$PROJECT_NAME$$", l_name, l_line);
        findAndReplace("$$PROJECT_ALIAS$$", l_alias, l_line);

        l_outputFile << l_line << endl;
      }

      l_templateFile.close();
      l_outputFile.close();

      cout << "Successfully created " << l_fileName << endl;
    } else {
      cout << "Skipping " << i_file << " because it is a directory" << endl;
    }
  }

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

void findAndReplace(const string &p_findString, const string &p_replaceString,
  string &p_originalString) {

  size_t l_replacePosition = p_originalString.find(p_findString);

  while (l_replacePosition != string::npos) {
    p_originalString.replace(
      l_replacePosition, p_findString.size(), p_replaceString
    );

    l_replacePosition = p_originalString.find(
      p_findString, l_replacePosition + p_replaceString.size()
    );
  }
}
