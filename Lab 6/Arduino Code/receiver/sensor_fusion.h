#include <Arduino.h>
#define CONFIG 26
#define GYRO_CONFIG 27
#define PWR_MGMT_1 107
#define INT_STATUS 58
#define ACCEL_XOUT_0 60
#define ACCEL_XOUT_1 59
#define ACCEL_YOUT_0 62
#define ACCEL_YOUT_1 61
#define ACCEL_ZOUT_0 64
#define ACCEL_ZOUT_1 63
#define GYRO_XOUT_0 68
#define GYRO_XOUT_1 67
#define GYRO_YOUT_0 70
#define GYRO_YOUT_1 69
#define GYRO_ZOUT_0 72
#define GYRO_ZOUT_1 71

/** Reads a register over I2C from the IMU.
 *
 * reg: register address to read from.
 * buf: array to store the register data in.
 * len: length of buf.
 */
void readReg(uint8_t reg, uint8_t *buf, size_t len);

/** Writes to a register over I2C from the IMU.
 *
 * reg: register address to write to.
 * buf: array containing the data to write.
 * len: length of buf.
 */
void writeReg(uint8_t reg, uint8_t *buf, size_t len);

struct apdata {
  float roll;
  float pitch;
  float m1sp;
  float m2sp;
  float m3sp;
  float m4sp;
};

struct vector {
  float x;
  float y;
  float z;
};

struct quaternion {
  float r;
  float i;
  float j;
  float k;
};

/**
 * Normalizes a vector.
 *
 * raw: pointer to the vector to be normalized.
 * unit: pointer to where unit vector dimensions should be stored.
 *
 * returns: length of original vector
 */
float vector_normalize(struct vector *raw, struct vector *unit);

/**
 * Adds two vectors together.
 *
 * v1: pointer to the first vector to be added.
 * v2: pointer to the second vector to be added.
 * result: pointer where the sum of v1 and v2 should be stored.
 */
void vector_add(struct vector *v1, struct vector *v2, struct vector *result);

/**
 * Multiples a vector by a constant.
 *
 * v: pointer to the vector to be multiplied.
 * c: scalar constant to multiply vector by.
 * result: pointer where the c * v should be stored.
 */
void vector_multiply(struct vector *v, float c, struct vector *result);

/**
 * Creates a quaternion representing a rotation.
 *
 * v: unit vector representing the axis of rotation.
 * angle: angle of rotation.
 * result: quaternion representing a rotation of degree angle around the unit vector of v.
 */
void quaternion_create(struct vector *v, float angle, struct quaternion *result);

/**
 * Rotates a vector based on a quaternion.
 *
 * v: vector to be rotated.
 * q: quaternion representing the rotation to be performed.
 * result: The rotated vector.
 */
void quaternion_rotate(struct vector *v, struct quaternion *q, struct vector *result);

/**
 * Multiplies two quaternions together.
 *
 * q1: The first quaternion to be multiplied.
 * q2: The second quaternion to be multiplied.
 * result: q1 * q2.
 */
void quaternion_multiply(struct quaternion *q1, struct quaternion *q2, struct quaternion *result);

float vector_roll(struct vector *v);

float vector_pitch(struct vector *v);

