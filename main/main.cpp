#include <dirent.h>
#include <stdio.h>
#include <pwm/motor.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "i2c/i2c_device.h"
#include "i2c/cat24c256.h"
#include "i2c/bmp280.h"
#include "i2c/mpu6050.h"
#include "helpers/wifi.h"

#include "control/rotation_matrix.h"

extern "C" _Noreturn void app_main(void) {

    init_wifi("schinken", "gnampf");

    while (1) {
        vTaskDelay(100);
        printf("Running");
    }
}
