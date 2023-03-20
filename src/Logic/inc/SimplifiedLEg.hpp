

typedef struct SimplifiedLeg{
    float x;
    bool legUp;
    bool operator==(const SimplifiedLeg &leg)const;
    bool operator!=(const SimplifiedLeg &leg)const;
    bool operator==(const FootCoordinates &leg)const;
    void SetLeg(float x, bool legUp){
        this->x = x;
        this->legUp = legUp;
    }
}SimplifiedLeg;