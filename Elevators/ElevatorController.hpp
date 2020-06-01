#pragma once

#include <vector>

#include "ElevatorControllerBase.hpp"

class ElevatorButton;
class ElevatorMotor;


/*
 * FloorInfo.
 *
 * A struct that stores floor information.
 * Mainly used for spawning floors and for managing them with the controller.
 *
 */
struct FloorInfo {

    //the stop position for the cabin
    float yPos;

    //buttons
    ElevatorButton* SummonUpButton;
    ElevatorButton* SummonDownButton;
    ElevatorButton* CabinButton;

    //initializer
    FloorInfo(float _yPos, ElevatorButton* _SummonUpButton, ElevatorButton* _SummonDownButton, ElevatorButton* _CabinButton) : yPos(_yPos), SummonUpButton(_SummonUpButton), SummonDownButton(_SummonDownButton), CabinButton(_CabinButton) {};
};


class ElevatorController : public ElevatorControllerBase
{
public:

    //constructor, destructor
    ElevatorController();
    ~ElevatorController();

protected:

    //attributes
    ElevatorMotor* motor;
    std::vector<FloorInfo> floors;
    unsigned int currentFloor;
    Direction currentRoute;
    bool loading = true;
    float loadingDuration = 3.f;
    float loadingTimer = 0.f;
    bool bHasReversed = false;

    //protected methods
    void updateCurrentFloor(float yPos);
    void selectNextFloor();
    unsigned int findNextFloor(bool changedDirection = false);
    void load();

public:

    //setup
    void connectFloor(const FloorInfo&);
    void setMotor(ElevatorMotor* _motor) { motor = _motor; };
    void start();

    //interface functions
    void summonButtonPushed(int summoningFloor, Direction direction) override;
    void floorButtonPushed(int destinationFloor) override;
    void reachedPosition(float position) override;

    //tick
    void tick(float DeltaTime);
};
