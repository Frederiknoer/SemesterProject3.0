#ifndef Sound_h
#define Sound_h

using namespace std;

class Sound
{
public:
    Sound();
    void setSamplingRate(double SR);
    void makeSound(vector<int>);

    short sinWave(double amp, double time , double timePrTone, int freqLast, int freqNext);
    short sinWaveOld(double amp, double time, int freq);
    void setSamplePrTone(int tonePlayTime);
    vector <sf::Int16> getSound();

    void delay(double ms);

    ~Sound();

private:
    int samplesPrTone;
    double samplingRate;
    vector<sf::Int16> inputSamples;



};
#endif /* Sound.h */
