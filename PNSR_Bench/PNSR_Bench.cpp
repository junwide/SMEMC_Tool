#include <cmath>
#include <cstdlib>
#include <unordered_map>

#include "jsonParse.hpp"
#include "bmpImage.hpp"

#define MAXI 255 * 255
uint16_t Threshold  = 3;

using namespace std;

int width, height; 


void ReadDataFromImage(string name, IMAGEDATA *&output)
{
    FILE *fpi;
    fpi = fopen(name.c_str(), "rb");
    if (fpi == NULL)
    {
        cout << "error file open !!! Please Check!" << endl;
        return;
    }
    WORD bfType;
    BITMAPFILEHEADER FileHead;
    BITMAPINFOHEADER ImageInfo;
    static int index = 0;
    fread(&bfType, 1, sizeof(WORD), fpi);
    if (0x4d42 != bfType)
    {
        cout << "The file is not a bmp file!" << endl;
        return;
    }
    fread(&FileHead, 1, sizeof(tagBITMAPFILEHEADER), fpi);
    fread(&ImageInfo, 1, sizeof(tagBITMAPINFOHEADER), fpi);
    width = ImageInfo.biWidth;
    height = ImageInfo.biHeight;
    int DataSize = width * height;
    output = new IMAGEDATA[DataSize]{};
    fread(output, sizeof(struct tagIMAGEDATA), DataSize, fpi);
    fclose(fpi);
}

// FS Compare
double Calculate_Accuracy(IMAGEDATA *origin, IMAGEDATA* target)
{
    double sum = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (abs(origin[j * width + i].red -  target[j * width + i].red) > Threshold)
            {
                sum++;
                continue;
            }
            if (abs(origin[j * width + i].green -  target[j * width + i].green) > Threshold)
            {
                sum++;
                continue;
            }
            if (abs(origin[j * width + i].blue -  target[j * width + i].blue) > Threshold)
            {
                sum++;
                continue;
            }
        }
    }
    return  1.f - sum / ( width * height);
}

// PNSR
double Calculate_PNSR(IMAGEDATA *origin, IMAGEDATA* target)
{
    double sum = 0.f;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sum += pow(origin[j * width + i].red -  target[j * width + i].red, 2);
            sum += pow(origin[j * width + i].green -  target[j * width + i].green, 2);
            sum += pow(origin[j * width + i].blue -  target[j * width + i].blue, 2);
        }
    }
    double MSE = sum / ( width * height * 3);
    return 10 * log10(MAXI / MSE);
}


int main()
{
    string origin_image;
    vector<string> target_set;
    unordered_map<string, IMAGEDATA *> image_map;

    rapidjson::Document object_json;
	ReadJson(object_json, "./imageConfig.json");
    ConfigPares(origin_image, target_set, object_json, Threshold);

    image_map[origin_image] = NULL;

    for ( auto name: target_set)
    {
        image_map[name] = NULL;
    }

    ///
    cout << "Bench Test:" << endl;

    for ( auto item : image_map)
    {  
        ReadDataFromImage(item.first, image_map[item.first]);
    }

    {
        int index = 1;
        for ( auto name: target_set)
        {
            double result_PNSR = Calculate_PNSR(image_map[origin_image], image_map[name]);
            double result_ACCU = Calculate_Accuracy(image_map[origin_image], image_map[name]);
            cout << "Bench Result With "<< index++ <<": PNSR "<< result_PNSR << "dB"
                 << " Accuracy " << result_ACCU << endl;
        }
    }
    cout << "PNSR Bench End" << endl;
    /// free Memory
    for (auto item : image_map)
    {
        delete [] image_map[item.first];
    }
    
    return 0;
}