#ifndef WORKCONDITION_H
#define WORKCONDITION_H

class WorkCondition
{
public:
    WorkCondition();

    int getID() const;

    bool getTorsoSupport() const;
    void setTorsoSupport(bool support);

    bool getArmSupport() const;
    void setArmSupport(bool support);

    int getPrecision() const;
    void setPrecision(int precision);

    int getVelocity() const;
    void setVelocity(int velocity);

    int getAcceleration() const;
    void setAcceleration(int acceleration);

    int getVibration() const;
    void setVibration(int vibration);

    int getGrabCondition() const;
    void setGrabCondition(int grabCondition);

    int getAccessibility() const;
    void setAccessibility(int accessibility);

    int getGround() const;
    void setGround(int ground);

    int getLighting() const;
    void setLighting(int lighting);

    int getClimate() const;
    void setClimate(int climate);

    int getWind() const;
    void setWind(int wind);

    int getClothing() const;
    void setClothing(int clothing);

    int getRoomToMove() const;
    void setRoomToMove(int roomToMove);

private:
    int id;
    bool torsoSupport;
    bool armSupport;
    int precision;
    int velocity;
    int acceleration;
    int vibration;
    int grabCondition;
    int accessibility;
    int ground;
    int lighting;
    int climate;
    int wind;
    int clothing;
    int roomToMove;
};

#endif // WORKCONDITION_H
