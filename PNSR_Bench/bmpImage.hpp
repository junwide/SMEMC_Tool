typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

typedef struct tagBITMAPFILEHEADER
{
    //WORD bfType;   // “BM”
    DWORD bfSize;     //File Size
    WORD bfReserved1; //Reserve
    WORD bfReserved2; //Reserve
    DWORD bfOffBits;  //File Head Offset to Real Data
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;          //信息头大小
    DWORD biWidth;         //图像宽度
    DWORD biHeight;        //图像高度
    WORD biPlanes;         //位平面数&#xff0c;必须为1
    WORD biBitCount;       //每像素位数
    DWORD biCompression;   //压缩类型
    DWORD biSizeImage;     //压缩图像大小字节数
    DWORD biXPelsPerMeter; //水平分辨率
    DWORD biYPelsPerMeter; //垂直分辨率
    DWORD biClrUsed;       //位图实际用到的色彩数
    DWORD biClrImportant;  //本位图中重要的色彩数
} BITMAPINFOHEADER;        //BMP Info header

typedef struct tagRGBQUAD
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD;


typedef struct tagIMAGEDATA
{
    BYTE red;
    BYTE green;
    BYTE blue;
} IMAGEDATA;

typedef struct Rotation_Maritx
{
    float one[3];
    float twe[3];
    float three[3];
} Rotation_M;