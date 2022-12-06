#pragma once

/*
        Exponential regression:
        Gas    | a      | b
        LPG    | 44771  | -3.245
        CH4    | 2*10^31| 19.01
        CO     | 521853 | -3.821
        Alcohol| 0.3934 | -1.504
        Benzene| 4.8387 | -2.68
        Hexane | 7585.3 | -2.849
*/

struct Sensor {
        void Init();

        void Handler();
        void Debug();

        struct mq3Sens {
                void Calibrate(uint16_t ratioCleanAir);

                void readSens();

                void Debug(bool _st);
                bool getDebug();

                float getValue();

              private:
                float value;
                uint32_t mqTmr;
                bool _debug;

                void errMsg(bool err);
        } mq3;

        struct thermoCouple {
                void readSens();

                void Debug(bool _st);
                bool getDebug();

                float getValue();

                float getValueF();

              private:
                float value;
                uint32_t thrTmr;
                bool _debug;

                void errMsg();
        } thermo;

      private:
        uint32_t dbgTmr;
        bool debug[3] = { 0, 0, 0 };
        void errMsg();
};

extern Sensor sens;
