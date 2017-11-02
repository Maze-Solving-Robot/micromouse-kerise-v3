#pragma once

#include <Arduino.h>
#include <deque>

#include "motor.h"
#include "icm20602.h"
#include "as5048a.h"

class Position {
  public:
    float x, y, theta;
  public:
    Position(const float x = 0, const float y = 0, const float theta = 0) : x(x), y(y), theta(theta) {}
    Position(const float pos[3]) : x(pos[0]), y(pos[1]), theta(pos[2]) {}

    void reset() {
      x = 0; y = 0; theta = 0;
    }
    void set(const float x = 0, const float y = 0, const float theta = 0) {
      this->x = x; this->y = y; this->theta = theta;
    }
    Position rotate(const float angle) {
      float _x = x;
      float _y = y;
      x = _x * cos(angle) - _y * sin(angle);
      y = _x * sin(angle) + _y * cos(angle);
      return *this;
    }
    float getNorm() const {
      return sqrt(x * x + y * y);
    }
    Position mirror_x() const {
      return Position(x, -y, -theta);
    }

    Position operator=(const Position &obj) {
      x = obj.x; y = obj.y; theta = obj.theta; return *this;
    }
    Position operator+() const {
      return Position(x, y, theta);
    }
    Position operator+(const Position &obj) const {
      return Position(x + obj.x, y + obj.y, theta + obj.theta);
    }
    Position operator+=(const Position &obj) {
      x += obj.x; y += obj.y; theta += obj.theta; return *this;
    }
    Position operator-() const {
      return Position(-x, -y, -theta);
    }
    Position operator-(const Position &obj) const {
      return Position(x - obj.x, y - obj.y, theta - obj.theta);
    }
    Position operator-=(const Position &obj) {
      x -= obj.x; y -= obj.y; theta -= obj.theta; return *this;
    }
    inline void print(const char* name = "Pos") {
      printf("%s: (%.1f,\t%.1f,\t%.3f)\n", name, x, y, theta);
    }
};

#define SPEED_CONTROLLER_TASK_PRIORITY  4
#define SPEED_CONTROLLER_STACK_SIZE     4096

#define SPEED_CONTROLLER_KP   1.0f
#define SPEED_CONTROLLER_KI   12.0f
#define SPEED_CONTROLLER_KD   0.0f

#define SPEED_CONTROLLER_PERIOD_US  1000

class SpeedController {
  public:
    struct WheelParameter {
      public:
        float trans;    //< translation
        float rot;      //< rotation
        float wheel[2]; //< wheel [0]: left, [1]: right
      public:
        WheelParameter(const float trans = 0, const float rot = 0) : trans(trans), rot(rot) {}
        void pole2wheel() {
          wheel[0] = trans - MACHINE_ROTATION_RADIUS * rot;
          wheel[1] = trans + MACHINE_ROTATION_RADIUS * rot;
        }
        void wheel2pole() {
          rot = (wheel[1] - wheel[0]) / 2.0f / MACHINE_ROTATION_RADIUS;
          trans = (wheel[1] + wheel[0]) / 2.0f;
        }
        void clear() {
          trans = 0;
          rot = 0;
          wheel[0] = 0;
          wheel[1] = 0;
        }
        const struct WheelParameter& operator =(const struct WheelParameter& obj) {
          trans = obj.trans;
          rot = obj.rot;
          wheel[0] = obj.wheel[0];
          wheel[1] = obj.wheel[1];
          return *this;
        }
    };
    WheelParameter target;
    WheelParameter actual;
    //    WheelParameter actual2;
    //    WheelParameter actual3;
    WheelParameter proportional;
    WheelParameter integral;
    WheelParameter differential;
    WheelParameter pwm_value;
    float Kp = SPEED_CONTROLLER_KP;
    float Ki = SPEED_CONTROLLER_KI;
    float Kd = SPEED_CONTROLLER_KD;

