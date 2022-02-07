#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define SR 8000 // Sample Rate

typedef struct{
	int chunkid;
	int chunksize;
	int format;
	int subchunk1id;
	int subchunk1size;
	uint16_t audioformat;
	uint16_t numchannels;
	int samplerate;
	int byterate;
	uint16_t blockalign;
	uint16_t bitspersample;
	int subchunk2id;
	int subchunk2size;
} wav;
// Convert seconds to sample
int sec_to_sample(int sec){
	return sec * SR;
}
double cubeRoot(double n){
   double i, precision = 0.000001;

   for(i = 1; (i*i*i) <= n; ++i);
   for(--i; (i*i*i) < n; i += precision);
   return i;
}
wav init_wav(int size){
	wav wav_s;
	wav_s.chunkid = 'FFIR'; // They need to be reversed i still do not know why
	wav_s.format = 'EVAW';
	wav_s.subchunk1id = ' tmf';
	wav_s.subchunk1size = 16;
	wav_s.audioformat = 1;
	wav_s.numchannels = 2;
	wav_s.samplerate = SR;
	wav_s.blockalign = wav_s.numchannels * wav_s.bitspersample / 8;
	wav_s.bitspersample = 16;
	wav_s.subchunk2id = 'atad';
	wav_s.subchunk2size = size * wav_s.numchannels * wav_s.bitspersample/8;
	wav_s.byterate = wav_s.samplerate *wav_s.numchannels* wav_s.numchannels/8;
	wav_s.chunksize = 36 + wav_s.subchunk2size;

	return wav_s;

}



int main(void){
	if(sizeof(int) != 4){
		printf("Cannot process wav file, because your machine int size is different than 4\n");
		return 1;
	}

	wav wav_s;
	size_t size = sec_to_sample(10);
	const float amp = 1; // Amplitude
	const float freq = 1; // Frequency
	const float teta = 0; // Move the sound wave
	
	wav_s = init_wav(size);
	float samples[size];
	// a*sin((2pi*f*x)/ samplerate)

	for(float x =0;x < (float)size;x++){samples[(int)x] = (amp * sin( (x * 2* M_PI * freq + teta )/SR )); } // Sine formula

	// (y - cuberoot of x**2)**2 + x**2    and let y be the sine formula
	
	// for(float x =0;x < (float)size;x++){
		// float sinres = (amp * sin( (x * 2* M_PI * freq + teta )/SR ));
		// float firstres = ( sinres - cubeRoot(x*x) );
		// samples[(int)x] = firstres*firstres + x*x ;
// 
	// } // Love Graph formula combined with sine formula (VERY SLOW NOT RECOMMENDED)

	FILE* fp;
	fp = fopen("gen.wav","wb");

	printf("AMPLITUDE : %f\n",amp);
	printf("FREQUENCY : %f\n",freq);
	printf("SAMPLERATE : %d\n",SR);

	fwrite(&wav_s.chunkid,13,sizeof(wav_s),fp);
	for(int i = 0;i < (int)size;i++){
		fwrite(&samples[i],1,sizeof(samples[i]),fp);
	}
	printf("Done\n");
	fclose(fp);

	return 0;
}
