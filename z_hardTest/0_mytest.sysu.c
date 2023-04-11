const float RADIUS = 5.5, PI = 03.141592653589793, EPS = 1e-6;

// hexadecimal float constant
const float PI_HEX = 0x1.921fb6p+1, HEX2 = 0x.AP-3;

// float constant evaluation
const float FACT = -.33E+5, EVAL1 = PI * RADIUS * RADIUS, EVAL2 = 2 * PI_HEX * RADIUS, EVAL3 = PI * 2 * RADIUS;

// float constant implicit conversion
const float CONV1 = 233, CONV2 = 0xfff;
const int MAX = 1e9, TWO = 2.9, THREE = 3.2, FIVE = TWO + THREE;
int main() {
  const int k0 = -2147483648;
  const int k1 = 0x80000000;
  const int k2 = 0x80000000 + 1;
  const int k3 = 0x7fFffffF;
  const int k4 = 0x7fFffffF - 1;
}
