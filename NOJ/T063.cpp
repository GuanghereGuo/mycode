//
// Created by 24087 on 24-10-15.
//
#include <iomanip>
#include <iostream>

struct PIDController {
    double Kp, Ki, Kd;
    double preError, integral;
};

double PIDCalculate(PIDController &pid, double setPoint, double measuredValue) {
    double error = setPoint - measuredValue;
    pid.integral += error;
    double differential = error - pid.preError;
    double output = pid.Kp * error + pid.Ki * pid.integral + pid.Kd * differential;
    pid.preError = error;
    return output;
}

int main() {
    double setPoint, measuredValue;
    int time;
    PIDController pid = {0};
    std::cin >> pid.Kp >> pid.Ki >> pid.Kd;
    std::cin >> setPoint >> measuredValue >> time;
    for (int i = 1; i <= time; ++i) {
        double output = PIDCalculate(pid, setPoint, measuredValue);
        measuredValue += output;
        std::cout << i << " " << std::fixed << std::setprecision(6) <<  measuredValue << std::endl;
    }
    return 0;
}