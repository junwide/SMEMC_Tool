#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

void ReadJson( rapidjson::Document &object, const std::string file_path)
{
    std::fstream fs;
    fs.open(file_path, std::fstream::in | std::fstream::out);
    if (!fs.is_open())
    {
        std::cout << "Read Json Error" << std::endl;
        return;
    }
    std::stringstream string_buffer;
    string_buffer << fs.rdbuf();
    fs.close();
    object.Parse(string_buffer.str().c_str());
}

void ConfigPares(
    std::string &origin_name,
    std::vector<std::string> &target_name,
    rapidjson::Document &object,
    std::uint16_t value)
{
    {
        const rapidjson::Value &image_set = object["Image_True"];
        origin_name = image_set[0]["name"].GetString();

    }
    {
        const rapidjson::Value &Smemc_set = object["Image_SMEMC"];
        for (rapidjson::SizeType i = 0; i < Smemc_set.Size(); i++)
        {
            target_name.push_back(Smemc_set[i]["name"].GetString());
        }
    }
    {
        const rapidjson::Value &Smemc_set = object["Threshold"];
        value = Smemc_set.GetInt();
    }
}