#include <Adafruit_MLX90640.h>

Adafruit_MLX90640 mlx;
float frameBuffer[32*24];

void initMLX90640() {
  mlx.begin(MLX90640_I2CADDR_DEFAULT,&Wire);
  mlx.setMode(MLX90640_CHESS); //INTERLEAVED,CHESS
  mlx.setResolution(MLX90640_ADC_18BIT); //16,17,18,19
  mlx.setRefreshRate(MLX90640_16_HZ); //0_5,1,2,4,8,16,32,64
  Wire.setClock(1000000); }

void getFrame() { mlx.getFrame(frameBuffer); }
