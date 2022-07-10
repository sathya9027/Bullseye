#pragma once
class Audio
{
private:
	FILE* fp;
	DWORD dataSize;
	unsigned char* buf = new unsigned char[dataSize];
	ALCdevice* device;
	ALCcontext* context;
	ALuint buffer;
	ALuint source;
	int endWithError(const char* msg, int error);
public:
	Audio();
	~Audio();
	int InitAudio(const char* filePath);
	void PlayAudio();
	void PauseAudio();
	void StopAudio();
	void DeleteAudio();
};

