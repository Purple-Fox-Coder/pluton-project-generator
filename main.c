#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "ppgProject.h"

int main(int argc, char const *argv[]) {
  const char* home = "~"; //getenv("HOME");
  if (home == NULL) {
    home = "~"; // getenv("USERPROFILE");
  }

  PPGProject projectInfo;
  projectInfo.workingDirectory = "~"; // get current working directory
  projectInfo.templateDirectory = PPG_DEFAULTTMPDIR;
  projectInfo.projectName = PPG_DEFAULTNAME;
  projectInfo.projectAlias = PPG_DEFAULTALIAS;

  parseArgs(argc, argv, &projectInfo);
  requestMoreInfo(&projectInfo);

  printf("Project name: %s\nProject alias: %s\n\nTemplate directory: %s\nProject directory: %s\n\n",
    projectInfo.projectName, projectInfo.projectAlias,
    projectInfo.templateDirectory, projectInfo.workingDirectory);
  printf("Is this information correct? (Y/n)");

  if(awaitYesOrNo() == 0) {
    printf("Please re-enter command with corrections, for help use: ppg -h\n");
    return 0;
  }

  generateProject(&projectInfo);

  return 0;
}
