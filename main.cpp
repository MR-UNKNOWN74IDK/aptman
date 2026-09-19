#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<unistd.h>
using namespace std;

// ANSI color definitions
const std::string RESET  = "\033[0m";
const std::string RED    = "\033[31m";
const std::string GREEN  = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN   = "\033[36m";
const std::string PURPLE = "\033[35m";

void moo() {
    cout <<"                  (__)" << endl;
    cout <<"                  (oo)" << endl;
    cout <<"            /------\\/" << endl;
    cout <<"           / |     ||" << endl;
    cout <<"          *  /\\---/\\" << endl;
    cout <<"             ~~   ~~" << endl;
    cout << R"(..."Have you mooed today?"...)" << std::endl;
}
void moomoo() {
    cout<<"                     ("<<YELLOW<<"__"<<RESET<<")"<<endl;
    cout<<RED<<"             -------"<<YELLOW<<"~("<<CYAN<<".."<<YELLOW<<")~"<<endl;
    cout<<YELLOW<<"               ,----"<<RED<<"\\"<<YELLOW<<"("<<PURPLE<<"oo"<<YELLOW<<")"<<endl;
    cout<<YELLOW<<"              /|____|,'"<<endl;
    cout<<YELLOW<<"               /\\   /\\"<<endl;
    cout<<GREEN<<"wWwWwWwWwWwWwWwWwWwWwWwWwWwWw"<<endl;
    cout<<"...\"Have you mooed today?\"..."<<endl;
}
void moomoomoo() {
    cout<<"                       \\ /"<<endl;
    cout<<"    mOOh  (__)        -(_)-"<<endl;
    cout<<"       \\  ~Oo~___      / \\"<<endl;
    cout<<"          (..)  |\\"<<endl;
    cout<<"____________|_|_|____________"<<endl;
    cout<<"...\"Have you mooed today?\"..."<<endl;

}





int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout<<R"(
aptman 1.1.4.514 (amd64)
Usage: apt [options] command

The command-line package manager apt provides package search,
management, and information query functions. It offers the same
functionality as other APT tools (like apt-get and apt-cache),
but is set up by default to be more suitable for interactive use.

