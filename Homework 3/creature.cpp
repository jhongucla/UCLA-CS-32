class Creature
{
public:
    Creature(string name);
    virtual ~Creature();
    string name() const;
    virtual string move() const = 0;
    virtual bool isMortal() const;
private:
    string m_name;
};

class Phoenix : public Creature
{
public:
    Phoenix(string name);
    virtual ~Phoenix();
    virtual string move() const;
    virtual bool isMortal() const;
};

class Giant : public Creature
{
public:
    Giant(string name, int weight);
    virtual ~Giant();
    virtual string move() const;
private:
    int m_weight;
};

class Centaur : public Creature
{
public:
    Centaur(string name);
    virtual ~Centaur();
    virtual string move() const;
};

Creature::Creature(string name)
: m_name(name)
{}

Creature::~Creature()
{}

string Creature::name() const
{
    return m_name;
}

bool Creature::isMortal() const
{
    return true;
}

Phoenix::Phoenix(string name)
: Creature(name)
{}

Phoenix::~Phoenix()
{
    cout << "Destroying " << Creature::name() << " the phoenix." << endl;
}

string Phoenix::move() const
{
    return "fly";
}

bool Phoenix::isMortal() const
{
    return false;
}

Giant::Giant(string name, int weight)
: Creature(name), m_weight(weight)
{}

Giant::~Giant()
{
    cout << "Destroying " << Creature::name() << " the giant." << endl;
}

string Giant::move() const
{
    if (m_weight < 20)
        return "tromp";
    return "lumber";
}

Centaur::Centaur(string name)
: Creature(name)
{}

Centaur::~Centaur()
{
    cout << "Destroying " << Creature::name() << " the centaur." << endl;
}

string Centaur::move() const
{
    return "trot";
}