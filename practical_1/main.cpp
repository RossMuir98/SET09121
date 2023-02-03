#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,   // Player1 Up
    Keyboard::Z,   // Player1 Down
    Keyboard::Up,  // Player2 Up
    Keyboard::Down // Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const int padding = 10.f;

//Chapter 3 Declarations
Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

void Load() {

    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

    //Set size and origin of paddles
    for (auto& p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }
    //Set size and origin of ball 
    ball.setRadius(ballRadius);
    ball.setOrigin({5, 5}); //Should be half the ball width and height
        //reset paddle position
        paddles[0].setPosition(Vector2(padding + paddleSize.x / 2.f, gameHeight / 2.f));
        paddles[1].setPosition(Vector2(gameWidth - padding - paddleSize.x / 2.f, gameHeight / 2.f));
    //reset ball position 
        ball.setPosition({400,300});
}

void Reset() {

}
void Update(RenderWindow& window) {
    //Reset clock and calc deltaTime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    //check and consume events 
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    //Quit via ESC key 
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    //Handle paddle movement
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
        paddles[0].move(Vector2(0.f, direction * paddleSpeed * dt));

        ball.move(ballVelocity * dt);

        // check ball collision
        const float bx = ball.getPosition().x;
        const float by = ball.getPosition().y;
        if (by > gameHeight) { //bottom wall
          // bottom wall
            ballVelocity.x *= 1.1f;
            ballVelocity.y *= -1.1f;
            ball.move(Vector2(0.f, -10.f));
        }
        else if (by < 0) { //top wall
       // top wall
            ballVelocity.x *= 1.1f;
            ballVelocity.y *= -1.1f;
            ball.move(Vector2(0.f, -10.f));
        }
}

void Render(RenderWindow& window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main() {
    RenderWindow window(VideoMode({ gameWidth, gameHeight }), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}