Common commands:
list - list packages by name
search - search package descriptions
show - show package details
install - install packages
reinstall - reinstall packages
remove - remove packages
autoremove - automatically remove all unused packages
update - update the list of available packages
upgrade - upgrade the system by installing/upgrading packages
full-upgrade - upgrade the system by removing/installing/upgrading packages
edit-sources - edit source information files
modernize-sources - modernize .list files and rewrite them as .sources files
satisfy - satisfy dependency strings
                                )"<<YELLOW<<"This APT has Super Cow Powers."<<endl;
        return 1;
    }

    if (geteuid()!=0) {
        cerr<<RED<<"Weakling! You need root to even talk to me!"<<endl;
        return -1;
    }

    if (string(argv[1])=="moo") {
        if (argc>2&&string(argv[2])=="moo") {
            if (argc>3&&string(argv[3])=="moo") {
                moomoomoo();
                return 0;
            }
            moomoo();
            return 0;
        }
        moo();
        return 0;
    }

    std::string cmd = argv[1];
    std::vector<std::string> args(argv + 2, argv + argc);
    std::string pacman = "pacman ";

    // Ignore commands with no equivalent (category 3)
    if (cmd=="changelog"){cout<<RED<<"[Nope... there's no such thing] Arch doesn't have a changelog"<<endl<<YELLOW<<"Workaround: install asp from the AUR, then use the `asp log` command to view history~"<<endl<<CYAN<<"Such a weakling~"<<endl;return 0;}
    else if (cmd=="source"){cout<<RED<<"[Nope... there's no such thing] Arch doesn't have a source command"<<endl<<CYAN<<"Such a weakling~"<<endl;return 0;}
    else if (cmd=="edit-sources"){cout<<RED<<"[Nope... there's no such thing] Arch can't switch sources like that~"<<endl<<YELLOW<<"Workaround: edit `/etc/pacman.d/mirrorlist` with your *favorite* editor"<<endl<<CYAN<<"You'll have to do it yourself~"<<endl;return 0;}
    else if (cmd=="list"){cout<<RED<<"[Nope... there's no such thing] Arch doesn't support viewing lists like that"<<endl<<YELLOW<<"Workaround: install asp from the AUR, then use the `asp list-*` commands to view lists~"<<endl<<CYAN<<"Such a weakling~"<<endl;return 0;}
    else if (cmd=="satisfy"){cout<<RED<<"[Nope... there's no such thing] Arch doesn't have a satisfy command"<<endl<<CYAN<<"Such a weakling~"<<endl;return 0;}
    else if (cmd=="--fix-broken"){cout<<RED<<"[Nope... there's no such thing] If an install fails on Arch, it just rolls back~"<<endl<<CYAN<<"Get outta here~"<<endl;return 0;}
    else if (cmd=="--no-install-recommends"){cout<<RED<<"[Nope... there's no such thing] Arch doesn't auto-install recommended dependencies~ *all dependencies are mandatory* recommended deps are just hints"<<endl<<CYAN<<"All you can do is look~"<<endl;return 0;}
    else if (cmd=="-t"||cmd=="--target-release"){cout<<RED<<"[Nope... there's no such thing] Arch is a rolling release, you can't just pick a target whenever~"<<endl<<CYAN<<"It's mandatory~"<<endl;return 0;}
    else if (cmd=="-a"||cmd=="--architecture"){cout<<RED<<"[You don't need that] Arch handles architecture on its own, just let pacman do its thing..."<<endl<<CYAN<<"Enjoy~"<<endl;return 0;}


    // Category 1: direct mapping & Category 2: composed mapping
    if (cmd == "update") pacman += "-Sy";
    else if (cmd == "upgrade") pacman += "-Su";
    else if (cmd == "full-upgrade") pacman += "-Syu";
    else if (cmd == "clean") pacman += "-Scc";
    else if (cmd == "autoclean") pacman += "-Sc";
    else if (cmd == "autoremove" || cmd == "autopurge") pacman += "-Rns $(pacman -Qdtq)";
    else if (cmd == "-h" || cmd == "--help") pacman += "-h";
    else if (cmd == "-v" || cmd == "--version")cout<<GREEN<<"pacman fucked apt 114514 times"<<endl,pacman += "-V";
    else if (cmd == "install" || cmd == "reinstall") {
        pacman += "-S";
        for (const auto& a : args) {
            if (a == "-y" || a == "--yes") pacman += " --noconfirm";
            else if (a == "-d" || a == "--download-only") pacman = "pacman -Sw";
            else if (a == "--no-upgrade") pacman += " --needed";
            else if (a == "--reinstall") continue;
            else pacman += " " + a;
        }
    }
    else if (cmd == "remove") {
        bool purge = std::find(args.begin(), args.end(), "--purge") != args.end();
        pacman += purge ? "-Rns" : "-R";
        for (const auto& a : args) if (a != "--purge") pacman += " " + a;
    }
    else if (cmd == "purge") {
        pacman += "-Rns";
        for (const auto& a : args) pacman += " " + a;
    }
    else if (cmd == "search") {
        pacman += "-Ss";
        for (const auto& a : args) pacman += " " + a;
    }
    else if (cmd == "show") {
        pacman += "-Si";
        for (const auto& a : args) pacman += " " + a;
    }
    else if (cmd == "download") {
        pacman += "-Sw";
        for (const auto& a : args) pacman += " " + a;
    }
    else {
        std::cout << RED << "Unknown command: " << cmd << RESET << "\n";
        return 1;
    }

    // Print the converted result in color
    std::cout << GREEN << "Converted: " << RESET << pacman << "\n";
    cout<<RESET<<endl;
    // Uncomment to actually execute
    system(pacman.c_str());

    return 0;
}

