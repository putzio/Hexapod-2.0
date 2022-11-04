#include <gtest/gtest.h>

#include "Logic/SlaveServo.hpp"

TEST(SlaveServo, test_slave_servo_init)
{
    SlaveServo slave;
}

TEST(SlaveServo, test_slave_change_hight_to_15000)
{
    SlaveServo slave;
    uint16_t newHight = 15000;
    Result r = slave.ChangeHight(newHight);
    ASSERT_EQ(kOkResult, r);
    ASSERT_EQ(newHight, slave.GetHight());
}

TEST(SlaveServo, test_slave_change_hight_to_7000)
{
    SlaveServo slave;
    uint16_t newHight = 7000;
    Result r = slave.ChangeHight(newHight);
    ASSERT_EQ(kHightOutOfRange, r);
    ASSERT_EQ(DEFAULT_HIGHT, slave.GetHight());
}

TEST(SlaveServo, test_slave_change_hight_to_60000)
{
    SlaveServo slave;
    uint16_t newHight = 60000;
    Result r = slave.ChangeHight(newHight);
    ASSERT_EQ(kHightOutOfRange, r);
    ASSERT_EQ(DEFAULT_HIGHT, slave.GetHight());
}

TEST(SlaveServo, test_calculating_position_45_deg_foreward)
{
    SlaveServo slave(SlaveServo::leftServo, SlaveServo::slaveForward);
    uint8_t masterPosition = 45;
    slave.ChangeHight(14142);
    slave.enableSlave = true;
    slave.UpdateSlavePosition(masterPosition);
    
    ASSERT_EQ(true, slave.enableSlave);
    ASSERT_EQ(180, slave.position);
}

TEST(SlaveServo, test_calculating_position_45_deg_back)
{
    SlaveServo slave(SlaveServo::leftServo, SlaveServo::slaveBack);
    uint8_t masterPosition = 45;
    slave.ChangeHight(14142);
    slave.enableSlave = true;
    slave.UpdateSlavePosition(masterPosition);
    
    ASSERT_EQ(true, slave.enableSlave);
    ASSERT_EQ(0, slave.position);
}