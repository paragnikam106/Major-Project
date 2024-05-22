// Define the analog pins for various water quality sensors.
const int pHAnalogPin = A0;
const int hardnessAnalogPin = A1;
const int sulfateAnalogPin = A2;
const int conductivityAnalogPin = A3;
const int organicCarbonAnalogPin = A4;
const int turbidityAnalogPin = A5;
const int chloraminesAnalogPin = A6;

void setup() {
  // Initialize the serial communication.
  Serial.begin(9600);
}

void loop() {
  // Read the analog values from the sensors.
  float pHValue = readSensor(pHAnalogPin, 0, 1023, 0.0, 14.0);
  float hardnessValue = readSensor(hardnessAnalogPin, 0, 1023, 0.0, 200.0);
  float sulfateValue = readSensor(sulfateAnalogPin, 0, 1023, 0.0, 500.0);
  float conductivityValue = readSensor(conductivityAnalogPin, 0, 1023, 0.0, 1000.0);
  float organicCarbonValue = readSensor(organicCarbonAnalogPin, 0, 1023, 0.0, 10.0);
  float turbidityValue = readSensor(turbidityAnalogPin, 0, 1023, 0.0, 10.0);
  float chloraminesValue = readSensor(chloraminesAnalogPin, 0, 1023, 0.0, 4.0);

  // Check if water is potable based on specified ranges.
  bool isPotable = checkWaterQuality(pHValue, hardnessValue, sulfateValue, conductivityValue, organicCarbonValue, turbidityValue, chloraminesValue);

  // Display the result.
  if (isPotable) {
    Serial.println("Water is potable.");
  } else {
    Serial.println("Water is not potable.");
  }

  // Add a delay to control the rate of sensor measurements.
  delay(1000); // Adjust as needed.
}

// Function to read and map sensor values.
float readSensor(int pin, int sensorMin, int sensorMax, float rangeMin, float rangeMax) {
  int sensorValue = analogRead(pin);
  return map(sensorValue, sensorMin, sensorMax, rangeMin, rangeMax);
}

// Function to check water quality based on specified ranges.
bool checkWaterQuality(float pH, float hardness, float sulfate, float conductivity, float organicCarbon, float turbidity, float chloramines) {
  // Define the acceptable ranges for each parameter.
  const float minpH = 6.5;
  const float maxpH = 8.5;
  const float minHardness = 50.0;
  const float maxHardness = 100.0;
  const float maxSulfate = 250.0;
  const float maxConductivity = 800.0;
  const float maxOrganicCarbon = 2.0;
  const float maxTurbidity = 5.0;
  const float maxChloramines = 4.0;

  // Check if all values fall within the acceptable ranges.
  return (pH >= minpH && pH <= maxpH &&
          hardness >= minHardness && hardness <= maxHardness &&
          sulfate <= maxSulfate &&
          conductivity <= maxConductivity &&
          organicCarbon <= maxOrganicCarbon &&
          turbidity <= maxTurbidity &&
          chloramines <= maxChloramines);
}
