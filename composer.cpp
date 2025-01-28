#include <iostream>
#include <string>
#include <filesystem>
#include <libloaderapi.h>
#include <unistd.h>

using namespace std;

bool checkPHP() {
    int check = system("where /q php || exit 1");

    return check == 0 ? true : false;
}

string getPath() {
    wchar_t path[FILENAME_MAX] = {0};
    GetModuleFileNameW(nullptr, path, FILENAME_MAX);
    filesystem::path current_path = filesystem::path(path).parent_path();

    return current_path.string();
}

void installComposer() {
    cout << "Info: Dang tien hanh cai dat Composer" << endl;
    system("php -r \"copy('https://getcomposer.org/installer', 'composer-setup.php');\"");
    system("php -r \"if (hash_file('sha384', 'composer-setup.php') === 'dac665fdc30fdd8ec78b38b9800061b4150413ff2e3b6f88543c636f7cd84f6db9189d43a81e5503cda447da73c7e5b6') { echo 'Installer verified'; } else { echo 'Installer corrupt'; unlink('composer-setup.php'); } echo PHP_EOL;\"");
    system((char*) ("php composer-setup.php --install-dir \"" + getPath() + "\"").c_str());
    system("php -r \"unlink('composer-setup.php');\"");
    cout << "Info: Cai dat Composer thanh cong" << endl;
    sleep(3);
    system("cls");
}

int main(int argc, char *argv[]) {
    if (checkPHP()) {
        if (!std::filesystem::exists(getPath() + "/composer.phar")) {
            installComposer();
        }

        string command = "php " + getPath() + "/composer.phar";
        if (argc > 1) {
            command += " ";
            for (int i = 1; i < argc; ++i) {
                command += string(argv[i]) + " ";
            }
            command.erase(command.find_last_not_of(" ") + 1);
        }

        system((char*) command.c_str());
    } else {
        cout << "Error: Vui long tai PHP" << endl;
    }

    return 0;
}
