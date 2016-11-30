#ifndef FORCEIMPULSETEST_H
#define FORCEIMPULSETEST_H

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class ForceImpulseTest : public Test
{
  protected:
    b2Body* edgeBody;
    b2Body* bodies[3];
    bool forceOn;
    bool torqueOn;

  public:
    ForceImpulseTest()
    {
        //m_world->SetGravity(b2Vec2(0, 0));

        forceOn = false;
        torqueOn = false;

        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;

        b2PolygonShape polygonShape;
        polygonShape.SetAsBox(1, 1);

        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygonShape;
        myFixtureDef.density = 1;

        for (int i = 0; i < 3; i++) {
            myBodyDef.position.Set((-10 + i * 10), 20);
            bodies[i] = m_world->CreateBody(&myBodyDef);
            bodies[i]->CreateFixture(&myFixtureDef);
        }

        myBodyDef.type = b2_staticBody;
        myBodyDef.position.Set(0, 0);

        b2EdgeShape edgeShape;
        edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 0));

        myFixtureDef.shape = &edgeShape;

        edgeBody = m_world->CreateBody(&myBodyDef);
        edgeBody->CreateFixture(&myFixtureDef);
    }

    void Keyboard(unsigned char key)
    {
        switch(key)
        {
        case 'q':
            forceOn = !forceOn;
            break;
        case 'a':
            torqueOn = !torqueOn;
            break;

        case 'w':
            // apply immediate force upwards
            bodies[1]->ApplyLinearImpulse(
                //b2Vec2(0, 50), bodies[1]->GetWorldCenter(), true
                b2Vec2(0, 50), bodies[1]->GetWorldPoint(b2Vec2(1, 1)), true
            );
            break;
        case 's':
            // apply immediate spin counter clockwise
            bodies[1]->ApplyAngularImpulse(20, true);
            break;
        case 'e':
            bodies[2]->SetTransform(b2Vec2(10, 20), 0);
            break;
        default:
            // run default behavior
            Test::Keyboard(key);
        }
    }

    void Step(Settings* settings)
    {
        if (forceOn) {
            // apply gradual force upwards
            bodies[0]->ApplyForce(
                //b2Vec2(0, 50), bodies[0]->GetWorldCenter(), true
                b2Vec2(0, 50), bodies[0]->GetWorldPoint(b2Vec2(1, 1)), true
            );
        }

        if (torqueOn) {
            bodies[0]->ApplyTorque(20, true);
        }

        //run the default physics and rendering
        Test::Step(settings);
    }

    static Test* Create()
    {
        return new ForceImpulseTest;
    }
};

#endif
