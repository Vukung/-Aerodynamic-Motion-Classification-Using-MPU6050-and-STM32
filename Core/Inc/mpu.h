#ifndef INC_MPU_H_
#define INC_MPU_H_

extern I2C_HandleTypeDef hi2c1;

#define MPU6050_ADDR            0xD0
#define MPU6050_PWR_MGMT_1      0x6B
#define MPU6050_ACCEL_XOUT_H    0x3B
#define MPU6050_ACCEL_YOUT_H    0x3D
#define MPU6050_ACCEL_ZOUT_H    0x3F
#define MPU6050_TEMP_OUT_H      0x41
#define MPU6050_GYRO_XOUT_H     0x43
#define MPU6050_GYRO_YOUT_H     0x45
#define MPU6050_GYRO_ZOUT_H     0x47

int16_t accel_data[3];
int16_t gyro_data[3];
int16_t temp_data[1];

float Ax, Ay, Az, Gx, Gy, Gz;
float tmp;

void MPU6050_Init(void)
{
  uint8_t data;

  // Wake up MPU6050
  data = 0x00;
  HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1, &data, 1, HAL_MAX_DELAY);
}

void MPU6050_Read_Accel(int16_t* accel_data)
{
  uint8_t buffer[6];

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, 1, buffer, 6, HAL_MAX_DELAY);

  accel_data[0] = (int16_t)((buffer[0] << 8) | buffer[1]);
  accel_data[1] = (int16_t)((buffer[2] << 8) | buffer[3]);
  accel_data[2] = (int16_t)((buffer[4] << 8) | buffer[5]);

  /* AFS_SEL: Full Scale Range and LSB Sensitivity
   *       0      Â±2g            16384 LSB/g
   *       1      Â±4g             8192 LSB/g
   *       2      Â±8g             4096 LSB/g
   *       3      Â±16g            2048 LSB/g
   */

  Ax = accel_data[0] / 16384.0;
  Ay = accel_data[1] / 16384.0;
  Az = accel_data[2] / 16384.0;
}

void MPU6050_Read_Gyro(int16_t* gyro_data)
{
  uint8_t buffer[6];

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_GYRO_XOUT_H, 1, buffer, 6, HAL_MAX_DELAY);

  gyro_data[0] = (int16_t)((buffer[0] << 8) | buffer[1]);
  gyro_data[1] = (int16_t)((buffer[2] << 8) | buffer[3]);
  gyro_data[2] = (int16_t)((buffer[4] << 8) | buffer[5]);

  /* FS_SEL: Full Scale Range and LSB Sensitivity
   *       0      Â±250 Â°/s        131 LSB/Â°/s
   *       1      Â±500 Â°/s         65.5 LSB/Â°/s
   *       2      Â±1000 Â°/s        32.8 LSB/Â°/s
   *       3      Â±2000 Â°/s        16.4 LSB/Â°/s
   */

  Gx = gyro_data[0] / 131.0;
  Gy = gyro_data[1] / 131.0;
  Gz = gyro_data[2] / 131.0;
}

/*
void MPU6050_Read_Temp(int16_t* temp_data)
{
  uint8_t buffer[2];

  HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_TEMP_OUT_H, 1, buffer, 2, HAL_MAX_DELAY);

  temp_data[0] = (int16_t)((buffer[0] << 8) | buffer[1]);
  //accel_data[1] = (int16_t)((buffer[2] << 8) | buffer[3]);
  //accel_data[2] = (int16_t)((buffer[4] << 8) | buffer[5]);

  // AFS_SEL: Full Scale Range and LSB Sensitivity
  //       0      Â±2g            16384 LSB/g
  //       1      Â±4g             8192 LSB/g
  //       2      Â±8g             4096 LSB/g
  //       3      Â±16g            2048 LSB/g
  //

  // tmp = temp_data[0] / 16384.0;
  //Ay = accel_data[1] / 16384.0;
  //Az = accel_data[2] / 16384.0;
}
*/

#endif /* INC_MPU_H_ */
