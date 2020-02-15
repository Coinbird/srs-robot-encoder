#define TICKS_PER_REVOLUTION 32.0
#define WHEEL_DIAMETER_MM 66.0
#define WHEEL_CIRC WHEEL_DIAMETER_MM * M_PI

const float wheelCircMm = M_PI * WHEEL_DIAMETER_MM;
const float distancePerTickMm = wheelCircMm / TICKS_PER_REVOLUTION;

float getDistanceMm(long int encoder_ticks) {
  return distancePerTickMm * encoder_ticks;
}
