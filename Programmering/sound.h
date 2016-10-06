#ifndef Sound_h
#define Sound_h

using namespace std;

class Sound
{
public:
    Sound();
    short SinWave(double time, double freq, double amp);
    double tpc();
    double cycles();
    double rad();
    void playSound(vector<int>);
    void recordSound(int);
    void delay(int ms);

    ~Sound();

private:
    double frequency;
    double theTime;
    double theAmplitude;


};
#endif /* Sound.h */