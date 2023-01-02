#pragma once

struct UserInterface {
        void Init();
        void Handler();
        String parseStr(String data,
                        char separator[],
                        int index);

        void parseIn();

      private:
        uint32_t uiTmr;
};

extern UserInterface ui;
