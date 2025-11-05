
#include "CComplex.h"
#include "avdweb_AnalogReadFast.h"

// Buffer size, make it a power of two if you want to improve fftw
const int N = 200;

float vif[6] = {}; //very important frequency
float vim[6] = {}; //very important magnitude

// input signal
Complex in[N];

float a_offset;

float powr[N / 2];

// frequencies of input signal after ft
// Size increased by one because the optimized sdft code writes data to freqs[N]
Complex freqs[N + 1];

// forward coeffs -2 PI e^iw -- normalized (divided by N)
Complex coeffs[N];

// global index for input and output signals
int idx;


// these are just there to optimize (get rid of index lookups in sdft)
Complex oldest_data, newest_data;

//initilaize e-to-the-i-thetas for theta = 0..2PI in increments of 1/N
void init_coeffs() {
  for (int i = 0; i < N; ++i) {
    float a = -2.0 * PI * i / float(N);
    coeffs[i] = Complex(cos(a) /* / N */, sin(a) /* / N */);
  }
}


// initialize all data buffers
void buff_init() {
  // clear data
  for (int i = 0; i < N; ++i)
    in[i] = 0;
  init_coeffs();
  oldest_data = newest_data = 0.0;
  idx = 0;
}

// simulating adding data to circular buffer
void add_data() {
  oldest_data = in[idx];
  newest_data = in[idx] = Complex((analogReadFast(A3) - a_offset )/ float(N));
}


// sliding dft
void sdft() {
  Complex delta = newest_data - oldest_data;
  int ci = 0;
  for (int i = 0; i < N; ++i) {
    freqs[i] += delta * coeffs[ci];
    if ((ci += idx) >= N)
      ci -= N;
  }
}


void insertFreq(int ptr) {
  float magnitude = powr[ptr];
  float frequency = ptr;
  for (int j = 0; j < 6; j++) {//0 to 5
    if (magnitude <= vim[j]) {
      for (int t = 0; t < j; t++) {//0 to 4
        vif[t] = vif[t + 1];//four can equal five
        vim[t] = vim[t + 1];
      }
      vif[j - 1] = frequency;
      vim[j - 1] = magnitude;
      return;
    }
  }
  vif[5] = frequency;
  vim[5] = magnitude;
  return;
}


float mag(Complex& c) {
  return sqrt(c.real() * c.real() + c.imag() * c.imag());
}

void powr_spectrum() {
  for (int i = 0; i < N / 2; ++i) {
    powr[i] = mag(freqs[i]);
    if (powr[i] > vim[0]) {
      insertFreq(i);
    }
  }
}


void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  delay(1000);
  a_offset = analogRead(A6);
  // put your setup code here, to run once:
  buff_init();
}

const int NSAMPS = N * 10;

void loop() {

  for (int i = 0; i < NSAMPS; ++i) {

    add_data();
    //add_data();


    sdft();
    // Mess about with freqs[] here
    //isdft();

    powr_spectrum();
    for (int j = 1; j < N / 2; j = j + 2) {
      //Serial.println(powr[j]);
      //vif[j] = 0;
    }

    for (int j = 0; j < 5; j = j + 1) {
      Serial.println(vif[j]);
      vif[j] = 0;
      vim[j] = 0;
    }

    if (++idx == N) {
      idx = 0;  // bump global index
    }
  }

}
