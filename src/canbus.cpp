#include "canbus.h"
#include <Arduino.h>
#include <driver/can.h>
#include <driver/gpio.h>


canbus::canbus() {

}

void canbus::init() {
    can_general_config_t general_config {
        .mode = CAN_MODE_NORMAL,
        .tx_io = (gpio_num_t)GPIO_NUM_22,
        .rx_io = (gpio_num_t)GPIO_NUM_21,
        .clkout_io = (gpio_num_t)CAN_IO_UNUSED,
        .bus_off_io = (gpio_num_t)CAN_IO_UNUSED,
        .tx_queue_len = 0,
        .rx_queue_len = 65,
        .alerts_enabled = CAN_ALERT_ALL,
        .clkout_divider = 0
    };

    can_timing_config_t timing_config = CAN_TIMING_CONFIG_125KBITS();
    can_filter_config_t filter_config = CAN_FILTER_CONFIG_ACCEPT_ALL();

    esp_err_t error;
    error = can_driver_install(&general_config,&timing_config,&filter_config);

    if(error==ESP_OK) {
        Serial.println("Can driver installation OK");
    } else {
        Serial.println("Can driver installation NOK");
        return;
    };

    error = can_start();

    if(error==ESP_OK){
        Serial.println("Can Driver started");
    }else{
        Serial.println("Can Driver failed to start");
        return;
    }

}

void canbus::refreshDatas() {

    can_message_t rx_frame;
    if(can_receive(&rx_frame,pdMS_TO_TICKS(1000))==ESP_OK){

        if (rx_frame.identifier==0x00000080){

            canbus::rpm = (rx_frame.data[2] << 8) | rx_frame.data[3];
            canbus::speed = (rx_frame.data[0] << 8) | rx_frame.data[1];
            int readvalue = rx_frame.data[4];
            canbus::tps = (readvalue*100)/122; //put 122 for now but 
      
        }

    }


}

