// Marquee effect on 4x4x4 led cube

  // string to write
  String marqueeText = String("abcd");

  // timing variables
  const int frameTime = 2000;
  const int stepTime = 250;  
  const int halfStep = stepTime / 2;
  const int doubleStep = stepTime * 2;

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
  int displayBuffer[4][4] = {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    };
    
  // character maps
  
  const int charmap_none[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  };
  const int charmap_all[4][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1}
  };
  const int charmap_a[4][4] = {
    {0,1,1,0},
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1}
  };
  const int charmap_b[4][4] = {
    {1,0,0,0},
    {1,0,0,0},
    {1,1,1,1},
    {1,1,1,1}
  };
  const int charmap_c[4][4] = {
    {0,1,1,1},
    {1,0,0,0},
    {1,0,0,0},
    {0,1,1,1}
  };
  const int charmap_d[4][4] = {
    {0,0,0,1},
    {0,0,0,1},
    {1,1,1,1},
    {1,1,1,1}
  };
  const int charmap_e[4][4] = {
    {1,1,1,1},
    {1,0,0,0},
    {1,1,1,0},
    {1,1,1,1}
  };
  const int charmap_f[4][4] = {
    {1,1,1,1},
    {1,0,0,0},
    {1,1,1,0},
    {1,0,0,0}
  };
  const int charmap_g[4][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {0,0,0,1},
    {1,1,1,1}
  };
  const int charmap_h[4][4] = {
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1}
  };
  const int charmap_i[4][4] = {
    {0,1,1,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,1,1,0}
  };
  const int charmap_j[4][4] = {
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {1,1,1,0}
  };
  const int charmap_k[4][4] = {
    {1,0,0,1},
    {1,0,1,0},
    {1,1,1,0},
    {1,0,0,1}
  };
  const int charmap_l[4][4] = {
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,1}
  };
  const int charmap_m[4][4] = {
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1}
  };
  const int charmap_n[4][4] = {
    {1,0,0,1},
    {1,1,0,1},
    {1,0,1,1},
    {1,0,0,1}
  };
  const int charmap_o[4][4] = {
    {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1}
  };
  const int charmap_p[4][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {1,0,0,0},
    {1,0,0,0}
  };
  const int charmap_q[4][4] = {
    {1,1,1,0},
    {1,0,1,0},
    {1,1,1,0},
    {0,0,0,1}
  };
  const int charmap_r[4][4] = {
    {1,1,1,0},
    {1,0,0,1},
    {1,1,1,0},
    {1,0,0,1}
  };
  const int charmap_s[4][4] = {
    {1,1,1,0},
    {1,1,1,0},
    {0,0,0,1},
    {1,1,1,0}
  };
  const int charmap_t[4][4] = {
    {1,1,1,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}
  };
  const int charmap_u[4][4] = {
    {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1}
  };
  const int charmap_v[4][4] = {
    {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {0,1,1,0}
  };
  const int charmap_w[4][4] = {
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1},
    {0,1,1,0}
  };
  const int charmap_x[4][4] = {
    {1,0,0,1},
    {0,1,1,0},
    {0,1,1,0},
    {1,0,0,1}
  };
  const int charmap_y[4][4] = {
    {1,0,0,1},
    {0,1,1,1},
    {0,0,0,1},
    {1,1,1,1}
  };
  const int charmap_z[4][4] = {
    {1,1,1,1},
    {0,0,1,0},
    {0,1,0,0},
    {1,1,1,1}
  };
  
 
void setup()
{
  
  for(int i = 0; i<16; i++)   
  {
    pinMode(pinColumn[i], OUTPUT);  //setting rows to ouput
  }
  
  for(int i = 0; i<4; i++)
  {
    pinMode(pinLayer[i], OUTPUT);  //setting layers to output
  }
  
  turnEverythingOff();
}

void loop()
{
  fillBufferWithFrame(charmap_h);
  render();

  fillBufferWithFrame(charmap_a);
  render();
 
  fillBufferWithFrame(charmap_y);
  render();
 
  fillBufferWithFrame(charmap_e);
  render(); 
 
  fillBufferWithFrame(charmap_none);
  render();
  
  fillBufferWithFrame(charmap_e);
  render();
  
  fillBufferWithFrame(charmap_n);
  render();
  
  fillBufferWithFrame(charmap_none);
  render();
  
  fillBufferWithFrame(charmap_s);
  render();
  
  fillBufferWithFrame(charmap_i);
  render();
  
  fillBufferWithFrame(charmap_l);
  render();
  
  fillBufferWithFrame(charmap_j);
  render();
  
  fillBufferWithFrame(charmap_e);
  render();
  
  fillBufferWithFrame(charmap_none);
  render();
}

void render() {
  for(int t = frameTime; t>0; t--) {  // for the duration of a frame
    for(int row = 0; row<4; row++) {  // multiplex through the frame in the buffer
      for(int col = 0; col<4; col++) {
        turnEverythingOff();
        if(displayBuffer[row][col]==1) {
          digitalWrite(frontInnerDisplay[col], LOW);
          digitalWrite(backInnerDisplay[col], LOW);
          digitalWrite(layerDisplay[row], HIGH);
        }
      }
    }
  }
}

void fillBufferWithFrame(const int frame[4][4]){
  for(int row = 0; row<4; row++) {
    for(int col = 0; col<4; col++) {
      displayBuffer[row][col] = frame[row][col];
    }
  }
}

//turn all off
void turnEverythingOff()
 {
   for(int i = 0; i<16; i++)
   {
     digitalWrite(pinColumn[i], 1);
   }
   for(int i = 0; i<4; i++)
   {
     digitalWrite(pinLayer[i], 0);
   }
 }
 
//turn all on
void turnEverythingOn()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(pinColumn[i], 0);
  }
  //turning on layers
  for(int i = 0; i<4; i++)
  {
    digitalWrite(pinLayer[i], 1);
  }
}

