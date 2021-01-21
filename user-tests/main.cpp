#include "main.h"

int main(int argc, char* argv[])
{
    std::string cli_output;
    bool all_packs_installed;
    std::vector<std::string> lines;
    std::vector<std::string> packages;
    std::string arg1 = "";

    if (argv[1] != NULL)
        arg1 = argv[1];
    
    switch (getOption(arg1))
    {
        case Option::Default: 
            cli_output = execCLI("tlmgr list --only-installed");
            getLinesOutput(cli_output, lines);
            getNamePackages(lines, packages);
            all_packs_installed = checkPackagesInstalled(packages);
            break;
        case Option::ManualConfig:
            cli_output = execCLI("whoami");
            cli_output.pop_back(); // eliminando salto de linea
            initFoldersVector(cli_output);
            all_packs_installed = findFolders();
            break;
        case Option::Help: help(); break;
        case Option::Version: version(); break;
        default: invalidOption(); break;
    }

    return all_packs_installed? EXIT_SUCCESS : EXIT_FAILURE;
}

/**
 * Funcion elaborada por el Ing. Ivan Deras
 * Clase de Compiladores 2 Q4 2020
 * Universidad Tecnologica Centroamericana
*/
std::string execCLI(const std::string& cmd)
{
    FILE *stream = popen(cmd.c_str(), "r");
    if (stream == nullptr)
        return "error executing command: " + cmd;
    
    std::ostringstream oss;
    char buffer[4096];

    while(fgets(buffer, sizeof(buffer)-1, stream))
        oss << buffer;
    
    return oss.str();
}

void getLinesOutput(std::string& cli_output, std::vector<std::string>& lines)
{
    char* token;
    token = std::strtok(const_cast<char*>(cli_output.c_str()), "\n");

    while (token != NULL)
    {
        if (token[0] == 'i')
            lines.push_back(std::string(token));
        token = std::strtok(NULL, "\n");
    }
}

void getNamePackages(std::vector<std::string>& lines, std::vector<std::string>& packages)
{
    std::string pack;

    for (auto l : lines)
    {
        for (auto i = 2; l[i] != ':'; i++)
            pack.push_back(l[i]);
        packages.push_back(pack);
        pack.clear();
    }
}

bool checkPackagesInstalled(std::vector<std::string>& packages)
{
    Color color;
    bool all_packs_installed = true;
    std::string username;
    std::vector<std::string>::iterator it;

    for (auto pckreq : packs_required)
    {
        it = std::find(packages.begin(), packages.end(), pckreq);
        
        if (it != packages.end())
            std::cout << color.open(Color::BrightGreen) 
                << emoji::emojize(":heavy_check_mark: ") 
                << color.close() << pckreq << std::endl;
        else {
            std::cout << color.open(Color::BrightRed)
                << emoji::emojize(":x: ") << color.close() << pckreq 
                << "\t\t" << emoji::emojize(" :point_right: ") 
                << "execute: tlmgr install " << pckreq << std::endl;
                all_packs_installed = false;
        }
    }

    username = execCLI("whoami");
    username.pop_back(); // eliminando salto de linea
    if (!folderExists("/home/" + username + "/texmf/tex/latex/setspace"))
        all_packs_installed = false;
        
    return all_packs_installed;
}

void help()
{
    std::cout << std::endl;
    std::cout << "\tHerramienta para la validacion de paquetes LaTeX. La validacion de paquetes puede ser "
            << "\n\ta traves de tlmgr (por defecto) o por configuracion manual." << std::endl;
    std::cout << std::endl;
    std::cout << " --manual-config\tEn lugar de buscar los paquetes LaTeX con tlmgr, busca que las carpetas correspondientes" 
            << "\n\t\t\ta los paquetes existan en el sistema. Buscara las carpetas en la ruta:"
            << "\n\t\t\t/home/<your user>/texmf/tex/latex/"
            << "\n\t\t\tNOTA: chktex no valida el contenido de la carpeta, solamente valida que exista." << std::endl;
    std::cout << " --version\t\tMuestra la version de chktex" << std::endl;

}

void version()
{
    std::cout << "v1.0.0" << std::endl;
}

void invalidOption()
{
    Color color;
    std::cout << "Opcion invalida, ejecute: ./chktex "
    << color.open(Color::BrightYellow) << " --help" << color.close() << std::endl;
}

Option getOption(std::string option)
{
    if (option == "") return Option::Default;
    if (option == "--help") return Option::Help;
    if (option == "--version") return Option::Version;
    if (option == "--manual-config") return Option::ManualConfig;

    return Option::Invalid;
}

void initFoldersVector(std::string username)
{
    std::string home = "/home/";
    std::string texmf = "/texmf";
    std::string tex = "/tex";
    std::string latex = "/latex";

    folders_required.push_back(home + username + texmf);
    folders_required.push_back(home + username + texmf + tex);
    folders_required.push_back(home + username + texmf + tex + latex);
    folders_required.push_back(home + username + texmf + tex + latex + "/subfigure");
    folders_required.push_back(home + username + texmf + tex + latex + "/setspace");
}

bool findFolders()
{
    bool all_packs_installed = true;

    std::cout << "verificando que las carpetas requeridas existan..." << std::endl;
    usleep(500000);

    for (const auto &fr : folders_required) 
    {
        if (!folderExists(fr))
            all_packs_installed = false;
        usleep(100000);
    }

    return all_packs_installed;
}

bool folderExists(const std::string& path)
{
    DIR *folder;
    Color color;
    bool status = true;

    if (folder = opendir(path.c_str())) {
        std::cout << color.open(Color::BrightGreen) 
                << emoji::emojize(":heavy_check_mark: ") 
                << color.close() << path << "/" << std::endl;
        closedir(folder);
    } else {
        std::cout << color.open(Color::BrightRed)
                << emoji::emojize(":x: ") << color.close() 
                << path << "/" << std::endl;
        status = false;
    }

    return status;
}