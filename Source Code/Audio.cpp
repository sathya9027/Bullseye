#include "Common.h"
Audio::Audio() {

}
Audio::~Audio() {
	this->DeleteAudio();
}
int Audio::endWithError(const char* msg, int error = 0) {
	cout << msg << "\n";
	system("PAUSE");
	return error;
}
int Audio::InitAudio(const char* filePath) {

	fp = fopen(filePath, "rb");

	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F') {
		return endWithError("NO RIFF");
	}

	fread(&size, sizeof(DWORD), 1, fp);
	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E') {
		return endWithError("NO WAVE");
	}

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ') {
		return endWithError("NO FMT");
	}

	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a') {
		return endWithError("Missing Data");
	}

	fread(&dataSize, sizeof(DWORD), 1, fp);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(BYTE), dataSize, fp);

	ALCdevice* device;
	ALCcontext* context;
	device = alcOpenDevice(NULL);
	if (!device) {
		return endWithError("no sound device");
	}
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if (!context) {
		return endWithError("no sound context");
	}

	ALuint buffer;
	ALuint frequency = sampleRate;
	ALuint format = 0;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	if (bitsPerSample == 8) {
		if (channels == 1) {
			format = AL_FORMAT_MONO8;
		}
		else if (channels == 2) {
			format = AL_FORMAT_STEREO8;
		}
	}
	else if (bitsPerSample == 16) {
		if (channels == 1) {
			format = AL_FORMAT_MONO16;
		}
		else if (channels == 2) {
			format = AL_FORMAT_STEREO16;
		}
	}

	alBufferData(buffer, format, buf, dataSize, frequency);

	ALfloat SourcePos[] = { 0.0f, 0.0f, 0.0f };
	ALfloat SourceVel[] = { 0.0f, 0.0f, 0.0f };
	ALfloat ListenerPos[] = { 0.0f, 0.0f, 0.0f };
	ALfloat ListenerVel[] = { 0.0f, 0.0f, 0.0f };
	ALfloat ListenerOri[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

	//Listener
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

	//Source
	alSourcei(source, AL_BUFFER, buffer);
	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSourcefv(source, AL_POSITION, SourcePos);
	alSourcefv(source, AL_VELOCITY, SourceVel);
	alSourcei(source, AL_LOOPING, AL_FALSE); 

}
void Audio::PlayAudio() {
	alSourcePlay(source);
}
void Audio::PauseAudio() {
	alSourcePause(source);
}
void Audio::StopAudio() {
	alSourceStop(source);
}
void Audio::DeleteAudio() {
	//Deleting all buffer and source

	fclose(fp);
	delete[] buf;
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
