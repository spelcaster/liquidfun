#ifndef FIXTURETEST_H
#define FIXTURETEST_H

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class FixtureTest : public Test
{
  protected:
    b2Body* circleBody;
    b2Body* polygonBody;
    b2Body* boxBody;
    b2Body* edgeBody;
    b2Body* complexBody;

  public:
    FixtureTest()
    {
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
        myBodyDef.position.Set(-10, 20); //a little to the left

        circleBody = m_world->CreateBody(&myBodyDef);
        complexBody = m_world->CreateBody(&myBodyDef);

        b2CircleShape circleShape;
        circleShape.m_p.Set(0, 0); //position, relative to body position
        circleShape.m_radius = 1; //radius

        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
        myFixtureDef.density = 1; //this is a pointer to the shape above

        circleBody->CreateFixture(&myFixtureDef); //add a fixture to the body
        complexBody->CreateFixture(&myFixtureDef); //add a fixture to the body

        b2Vec2 vertices[5];
        vertices[0].Set(-1, 2);
        vertices[1].Set(-1, 0);
        vertices[2].Set(0, -3);
        vertices[3].Set(1, 0);
        vertices[4].Set(1, 1);

        b2PolygonShape polygonShape;
        polygonShape.Set(vertices, 5); //pass array to the shape

        myFixtureDef.shape = &polygonShape; //change the fixture shape
        myBodyDef.position.Set(0, 20); //in the middle

        polygonBody = m_world->CreateBody(&myBodyDef);
        polygonBody->CreateFixture(&myFixtureDef); //add fixture to the body

        vertices[0].Set(-1 +10, 2);
        vertices[1].Set(-1 +10, 0);
        vertices[2].Set(0 +10, -3);
        vertices[3].Set(1 +10, 0);
        vertices[4].Set(1 +10, 1);
        polygonShape.Set(vertices, 5); //pass array to the shape
        complexBody->CreateFixture(&myFixtureDef); //add fixture to the body

        polygonShape.SetAsBox(2, 1); //a 4x2 rectangle
        myBodyDef.position.Set(10, 20); //a bit to the right

        boxBody = m_world->CreateBody(&myBodyDef);
        boxBody->CreateFixture(&myFixtureDef);

        polygonShape.SetAsBox(2, 1, b2Vec2(20, 0), 0); //moved 20 units right, same angle
        complexBody->CreateFixture(&myFixtureDef);

        myBodyDef.type = b2_staticBody; //change body type
        myBodyDef.position.Set(0, 0);

        b2Vec2 edge[2];
        edge[0].Set(-15, 0);
        edge[1].Set(15, 0);

        b2EdgeShape edgeShape;
        edgeShape.Set(edge[0], edge[1]);

        myFixtureDef.shape = &edgeShape;

        edgeBody = m_world->CreateBody(&myBodyDef);
        edgeBody->CreateFixture(&myFixtureDef);
    }

    void Step(Settings* settings)
    {
        //run the default physics and rendering
        Test::Step(settings);

        // show some text in the main scree
        m_debugDraw.DrawString(5, m_textLine, "Now we have a Fixture Test");
        m_textLine += 15;
    }

    static Test* Create()
    {
        return new FixtureTest;
    }
};

#endif
