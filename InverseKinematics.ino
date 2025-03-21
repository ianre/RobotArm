void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void calculateInverseKinematics(double x, double y) {
  // Constants
  double len1 = 10;
  double len2 = 10;
  double len3 = 10;
  double endAngle = -68; // Angle of motor3;
  
  double targetX = x; // Default: 12.6
  double targetY = y; // Default: 5.64
  
  double m, n;
  m = targetX - (len3 * (cos(endAngle)));
  n = targetY - (len3 * (sin(endAngle)));

  // Link 3
  double theta112 = atan(n / m);
  double mnlen = sqrt(sq(m) + sq(n));
  double theta13 = acos((sq(len2) - sq(len1) - sq(mnlen)) / (-2 * mnlen * len1));

  // Link 1
  double phi1 = theta112 + theta13; // This is angle of motor1;
  double phi2 = acos((sq(mnlen) - sq(len2) - sq(len1)) / (-2 * len2 * len1));
  double theta2 = phi1 + phi2 - 180; // Add 90 degrees for angle of motor2;

  Serial.print("Angle1: ");
  Serial.println(phi1);
  Serial.print("Angle2: ");
  Serial.println(theta2);
}