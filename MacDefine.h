#ifndef MAC_DEFINE
#define MAC_DEFINE
/******************************************************/
#define LINE_NUM 2
//像素的RGB结构
typedef struct tagPIXELCOLORRGB
{
	BYTE red;
	BYTE green;
	BYTE blue;
}PIXELCOLORRGB;
//进行形态运算定义的结构
typedef struct tagMORPHOLOGYELEMENT
{
	int x;
	int y;
	short red;
	short green;
	short blue;
}MORPHOLOGYELEMENT;
//定义的交通流参数结构
typedef struct tagTRANSPORTATIONFLOWPARAMETER
{
	int VehicleNumber1;
	short MinuteVehicleNum1;
	float Speed1;
	float TimeDensity1;	

	int VehicleNumber2;
	short MinuteVehicleNum2;
	float Speed2;
	float TimeDensity2;

	int VehicleNumber3;
	short MinuteVehicleNum3;
	float Speed3;
	float TimeDensity3;

	int VehicleNumber4;
	short MinuteVehicleNum4;
	float Speed4;
	float TimeDensity4;

	int VehicleNumberSum;
	short MinuteVehicleNumSum;
	float SpeedSum;
	float TimeDensitySum;
	

}TRANSPORTATIONFLOWPARAMETER;

#define BOUND(x,a,b) (((x)<(a))?(a):(((x)>(b))?(b):(x)))
#define ABS(x) (((x)<0)?-(x):(((x)>0):(x):0))
/******************************************************/
#endif