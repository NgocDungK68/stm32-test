#include "stm32f1xx_hal.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

I2C_HandleTypeDef hi2c1;

// ================= I2C INIT =================
void MX_I2C1_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // PB6 = SCL, PB7 = SDA
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;

    HAL_I2C_Init(&hi2c1);
}

// ================= MAIN =================
int main(void)
{
    HAL_Init();
    MX_I2C1_Init();

    HAL_Delay(100); // 🔥 rất quan trọng
    // test I2C
    if (HAL_I2C_IsDeviceReady(&hi2c1, 0x78, 3, 100) != HAL_OK)
    {
        while(1); // ❌ treo = KHÔNG tìm thấy OLED
    }

    // Init OLED
    ssd1306_Init();

    // Clear màn
    ssd1306_Fill(Black);

    // Set vị trí
    ssd1306_SetCursor(10, 25);

    // In chữ
    ssd1306_WriteString("HELLO", Font_11x18, White);

    // Update màn hình
    ssd1306_UpdateScreen();

    while (1)
    {
    }
}