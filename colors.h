// #import "application.h"
// #import "frisbeem.h"
//
//
// // Input a value 0 to 255 to get a color value.
// // The colours are a transition r - g - b - back to r.
// uint32_t wheel(byte WheelPos) {
//   if(WheelPos < 85) {
//    return frisbeem._strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//   } else if(WheelPos < 170) {
//    WheelPos -= 85;
//    return frisbeem._strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//   } else {
//    WheelPos -= 170;
//    return frisbeem._strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//   }
// }
//
// void blue() {
//   uint16_t i, j;
//
//   for(i=0; i<_strip.numPixels(); i++) {
//       _strip.setPixelColor(i, wheel(255));
//   }
//   frisbeem._strip.show();
// }
//
// void rainbow(uint8_t wait) {
//   uint16_t i;
//   if (whl > 255){
//     whl = 0;
//   }
//   for(i=0; i<frisbeem._strip.numPixels(); i++) {
//     frisbeem._strip.setPixelColor(i, wheel((i+whl)));
//   }
//   whl++;
//   frisbeem._strip.show();
//   delay(wait);
//
// }
//
// // Set all pixels in the strip to a solid color, then wait (ms)
// void colorAll(uint32_t c, uint8_t wait) {
//   uint16_t i;
//
//   for(i=0; i<frisbeem._strip.numPixels(); i++) {
//     frisbeem._strip.setPixelColor(i, c);
//   }
//   frisbeem._strip.show();
//   delay(wait);
// }
//
// // Fill the dots one after the other with a color, wait (ms) after each one
// void colorWipe(uint32_t c, uint8_t wait) {
//   for(uint16_t i=0; i<frisbeem._strip.numPixels(); i++) {
//     frisbeem._strip.setPixelColor(i, c);
//     frisbeem._strip.show();
//     delay(wait);
//   }
// }
