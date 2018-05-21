// Marquee effect on 4x4x4 led cube

  #define charSize 4
  #define maxTextLength 20
  #define maxBufferLength 107 // chars * 4 + ((char - 1) * space) + 4 spaces in front + 4 spaces in the back)
  // size of the matrix, and thus the size of the characters
  // const int charSize = 4;
  
  // timing variables
  const int frameTime = 2000;
  //const int stepTime = 250;  
  //const int halfStep = stepTime / 2;
  //const int doubleStep = stepTime * 2;
 
  // initial pin mapping
  int pinLayer[4]={A3,A2,A1,A0}; //initializing and declaring led layers
  int pinColumn[16]={13,12,11,10,9,8,7,6,5,4,3,2,1,0,A5,A4}; //initializing and declaring led rows

  // mapping the display slices to pins
  int frontOuterDisplay[4] = {A4, A5, 0, 1};
  int backOuterDisplay[4] = {10, 11, 12, 13};
  int frontInnerDisplay[4] = {2, 3, 4, 5};
  int backInnerDisplay[4] = {6, 7, 8, 9};
  int layerDisplay[4] = {A3,A2,A1,A0};  // layers up to down

  // contents to write to the cube in each timing step
  // the buffer will be written to the middle two slices of the cube, front and back faces are turned off.
  bool displayBuffer[4][4] = {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    };
    
  // the combination of charmaps to write to the display are constructed in this buffer
  bool textBuffer[charSize][maxBufferLength];
  int actualTextLength = 0;
  int actualBufferLength = 0;
  bool *marqueeFinger;
  bool *bufferEndFinger;
  
  // character maps
  const bool charmap_none[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  };
  const bool charmap_all[4][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1}
  };
  const bool charmap_a[4][4] = {
    {0,1,1,0},
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1}
  };
  const bool charmap_b[4][4] = {
    {1,0,0,0},
    {1,0,0,0},
    {1,1,1,1},
    {1,1,1,1}
  };
  const bool charmap_c[4][4] = {
    {0,1,1,1},
    {1,0,0,0},
    {1,0,0,0},
    {0,1,1,1}
  };
  const bool charmap_d[4][4] = {
    {0,0,0,1},
    {0,0,0,1},
    {1,1,1,1},
    {1,1,1,1}
  };
  const bool charmap_e[4][4] = {
    {1,1,1,1},
    {1,0,0,0},
    {1,1,1,0},
    {1,1,1,1}
  };
  const bool charmap_f[4][4] = {
    {1,1,1,1},
    {1,0,0,0},
    {1,1,1,0},
    {1,0,0,0}
  };
  const bool charmap_g[4][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {0,0,0,1},
    {1,1,1,1}
  };
  const bool charmap_h[4][4] = {
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1}
  };
  const bool charmap_i[4][4] = {
    {0,1,1,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,1,1,0}
  };
  const bool charmap_j[4][4] = {
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {1,1,1,0}
  };
  const bool charmap_k[4][4] = {
    {1,0,0,1},
    {1,0,1,0},
    {1,1,1,0},
    {1,0,0,1}
  };
  const bool charmap_l[4][4] = {
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,1}
  };
  const bool charmap_m[4][4] = {
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1}
  };
  const bool charmap_n[4][4] = {
    {1,0,0,1},
    {1,1,0,1},
    {1,0,1,1},
    {1,0,0,1}
  };
  const bool charmap_o[4][4] = {
    {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1}
  };
  const bool charmap_p[4][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {1,0,0,0},
    {1,0,0,0}
  };
  const bool charmap_q[4][4] = {
    {1,1,1,0},
    {1,0,1,0},
    {1,1,1,0},
    {0,0,0,1}
  };
  const bool charmap_r[4][4] = {
    {1,1,1,0},
    {1,0,0,1},
    {1,1,1,0},
    {1,0,0,1}
  };
  const bool charmap_s[4][4] = {
    {1,1,1,0},
    {1,1,1,0},
    {0,0,0,1},
    {1,1,1,0}
  };
  const bool charmap_t[4][4] = {
    {1,1,1,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}
  };
  const bool charmap_u[4][4] = {
    {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1}
  };
  const bool charmap_v[4][4] = {
    {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {0,1,1,0}
  };
  const bool charmap_w[4][4] = {
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1},
    {0,1,1,0}
  };
  const bool charmap_x[4][4] = {
    {1,0,0,1},
    {0,1,1,0},
    {0,1,1,0},
    {1,0,0,1}
  };
  const bool charmap_y[4][4] = {
    {1,0,0,1},
    {0,1,1,1},
    {0,0,0,1},
    {1,1,1,1}
  };
  const bool charmap_z[4][4] = {
    {1,1,1,1},
    {0,0,1,0},
    {0,1,0,0},
    {1,1,1,1}
  };

void setup()
{
  setupPhysicalDisplay();

  clearTextBuffer();
  
  // string to write
  String marqueeText = String("abcd");
  buildMarqueeText(marqueeText);
}

void setupPhysicalDisplay() {
  for(int i = 0; i<16; i++) {
    pinMode(pinColumn[i], OUTPUT);  //setting rows to ouput
  }
  
  for(int i = 0; i<4; i++) {
    pinMode(pinLayer[i], OUTPUT);  //setting layers to output
  }
  
  turnEverythingOff();
}

