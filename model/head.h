#ifndef HEAD_H
#define HEAD_H


class Head
{
public:
    Head(int* rotation, int* tilt, int* sidewiseTilt);
    ~Head();

    void setRotation(int* r);
    void setTilt(int* t);
    void setSidewiseTilt(int* s);

    int* getRotation();
    int* getTilt();
    int* getSidewiseTilt();

private:
    int* rotation;
    int* tilt;
    int* sidewiseTilt;
};

#endif // HEAD_H