  public:
    SpeedController() {
      enabled = false;
      reset();
      xTaskCreate([](void* obj) {
        static_cast<SpeedController*>(obj)->task();
      }, "SpeedController", SPEED_CONTROLLER_STACK_SIZE, this, SPEED_CONTROLLER_TASK_PRIORITY, NULL);
    }
    void reset() {
      target.clear();
      actual.clear();
      integral.clear();
      differential.clear();
      actual_prev.clear();
      target_prev.clear();
      for (int i = 0; i < 2; i++) {
        wheel_buffer[i].resize(0);
        float pos = as.position(i);
        wheel_buffer[i].resize(ave_num, pos);
        for (int j = 0; j < ave_num; j++) {
          accel[j] = 0;
          gyro[j] = 0;
        }
      }
      position.reset();
    }
    void enable(bool suction = false) {
      Kp = SPEED_CONTROLLER_KP;
      Ki = SPEED_CONTROLLER_KI;
      Kd = SPEED_CONTROLLER_KD;
      reset();
      enabled = true;
      printf("Speed Controller Enabled\n");
    }
    void disable() {
      enabled = false;
      delay(1);
      mt.free();
    }
    void set_target(float trans, float rot) {
      target.trans = trans;
      target.rot = rot;
      target.pole2wheel();
    }
    Position& getPosition() {
      return position;
    }
  private:
    bool enabled;
    static const int ave_num = 16;
    float accel[ave_num];
    float gyro[ave_num];
    WheelParameter actual_prev;
    WheelParameter target_prev;
    std::deque<float> wheel_buffer[2];
    Position position;

    void task() {
      portTickType xLastWakeTime;
      xLastWakeTime = xTaskGetTickCount();
      while (1) {
        vTaskDelayUntil(&xLastWakeTime, 1 / portTICK_RATE_MS);
        if (!enabled) {
          //          mt.free();
          continue;
        }
        for (int i = 0; i < 2; i++) {
          wheel_buffer[i].push_back(as.position(i));
          wheel_buffer[i].pop_front();
        }
        for (int j = ave_num - 1; j > 0; j--) {
          accel[j] = accel[j - 1];
          gyro[j] = gyro[j - 1];
        }
        accel[0] = icm.accel.y;
        gyro[0] = icm.gyro.z;
        float sum_accel = 0.0f;
        for (int j = 0; j < ave_num - 1; j++) {
          sum_accel += accel[j];
        }
        for (int i = 0; i < 2; i++) {
          actual.wheel[i] = (wheel_buffer[i].back() - wheel_buffer[i].front()) / (ave_num - 1) * 1000000 / SPEED_CONTROLLER_PERIOD_US + sum_accel * SPEED_CONTROLLER_PERIOD_US / 1000000 / 2;
        }
        actual.wheel2pole();
        //        actual.rot = icm.gyro.z;
        actual.pole2wheel();
        for (int i = 0; i < 2; i++) {
          integral.wheel[i] += (target.wheel[i] - actual.wheel[i]) * SPEED_CONTROLLER_PERIOD_US / 1000000;
          proportional.wheel[i] = target.wheel[i] - actual.wheel[i];
        }
        differential.trans = (target.trans - target_prev.trans) / SPEED_CONTROLLER_PERIOD_US * 1000000 - (accel[0] + accel[1] + accel[2]) / 3;
        differential.rot = (target.rot - target_prev.rot) / SPEED_CONTROLLER_PERIOD_US * 1000000 - (gyro[0] - gyro[ave_num - 1]) / (ave_num - 1) / SPEED_CONTROLLER_PERIOD_US * 1000000;
        differential.pole2wheel();
        for (int i = 0; i < 2; i++) {
          pwm_value.wheel[i] = Kp * proportional.wheel[i] + Ki * integral.wheel[i] + Kd * differential.wheel[i];
        }
        mt.drive(pwm_value.wheel[0], pwm_value.wheel[1]);

        proportional.wheel2pole();
        integral.wheel2pole();

        position.theta += (actual_prev.rot + actual.rot) / 2 * SPEED_CONTROLLER_PERIOD_US / 1000000;
        position.x += (actual_prev.trans + actual.trans) / 2 * cos(position.theta) * SPEED_CONTROLLER_PERIOD_US / 1000000;
        position.y += (actual_prev.trans + actual.trans) / 2 * sin(position.theta) * SPEED_CONTROLLER_PERIOD_US / 1000000;

        actual_prev = actual;
        target_prev = target;
      }
    }
};

extern SpeedController sc;

