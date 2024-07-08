#include "SystemManager.h"

int main() {
    SystemManager systemManager("system.db");
    systemManager.run();
    return 0;
}