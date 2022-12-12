
#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

int main(int argc, char** argv){
    CLI::App thisApplication{"Hier ist die Programmbeschreibung für das Super CLI11 Demoprojekt", "Super CLI11 Demo"};
    
    std::string file;
    thisApplication.add_option("-f", file, "Database-File");

    try{
        thisApplication.parse(argc, argv);
    } catch(const CLI::ParseError& e){
        return thisApplication.exit(e);
    }


    std::ifstream databasefile{file};
    nlohmann::json database = nlohmann::json::parse(databasefile);

    for (auto& member : database["members"]){
        std::cout << "Old name: " << member["name"] << std::endl << "New Name: ";
        std::cin >> member["name"];
        std::cout << "Alright! New name is: " << member["name"] << std::endl;
    }

    std::cout << database.dump() << std::endl << std::endl;

    std::string save_path{};
    std::cout << "Save file as: ";
    std::cin >> save_path;

    std::ofstream save_as{save_path};
    save_as << database.dump();
    save_as.close();

}