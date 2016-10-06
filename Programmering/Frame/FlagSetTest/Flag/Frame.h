//
// Created by Mikkel on 03-10-2016.
//

#ifndef FLAG_FRAME_H
#define FLAG_FRAME_H

#endif //FLAG_FRAME_H

class Frame
{
public:
    Frame();

    Frame(unsigned int Data);
    unsigned int getFrame();

    void setFlag();
    void setParitybit();



    ~Frame();

private:
    unsigned int frame;
};

