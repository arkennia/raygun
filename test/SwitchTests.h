#ifndef SWITCH_TESTS_H
#define SWITCH_TESTS_H

#define SWITCHPIN1 12
#define SWITCHPIN2 11
#define SWITCHPIN3 10
#define SWITCHPIN4 9

static class SwitchTests{
    public:
        SwitchTests();
        static void runAll();
    private:
        static void testSetting1();
        static void testSetting2();
        static void testSetting3();
        static void testSetting4();
        static void testSettingOff();
        static void testHoldState();
        static void testPowerOn();
}

#endif // SWITCH_TESTS_H
