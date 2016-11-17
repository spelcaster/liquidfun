#ifndef FRICTIONTEST_H
#define FRICTIONTEST_H

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class FrictionTest : public Test
{
  protected:
    b2Body* body;
    b2Body* edgeBody;

  public:
    FrictionTest()
    {
        // set up a dynamic body
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;
        myBodyDef.position.Set(0, 20);
        body = m_world->CreateBody(&myBodyDef);

        // prepare a shape definition
        b2PolygonShape polygonShape;
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygonShape;
        myFixtureDef.density = 1;
        myFixtureDef.friction = 0.179;
        myFixtureDef.restitution = 0.06619999;

        //add 4 square shaped fixtures around the body center
        for (int i = 0; i < 4; i++) {
            b2Vec2 pos(sinf(i*90*DEGTORAD), cosf(i*90*DEGTORAD)); //radial placement
            polygonShape.SetAsBox(1, 1, pos, 0); // a 2x2 rectangle
            body->CreateFixture(&myFixtureDef);
        }

        myBodyDef.type = b2_staticBody;
        myBodyDef.position.Set(0, 0);
        edgeBody = m_world->CreateBody(&myBodyDef);

        b2Vec2 edge[2];
        edge[0].Set(-15, 0);
        edge[1].Set(15, 3);

        b2EdgeShape edgeShape;
        edgeShape.Set(edge[0], edge[1]);

        myFixtureDef.shape = &edgeShape;

        edgeBody->CreateFixture(&myFixtureDef);
    }

    void Step(Settings* settings)
    {
        //run the default physics and rendering
        Test::Step(settings);
    }

    static Test* Create()
    {
        return new FrictionTest;
    }
};

#endif