void loop()
{
  loadFrameFromTextBuffer(marqueeFinger);
  render();
  marqueeFinger += charSize;

  //reset the finger when at the end of the text
  if(marqueeFinger==bufferEndFinger)
    marqueeFinger = textBuffer[0];
}

void render() {
  for(int t = frameTime; t>0; t--) {  // for the duration of a frame
    renderFrame();
  }
}

void renderFrame() {
  for(int row = 0; row < charSize; row++) {  // multiplex through the frame in the buffer
    for(int col = 0; col < charSize; col++) {
      turnEverythingOff();
      if(displayBuffer[row][col]) {
        digitalWrite(frontInnerDisplay[col], LOW);
        digitalWrite(backInnerDisplay[col], LOW);
        digitalWrite(layerDisplay[row], HIGH);
      }
    }
  }
}

void fillBufferWithFrame(const int frame[charSize][charSize]){
  for(int row = 0; row < charSize; row++) {
    for(int col = 0; col < charSize; col++) {
      displayBuffer[row][col] = frame[row][col];
    }
  }
}

void loadFrameFromTextBuffer(bool* finger) {
  for(int row = 0; row < charSize; row++) {
    for(int col = 0; col < charSize; col++) {
      displayBuffer[row][col] = (bool) finger + (row * charSize) + col;
      //displayBuffer[row][col] = textBuffer[row][col + finger];
    }
  }
}

bool* clearTextBuffer() {
  for(int row = 0; row < charSize; row++) {
    for(int col = 0; col < maxBufferLength; col++) {
      textBuffer[row][col] = 0;
    }
  }
  return textBuffer[0];
}

const bool* getMapForChar(char c) {
  switch(c) {
    case 'a':
      return charmap_a[0];
      break;
    case 'b':
      return charmap_b[0];
      break;
    case 'c':
      return charmap_c[0];
      break;
    case 'd':
      return charmap_d[0];
      break;
    case 'e':
      return charmap_e[0];
      break;
    case 'f':
      return charmap_f[0];
      break;
    case 'g':
      return charmap_g[0];
      break;
    case 'h':
      return charmap_h[0];
      break;
    case 'i':
      return charmap_i[0];
      break;
    case 'j':
      return charmap_j[0];
      break;
    case 'k':
      return charmap_k[0];
      break;
    case 'l':
      return charmap_l[0];
      break;
    case 'm':
      return charmap_m[0];
      break;
    case 'n':
      return charmap_n[0];
      break;
    case 'o':
      return charmap_o[0];
      break;
    case 'p':
      return charmap_p[0];
      break;
    case 'q':
      return charmap_q[0];
      break;
    case 'r':
      return charmap_r[0];
      break;
    case 's':
      return charmap_s[0];
      break;
    case 't':
      return charmap_t[0];
      break;
    case 'u':
      return charmap_u[0];
      break;
    case 'v':
      return charmap_v[0];
      break;
    case 'w':
      return charmap_w[0];
      break;
    case 'x':
      return charmap_x[0];
      break;
    case 'y':
      return charmap_y[0];
      break;
    case 'z':
      return charmap_z[0];
      break;
    default:
      return charmap_none[0];
  }
}

void copyCharmap(const bool* frame, bool* pos) {
  for(int row = 0; row < charSize; row++) {
    for(int col = 0; col < charSize; col++) {
      bool val = (bool) frame + (row * charSize) + col;
      *pos = val;
      pos += 1;
    }
  }
}

void buildMarqueeText(String text) {
  actualTextLength = sizeof(text)-1;
  actualBufferLength = calculateBufferLength(actualTextLength);
  bufferEndFinger = textBuffer[0] + (actualBufferLength - (4*charSize));
  
  if(actualTextLength > maxTextLength) {
    text = "input too long";
    actualTextLength = sizeof(text)-1;
    actualBufferLength = calculateBufferLength(actualTextLength);
    bufferEndFinger = textBuffer[0] + (actualBufferLength - (4*charSize));
  }
  
  bool* finger = textBuffer[0];
  
  // start with four spaces have the text move in: advance pointer
  finger += (4 * charSize);
  
  for(int i = 0; i < actualTextLength; i++) { // for each char in the text to display
    char c = text[i];
    const bool* charmap = getMapForChar(c);
    
    // write the char to the textBuffer
    copyCharmap(charmap, finger);
    finger += (charSize * charSize); // advance pointer
  
    // write a space after the character to the textBuffer
    finger += (charSize);
  }
  // finish with 3 more spaces to have the text move out.
  finger += (3 * charSize);
}

int calculateBufferLength(int len) {
  return ((len+2)*charSize)+(len-1); // 4 columns per char, 4 on the head, 4 on the tail, n-1 spaces between chars.
}

//turn all off
void turnEverythingOff() {
  for(int i = 0; i<16; i++) {
    digitalWrite(pinColumn[i], 1);
  }
  for(int i = 0; i<4; i++) {
    digitalWrite(pinLayer[i], 0);
  }
}
 
//turn all on
void turnEverythingOn() {
  for(int i = 0; i<16; i++) {
    digitalWrite(pinColumn[i], 0);
  }
  //turning on layers
  for(int i = 0; i<4; i++) {
    digitalWrite(pinLayer[i], 1);
  }
}

