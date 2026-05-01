// --- Pin Definitions / Pin Tanımlamaları ---
const int trigPin = 9;    // Trig pin to trigger the sound wave / Ses dalgasını tetiklemek için Trig pini
const int echoPin = 10;   // Echo pin to receive the reflected wave / Yansıyan dalgayı almak için Echo pini
const int buzzerPin = 11; // Pin connected to the buzzer / Buzzer'ın bağlı olduğu pin

long duration; // Variable to store travel time of the wave / Dalganın gidiş-dönüş süresi için değişken
int distance;  // Variable to store calculated distance / Hesaplanan mesafe için değişken
int toneFreq;  // Variable for the frequency of the sound / Sesin frekansı için değişken

void setup() {
  // Set pin modes / Pin modlarını ayarlıyoruz
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Start serial communication at 9600 baud / Seri haberleşmeyi 9600 hızında başlatıyoruz
  Serial.begin(9600); 
}

void loop() {
  // Send a 10-microsecond pulse to trigger the sensor 
  // Sensörü tetiklemek için 10 mikrosaniyelik bir sinyal gönderiyoruz
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time the wave took to return (in microseconds)
  // Dalganın geri dönme süresini ölçüyoruz (mikrosaniye cinsinden)
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters / Mesafeyi santimetreye çeviriyoruz
  // (Speed of sound = 0.034 cm/us)
  distance = duration * 0.034 / 2;

  // Process movements only between 5cm and 30cm
  // Sadece 5cm ile 30cm arasındaki hareketleri işleyelim
  if (distance > 5 && distance < 30) {
    
    // Map distance (5-30) to frequency range (1000-200 Hz)
    // Mesafeyi (5-30), frekans aralığına (1000-200 Hz) dönüştürüyoruz
    // Nearer = Higher pitch, Farther = Lower pitch / Yakın = İnce ses, Uzak = Kalın ses
    toneFreq = map(distance, 5, 30, 1000, 200); 
    
    tone(buzzerPin, toneFreq); // Generate the sound / Sesi üret
  } else {
    // Stop sound if distance is out of range / Mesafe aralık dışındaysa sesi durdur
    noTone(buzzerPin); 
  }

  // Print the distance to the Serial Monitor / Mesafeyi Seri Port Ekranına yazdır
  Serial.print("Distance / Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Small delay for a smoother sound transition / Daha pürüzsüz ses geçişi için kısa bekleme
  delay(50); 
}
