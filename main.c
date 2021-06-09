#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

wav init_wav(int size){
	wav wav_s;
	wav_s.chunkid = 'FFIR';
	wav_s.format = 'EVAW';
	wav_s.subchunk1id = ' tmf';
	wav_s.subchunk1size = 16;
	wav_s.audioformat = 1;
	wav_s.numchannels = 2;
	wav_s.samplerate = 8000;
	wav_s.blockalign = wav_s.numchannels * wav_s.bitspersample / 8;
	wav_s.bitspersample = 8;
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
	size_t size = 120000;
	int notes[size];

	wav_s = init_wav(size);
	int i = 0;
	while(notes[i]){
		notes[i++] = 73;
		notes[i++] = 0;
		notes[i++] = 0;
		notes[i++] = 0;
		notes[i++] = 61;
		notes[i++] = 0;
		notes[i++] = 0;
		notes[i++] = 0;
		notes[i++] = 49;
		notes[i++] = 0;
		notes[i++] = 0;
		notes[i++] = 0;
	}
	int samples[size];

	for(int i =0;i < (int)size;i++){samples[i] = notes[i] ;}

	FILE* fp;
	fp = fopen("gen.wav","wb");
	// printf("BEFORE CHAR : %c\n",wav_s.chunkid);
	// printf("BEFORE DEC : %d\n",wav_s.chunkid);
	// printf("BEFORE HEX : %02hhX\n",wav_s.chunkid);
	// printf("AFTER HEX : %02hhX\n",reverse(wav_s.chunkid));
	printf("AFTER CHAR : %c\n",wav_s.chunkid);
	// printf("AFTER DEC : %d\n",reverse(wav_s.chunkid));
	fwrite(&wav_s.chunkid,13,sizeof(wav_s),fp);
	for(int i = 0;i < (int)size;i++){
		fwrite(&samples[i],1,sizeof(samples[i]),fp);
	}
	printf("Done\n");
	fclose(fp);

	return 0;
}
