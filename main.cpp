#include "RotationLogger/Logger.h"

using namespace std;

int main() {
    Logger logger = Logger(4, 60, "/Users/user/Documents/workspace/git_repositories/RotationLogger/");
    char chrs[1];

    for (int i = 0; i < 55; i++) {
        chrs[0] = (char) (i + 55);
        std::string str(chrs);
        logger.DateWrite(str);
    }

    return 0;

}
