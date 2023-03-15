#ifndef PLAYER_
#define PLAYER_H
#include "raylib.h"



class Ball{
    public:
        int cpu_score = 0;
        int player_score = 0;
        float x, y;
        int speedx, speedy;
        int radius;
        Ball(float, float, int, int, int);
        
    void draw(){
        DrawCircle(x, y, radius, RAYWHITE);
    }
    
    
    bool update(){
        x = x+speedx;
        y = y+speedy;
        if(x<=0){
            x = 400.0;
            y = 225.0;
            speedy = 0;
            speedx= -7;
            cpu_score ++;
            return true;
        }
        if (x >= GetScreenWidth()){
            x = 400.0;
            y = 225.0;
            speedy = 0;
            speedx= 7;
            player_score++;
            return true;
        }
        if(y+radius >= GetScreenHeight() || y-radius <= 0){
            speedy *= -1;
        }
        return false;
    }
    
    void directionAfterCollisionWithPlayer(int player_y, int add_speedx){
        float collision_point = y - player_y;
        if(collision_point <= 40 ){
            if(collision_point <= 10)
            {
                speedy = +7;
                speedx += add_speedx;
            } else
            {
                speedy = +5;
            }
        }
        if((collision_point <= 80) && (y - player_y > 40)){
            speedy = GetRandomValue(-2, 2);
        }
        if((collision_point >= 80) && (y - player_y <= 120)){
            if(collision_point >= 110)
            {
                speedy = -7;
                speedx += add_speedx;
            } else
            {
                speedy = -5;
            }
        }
    }
};


class Player{
    public:
        float x, y;
        float width, height;
        int speed;
        Player(float, float, int, float, float);
        
        
    void draw(){
        DrawRectangle(x, y, width, height, WHITE); 
    }
    
    
    void update(){
        if(IsKeyDown(KEY_UP) && y>0){
            y = y - speed;
        }
        
        if(IsKeyDown(KEY_DOWN) && y+height<GetScreenHeight()){
            y = y + speed;
        }      
    }
    
    
    void restart(){
        y = (GetScreenHeight()/2 - height/2);
    };
};


class Cpu: public Player{
    public:
        Cpu(float, float, int, float, float);
        
        
        void move(float ball_y, float ball_x, int screen_width, int screen_height, int paddle_height, int cpuReactionTime){
            if(ball_x>cpuReactionTime){
                if((y+60 > ball_y) && (y>0)){
                    y = y - speed;
                }
                if ((y+60 < ball_y) && (y+paddle_height<screen_height)){
                    y = y + speed;
                }
            }
        }
};


// CONSTRUCTORES

Ball::Ball(float _x, float _y, int _radius, int _speedx, int _speedy){
    x = _x;
    y = _y;
    radius = _radius;
    speedx = _speedx;
    speedy = _speedy;
}


Player::Player(float _x, float _y, int _speed, float _width, float _height){
    x = _x;
    y = _y;
    speed = _speed;
    width = _width;
    height = _height;
}


Cpu::Cpu(float _x, float _y, int _speed, float _width, float _height): Player(_x, _y, _speed, _width, _height){}
#endif