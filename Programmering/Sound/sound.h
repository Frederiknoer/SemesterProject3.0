#ifndef Sound_h
#define Sound_h

using namespace std;

class Sound
{
public:
    Sound();
    void setSamplingRate(double SR);
    void makeSound(vector<int>);

    short sinWave(double time , double timePrTone,  double freqLast, double freqNext);
    vector <sf::Int16> getSound();

    void delay(double ms);

    ~Sound();

private:
    double samplingRate;
    vector<sf::Int16> inputSamples;



};
#endif /* Sound.h */