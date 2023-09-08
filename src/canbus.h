#ifndef CANBUS_H
#define CANBUS_H

#include <Arduino.h>

class canbus{

    public:

        int speed;  // speed kmh
        int gear;   // engaged gear
        int rpm;    // rpm
        int tps;    // percentage of tps opening

        canbus();

        void init();
        void refreshDatas();

};

#endif