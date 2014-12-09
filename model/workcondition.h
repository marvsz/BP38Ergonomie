#ifndef WORKCONDITION_H
#define WORKCONDITION_H


class WorkCondition
{
public:
    WorkCondition(bool* torsoSupport, bool* armSupport, int* neededPrecision, int* neededVelocity, int* neededAcceleration, int* givenVibration, int* gripCondition, int* accessibility, int* terrain, int* lighting, int* clima, int* wind, int* clothing, int* mobility);
    ~WorkCondition();

    void setTorsoSupport(bool* ts);
    void setArmSupport(bool* as);
    void setNeededPrecision(int* np);
    void setNeededVelocity(int* nv);
    void setNeededAccelaration(int* na);
    void setGivenVibration(int* gv);
    void setGripCondition(int* gc);
    void setAccessibility(int* ac);
    void setTerrain(int* te);
    void setLighting(int* li);
    void setClima(int* cl);
    void setWind(int* wi);
    void setClothing(int* clo);
    void setMobility(int* mo);

    bool* isTorsoSupported();
    bool* isArmSupported();
    int* getNeededPrecision();
    int* getNeededVelocity();
    int* getNeededAcceleration();
    int* getGivenVibration();
    int* getGripCondition();
    int* getAccessibility();
    int* getTerrain();
    int* getLighting();
    int* getClima();
    int* getWind();
    int* getClothing();
    int* getMobility();

private:
    bool* torsoSupport;
    bool* armSupport;
    int* neededPrecision;
    int* neededVelocity;
    int* neededAcceleration;
    int* givenVibration;
    int* gripCondition;
    int* accessibility;
    int* terrain;
    int* lighting;
    int* clima;
    int* wind;
    int* clothing;
    int* mobility;
};

#endif // WORKCONDITION_H
