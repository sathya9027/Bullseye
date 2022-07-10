#include "Common.h"
Timer::Timer() {
	this->maxSeconds = NULL;
	this->seconds = NULL;
	this->temp = this->seconds;
	this->currentTime = this->maxSeconds - this->seconds;
}
Timer::~Timer() {

}
int& Timer::SetCurrentTime() {
	return this->currentTime;
}
void Timer::SetTimer(int _maxSeconds) {
	this->maxSeconds = _maxSeconds + 1;
}
void Timer::RunTimer() {
	this->seconds = int(glfwGetTime());
	if (this->temp < this->seconds) {
		this->currentTime = this->maxSeconds - this->seconds;
		cout << "Time: " << this->currentTime << endl;
		this->temp = this->seconds;
	}
}
int Timer::GetTimer() {
	return this->currentTime;
}
int Timer::GetMaxTimeLimit() {
	return this->maxSeconds;
}
