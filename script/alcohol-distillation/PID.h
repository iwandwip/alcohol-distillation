#pragma once

struct PID {
        void SetLimit(float mn, float mx);
        void SetConstants(float kp, float ki, float kd, float ts);
        void Calculate(float sp, float av);
        float GetResult(void);
        void Reset(void);
        float GetError();

      private:
        float mn, mx;
        float kp, ki, kd, ts;
        float e, se, le, de, u;
        uint32_t timer;
};

extern PID pid;