/*
shiftOut với 8 LED bằng 1 IC HC595
*/
//chân ST_CP của 74HC595
int latchPin = 8;
//chân SH_CP của 74HC595
int clockPin = 12;
//Chân DS của 74HC595
int dataPin = 11;
 
//Trạng thái của LED, hay chính là byte mà ta sẽ gửi qua shiftOut
const int HC595_COUNT = 2;//Nếu bạn dùng nhiều hơn thì thay bằng một số lớn hơn 2.
byte ledStatus[HC595_COUNT]= {0}; 
void setup() {
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void fillValueToArray(byte value) {
  for (int i = 0;i < HC595_COUNT; i++) {
    ledStatus[i] = value;
  }
}
 
void shiftOutHC595(int dataPin, int clockPin, byte ledStatus[]) {
  digitalWrite(latchPin, LOW);
  
  for (int i = 0; i < HC595_COUNT; i++) {
    shiftOut(dataPin,clockPin,LSBFIRST,ledStatus[i]); 
  }
  
  digitalWrite(latchPin, HIGH);
}

 
void loop() { 
  /*
    Trong tin học, ngoài các phép +, -, *, / hay % mà bạn đã biết trên hệ cơ số 10.
    Thì còn có nhiều phép tính khác nữa. Và một trong số đó là Bit Math (toán bit) trên hệ cơ số 2.
    Để hiểu những gì tôi viết tiếp theo sau, bạn cần có kiến thức về Bit Math.
    Để tìm hiểu về Bit Math, bạn vào mục Tài liệu tham khảo ở bảng chọn nằm phía trên cùng trang web và chạy xuống khi bạn kéo chuột trên trang Arduino.VN
  */
  //Sáng tuần tự
 
  //vì ledStatus là một mảng vì vậy để mặc định tất cả đèn tắt thì chúng ta phải for đến từng giá trị của mảng rồi đặt giá trị là 0.
  fillValueToArray(0);
  //Bật tuần tự
  for (int i =HC595_COUNT; i>=0; i--) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] >> 1)|128;
      shiftOutHC595(dataPin,clockPin,ledStatus);
      delay(100); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
      
    }    
  }
    for (int i =HC595_COUNT; i>=0; i--) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] >> 1);
      shiftOutHC595(dataPin,clockPin,ledStatus);
      delay(100); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
    }    
  }
  
   for (int i=0; i< HC595_COUNT; i++) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1)|1;
      shiftOutHC595(dataPin,clockPin,ledStatus);
      delay(100); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
    }    
  }
    for (int i = 0; i < HC595_COUNT; i++) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1);
      shiftOutHC595(dataPin,clockPin,ledStatus);
      delay(100); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
    }    
  }
}
