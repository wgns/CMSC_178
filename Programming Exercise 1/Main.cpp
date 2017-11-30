#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <string>
#include "AudioFile.h"
#include "AudioFile.cpp"

void generatePureTone(int freq);
void generateJustIntonation(int freq);
void generate12TET(int freq);

int main() {
	int choice = 0, freq = 0;
	char temp = 'p';
	
	printf("1. Generate a Pure Tone\n2. Generate Tuning Sequence\nChoose a feature: ");
	scanf("%d", &choice);
	
	while (choice < 1 || choice > 2) {
		fflush(stdin);
		printf("Please enter a valid input: ");
		scanf("%d", &choice);
	}
	
	switch(choice) {
		case 1:
			printf("\nFrequency of the pure tone in Hertz: ");
			scanf("%d", &freq);
			
			while (freq < 1) {
				fflush(stdin);
				printf("Please enter a valid input: ");
				scanf("%d", &freq);
			}
			
			generatePureTone(freq);			
			fflush(stdin);
			printf("\nPure tone generated and saved to %csine-%i.wav%c\nPress Enter key to exit...", 34, freq, 34);
			scanf("%c", &temp);
			break;
		case 2:
			choice = 0;
			printf("\n1. Just Intonation\n2. 12-Tone Equal Temperament\nChoose a Tuning System: ");
			scanf("%d", &choice);
			
			while (choice < 1 || choice > 2) {
				fflush(stdin);
				printf("Please enter a valid input: ");
				scanf("%d", &choice);
			}
			
			switch(choice) {
				case 1:
					printf("\nFrequency of %cDo%c in Hertz: ", 34, 34);
					scanf("%d", &freq);
					
					while (freq < 20) {
						fflush(stdin);
						printf("Please enter a value greater than or equal to 20Hz: ");
						scanf("%d", freq);
					}
					
					generateJustIntonation(freq);					
					fflush(stdin);
					printf("\nTuning sequence saved to %cjust-intonation-%i.wav%c\nPress Enter key to exit...", 34, freq, 34);
					scanf("%c", &temp);
					break;
				case 2:
					printf("\nFrequency of Unison in Hertz: ");
					scanf("%d", &freq);
					
					while (freq < 20) {
						fflush(stdin);
						printf("Please enter a value greater than or equal to 20Hz: ");
						scanf("%d", freq);
					}
					
					generate12TET(freq);					
					fflush(stdin);
					printf("\nTuning sequence saved to %c12-TET-%i.wav%c\nPress Enter key to exit...", 34, freq, 34);
					scanf("%c", &temp);
			}
	}
	
	return 0;
}

void generate12TET(int freq) {
	std::string str = std::to_string(freq);
	float temp = (float) freq;

	AudioFile<float> audio;
	audio.setAudioBufferSize(2, 44100 * 25);
	
	for (int start = 0, end = 44100, sec = 0; sec < 25;) {
		for (; start < end; start++) {
	        float sample = sinf(2.0 * M_PI * ((float) start / 44100.0) * temp);
	        
	        for (int j = 0; j < audio.getNumChannels(); j++) {
	            audio.samples[j][start] = sample * 0.5;
	        }
	    }
	    
	    sec++;
	    start = end;
	    end += 44100;
	    
	    if (sec % 2 == 0) {
	    	temp = freq * pow(1.059463, sec / 2);
		} else {
			temp = 0;
		}
	}
	
	audio.setSampleRate(44100);
	audio.setBitDepth(16);
	audio.save("12-TET-" + str + ".wav");
}

void generateJustIntonation(int freq) {
	std::string str = std::to_string(freq);
	float temp = (float) freq;

	AudioFile<float> audio;
	audio.setAudioBufferSize(2, 44100 * 15);
	
	for (int start = 0, end = 44100, sec = 0; sec < 15;) {
		for (; start < end; start++) {
	        float sample = sinf(2.0 * M_PI * ((float) start / 44100.0) * temp);
	        
	        for (int j = 0; j < audio.getNumChannels(); j++) {
	            audio.samples[j][start] = sample * 0.5;
	        }
	    }
	    
	    sec++;
	    start = end;
	    end += 44100;
	    
	    switch(sec) {
	    	case 2:
	    		temp = round(freq * 9 / 8);
	    		break;
	    	case 4:
	    		temp = round(freq * 5 / 4);
	    		break;
	    	case 6:
	    		temp = round(freq * 4 / 3);
	    		break;
	    	case 8:
	    		temp = round(freq * 3 / 2);
	    		break;
	    	case 10:
	    		temp = round(freq *5 / 3);
	    		break;
	    	case 12:
	    		temp = round(freq * 15 / 8);
	    		break;
	    	case 14:
	    		temp = round(freq * 2);
	    		break;
	    	default:
	    		temp = 0;
		}
	}
	
	audio.setSampleRate(44100);
	audio.setBitDepth(16);
	audio.save("just-intonation-" + str + ".wav");
}

void generatePureTone(int freq){
	std::string str = std::to_string(freq);
	float temp = (float) freq;

	AudioFile<float> audio;
	audio.setAudioBufferSize(2, 44100 * 10);
	
	for (int i = 0; i < audio.getNumSamplesPerChannel(); i++) {
        float sample = sinf(2.0 * M_PI * ((float) i / 44100.0) * temp);
        
        for (int j = 0; j < audio.getNumChannels(); j++) {
            audio.samples[j][i] = sample * 0.5;
        }
    }
	
	audio.setSampleRate(44100);
	audio.setBitDepth(16);
	audio.save("sine-" + str + ".wav");
}
