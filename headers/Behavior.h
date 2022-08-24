#ifndef BEHAVIOR_H
#define BEHAVIOR_H

class Behavior
{
    public:
        virtual void update(void*, void*) = 0;
};

class Fall : public Behavior
{
    public:
        Fall(){}
        virtual void update(void*, void*);
};

class Rise : public Behavior
{
    private:
        bool passive;
    public:
        Rise(bool p): passive(p){}
        virtual void update(void*, void*);
};

class Grow : public Behavior
{
    private:
        int height;
    public:
        Grow(): height(0){}
        virtual void update(void*, void*);
};

class Liquid : public Behavior
{
    public:
        Liquid(){}
        virtual void update(void*, void*);
};

class Burn : public Behavior
{
    private:
        int halfLife;
    public:
        Burn(): halfLife(0){}
        virtual void update(void*, void*);
};

#endif